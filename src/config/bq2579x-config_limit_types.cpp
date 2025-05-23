#include "config/bq2579x-config_limit_types.hpp"
#include <esp_log.h>

namespace bq2579x
{

    void MinimalSystemVoltageRegister::set_value(uint16_t mv)
    {
        if (mv < 2500)
            mv = 2500;
        if (mv > 16000)
            mv = 16000;
        raw_ = ((mv - 2500) / 250) & 0x3F; // 6 bits
    }

    uint16_t MinimalSystemVoltageRegister::get_value() const
    {
        return ((raw_ & 0x3F) * 250) + 2500;
    }

    void ChargeVoltageLimitRegister::set_value(uint16_t mv)
    {
        if (mv < 3000)
            mv = 3000;
        if (mv > 18800)
            mv = 18800;
        raw_ = (mv / 10) & 0x07FF;
    }

    uint16_t ChargeVoltageLimitRegister::get_value() const
    {
        return (raw_ & 0x07FF) * 10;
    }

    void ChargeCurrentLimitRegister::set_value(uint16_t ma)
    {
        if (ma > 5000)
            ma = 5000;
        raw_ = (ma / 10) & 0x03FF; // 10 bits
    }

    uint16_t ChargeCurrentLimitRegister::get_value() const
    {
        return (raw_ & 0x03FF) * 10;
    }

    void InputVoltageLimitRegister::set_value(uint16_t mv)
    {
        if (mv < 3600)
            mv = 3600;
        if (mv > 22000)
            mv = 22000;
        raw_ = mv / 100;
    }

    uint16_t InputVoltageLimitRegister::get_value() const
    {
        return raw_ * 100;
    }

    void InputCurrentLimitRegister::set_value(uint16_t ma)
    {
        if (ma > 3300)
            ma = 3300;
        raw_ = ma / 10;
    }

    uint16_t InputCurrentLimitRegister::get_value() const
    {
        return raw_ * 10;
    }

    void VOTGRegulationRegister::set_value(uint16_t mv)
    {
        if (mv < 2800)
            mv = 2800;
        if (mv > 22000)
            mv = 22000;
        raw_ = (mv - 2800) / 10;
    }

    uint16_t VOTGRegulationRegister::get_value() const
    {
        return (raw_ & 0x07FF) * 10 + 2800;
    }

    void IOTGRegulationRegister::set_values(const IOTGRegulationRegister::Values &v)
    {
        uint8_t timer_bit = v.precharge_timer_short ? 0x80 : 0x00;
        uint8_t iotg = (v.otg_current_ma / 40) & 0x7F;
        raw_ = timer_bit | iotg;
    }

    IOTGRegulationRegister::Values IOTGRegulationRegister::get_values() const
    {
        Values v;
        v.precharge_timer_short = (raw_ >> 7) & 0x01;
        v.otg_current_ma = (raw_ & 0x7F) * 40;
        return v;
    }

    void ConfigLimit::log() const
    {
        ESP_LOGI("BQ2579X_ConfigLimit", " VSYSMIN        : %u mV (raw=0x%02X)", vsysmin_mv.get_value(), vsysmin_mv.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " VREG           : %u mV (raw=0x%04X)", vreg_mv.get_value(), vreg_mv.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " ICHG           : %u mA (raw=0x%04X)", ichg_ma.get_value(), ichg_ma.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " VINDPM         : %u mV (raw=0x%02X)", vindpm_mv.get_value(), vindpm_mv.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " IINDPM         : %u mA (raw=0x%02X)", iindpm_ma.get_value(), iindpm_ma.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " VOTG           : %u mV (raw=0x%04X)", votg_mv.get_value(), votg_mv.get_raw());

        IOTGRegulationRegister::Values otg = iotg_values.get_values();
        ESP_LOGI("BQ2579X_ConfigLimit", " IOTG           : %u mA (raw=0x%02X)", otg.otg_current_ma, iotg_values.get_raw());
        ESP_LOGI("BQ2579X_ConfigLimit", " PrechargeTimer : %s", otg.precharge_timer_short ? "0.5h" : "2h");
    }

    std::string ConfigLimit::to_json() const
    {
        IOTGRegulationRegister::Values otg = iotg_values.get_values();

        return std::string("{") +
               "\"vsysmin_mv\": " + std::to_string(vsysmin_mv.get_value()) + "," +
               "\"vreg_mv\": " + std::to_string(vreg_mv.get_value()) + "," +
               "\"ichg_ma\": " + std::to_string(ichg_ma.get_value()) + "," +
               "\"vindpm_mv\": " + std::to_string(vindpm_mv.get_value()) + "," +
               "\"iindpm_ma\": " + std::to_string(iindpm_ma.get_value()) + "," +
               "\"votg_mv\": " + std::to_string(votg_mv.get_value()) + "," +
               "\"iotg_ma\": " + std::to_string(otg.otg_current_ma) + "," +
               "\"precharge_timer_short\": " + std::to_string(otg.precharge_timer_short) +
               "}";
    }

}