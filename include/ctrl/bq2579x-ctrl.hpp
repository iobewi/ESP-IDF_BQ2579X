#pragma once
#include <cstdint>
#include <string>

#include "ctrl/bq2579x-ctrl_types.hpp"
#include "bq2579x-interface.hpp"

namespace bq2579x
{
    static_assert(std::is_class<INTERFACE>::value, "INTERFACE is not a class");
    class CTRL : public INTERFACE
    {
    public:
        explicit CTRL(I2CDevices &dev) : INTERFACE(dev) {}

        ICO_Current_Limit_Register ico_current_limit_ma = {};
        IBUS_ADC_Register ibus_adc_ma = {};
        IBAT_ADC_Register ibat_adc_ma = {};
        VBUS_ADC_Register vbus_adc_mv = {};
        VAC1_ADC_Register vac1_adc_mv = {};
        VAC2_ADC_Register vacd2_adc_mv = {};
        VBAT_ADC_Register vbat_adc_mv = {};
        VSYS_ADC_Register vsys_adc_mv = {};
        TS_ADC_Register ts_adc_mp = {};
        TDIE_ADC_Register tdie_adc_dc = {};
        DPlus_ADC_Register dplus_adc_mv = {};
        DMinus_ADC_Register dminus_adc_mv = {};
        
        esp_err_t ready();
        esp_err_t send_reset();

        esp_err_t en_adc();
        esp_err_t get_ico_current_limit();
        esp_err_t get_ibus_adc();
        esp_err_t get_ibat_adc();
        esp_err_t get_vbus_adc();
        esp_err_t get_vac1_adc();
        esp_err_t get_vacd2_adc();
        esp_err_t get_vbat_adc();
        esp_err_t get_vsys_adc();
        esp_err_t get_ts_adc();
        esp_err_t get_tdie_adc();
        esp_err_t get_dplus_adc();
        esp_err_t get_dminus_adc();
        esp_err_t get();

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_CTRL";

        static constexpr uint8_t REG_RESET = 0X10;
        static constexpr uint8_t REG_ADC_CONTROL = 0X2E;
        static constexpr uint8_t VALUE_DEVICE_ID  = 0x03;
        static constexpr uint16_t RESET_COMMAND = 1 << 3; // [3] Watchdog Reset (0 = pas de reset, 1 = reset)
        static constexpr uint16_t EN_ADC_COMMAND = 1 << 7;


    };

} // namespace bq2579x