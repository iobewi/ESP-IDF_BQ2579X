#include "config/bq2579x-config_adc_types.hpp"
#include <esp_log.h>

namespace bq2579x
{
    const char *to_string(ADCControlRegister::ADCSampleResolution res)
    {
        switch (res)
        {
        case ADCControlRegister::ADCSampleResolution::RES_15_BIT:
            return "\"15bit\"";
        case ADCControlRegister::ADCSampleResolution::RES_14_BIT:
            return "\"14bit\"";
        case ADCControlRegister::ADCSampleResolution::RES_13_BIT:
            return "\"13bit\"";
        case ADCControlRegister::ADCSampleResolution::RES_12_BIT:
            return "\"12bit\"";
        default:
            return "\"unknown\"";
        }
    }

    void ADCControlRegister::set_values(const ADCControlRegister::Values &v)
    {
        raw_ = (v.adc_enable ? 1 << 7 : 0) | (v.adc_rate_oneshot ? 1 << 6 : 0) | (static_cast<uint8_t>(v.sample_resolution) << 4) | (v.average_enable ? 1 << 3 : 0) | (v.average_init ? 1 << 2 : 0);
    }

    ADCControlRegister::Values ADCControlRegister::get_values() const
    {
        Values v;
        v.adc_enable = (raw_ >> 7) & 0x01;
        v.adc_rate_oneshot = (raw_ >> 6) & 0x01;
        v.sample_resolution = static_cast<ADCSampleResolution>((raw_ >> 4) & 0x03);
        v.average_enable = (raw_ >> 3) & 0x01;
        v.average_init = (raw_ >> 2) & 0x01;
        return v;
    }

    void ADCControlRegister::log() const
    {
        auto v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW        : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " Sample Resolution   : %s", to_string(v.sample_resolution));
        ESP_LOGI(TAG, " EN=%d OS=%d AVG_EN=%d AVG_INIT=%d",
                 v.adc_enable,
                 v.adc_rate_oneshot,
                 v.average_enable,
                 v.average_init);
    }

    std::string ADCControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"EN\": " + std::to_string(v.adc_enable) + "," +
               "\"OS\": " + std::to_string(v.adc_rate_oneshot) + "," +
               "\"RES\": " + std::to_string(static_cast<uint8_t>(v.sample_resolution)) + "," +
               "\"AVG_EN\": " + std::to_string(v.average_enable) + "," +
               "\"AVG_INIT\": " + std::to_string(v.average_init) +
               "}";
    }

    void ADCFunctionDisable0Register::set_values(const ADCFunctionDisable0Register::Values &v)
    {
        raw_ = (v.ibus_adc_disable ? 1 << 7 : 0) | (v.ibat_adc_disable ? 1 << 6 : 0) | (v.vbus_adc_disable ? 1 << 5 : 0) | (v.vbat_adc_disable ? 1 << 4 : 0) | (v.vsys_adc_disable ? 1 << 3 : 0) | (v.ts_adc_disable ? 1 << 2 : 0) | (v.tdie_adc_disable ? 1 << 1 : 0);
        // bit 0 réservé
    }

    ADCFunctionDisable0Register::Values ADCFunctionDisable0Register::get_values() const
    {
        Values v;
        v.ibus_adc_disable = (raw_ >> 7) & 0x01;
        v.ibat_adc_disable = (raw_ >> 6) & 0x01;
        v.vbus_adc_disable = (raw_ >> 5) & 0x01;
        v.vbat_adc_disable = (raw_ >> 4) & 0x01;
        v.vsys_adc_disable = (raw_ >> 3) & 0x01;
        v.ts_adc_disable = (raw_ >> 2) & 0x01;
        v.tdie_adc_disable = (raw_ >> 1) & 0x01;
        return v;
    }

    void ADCFunctionDisable0Register::log() const
    {
        auto v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " IBUS=%d IBAT=%d VBUS=%d VBAT=%d VSYS=%d TS=%d TDIE=%d",
                 v.ibus_adc_disable,
                 v.ibat_adc_disable,
                 v.vbus_adc_disable,
                 v.vbat_adc_disable,
                 v.vsys_adc_disable,
                 v.ts_adc_disable,
                 v.tdie_adc_disable);
    }

    std::string ADCFunctionDisable0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"IBUS\": " + std::to_string(v.ibus_adc_disable) + "," +
               "\"IBAT\": " + std::to_string(v.ibat_adc_disable) + "," +
               "\"VBUS\": " + std::to_string(v.vbus_adc_disable) + "," +
               "\"VBAT\": " + std::to_string(v.vbat_adc_disable) + "," +
               "\"VSYS\": " + std::to_string(v.vsys_adc_disable) + "," +
               "\"TS\": " + std::to_string(v.ts_adc_disable) + "," +
               "\"TDIE\": " + std::to_string(v.tdie_adc_disable) +
               "}";
    }

    void ADCFunctionDisable1Register::set_values(const ADCFunctionDisable1Register::Values &v)
    {
        raw_ = (v.dp_adc_disable ? 1 << 7 : 0) | (v.dm_adc_disable ? 1 << 6 : 0) | (v.vac2_adc_disable ? 1 << 5 : 0) | (v.vac1_adc_disable ? 1 << 4 : 0);
        // bits 3:0 réservés
    }

    ADCFunctionDisable1Register::Values ADCFunctionDisable1Register::get_values() const
    {
        Values v;
        v.dp_adc_disable = (raw_ >> 7) & 0x01;
        v.dm_adc_disable = (raw_ >> 6) & 0x01;
        v.vac2_adc_disable = (raw_ >> 5) & 0x01;
        v.vac1_adc_disable = (raw_ >> 4) & 0x01;
        return v;
    }

    void ADCFunctionDisable1Register::log() const
    {
        auto v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " DP=%d DM=%d VAC2=%d VAC1=%d",
                 v.dp_adc_disable,
                 v.dm_adc_disable,
                 v.vac2_adc_disable,
                 v.vac1_adc_disable);
    }

    std::string ADCFunctionDisable1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"DP\": " + std::to_string(v.dp_adc_disable) + "," +
               "\"DM\": " + std::to_string(v.dm_adc_disable) + "," +
               "\"VAC2\": " + std::to_string(v.vac2_adc_disable) + "," +
               "\"VAC1\": " + std::to_string(v.vac1_adc_disable) +
               "}";
    }

    void ADCFunctionDisableRegister::log() const
    {
        adc_function_disable0.log();
        adc_function_disable1.log();
    }

    std::string ADCFunctionDisableRegister::to_json() const
    {
        return std::string("{") +
               "\"disable0\": " + adc_function_disable0.to_json() + "," +
               "\"disable1\": " + adc_function_disable1.to_json() +
               "}";
    }

    void ConfigADC::log() const
    {
        acd.log();
        adc_function_disable.log();
    }

    std::string ConfigADC::to_json() const
    {
        return std::string("{") +
               "\"control\": " + acd.to_json() + "," +
               "\"function_disable\": " + adc_function_disable.to_json() +
               "}";
    }

}