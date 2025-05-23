#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
    // REG2Eh - ADC Control
    class ADCControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x2E;

        enum class ADCSampleResolution : uint8_t
        {
            RES_15_BIT = 0b00,
            RES_14_BIT = 0b01,
            RES_13_BIT = 0b10,
            RES_12_BIT = 0b11 // Non recommandé
        };

        struct Values
        {
            bool adc_enable = false;                                                 // bit 7
            bool adc_rate_oneshot = false;                                           // bit 6 (false = continuous)
            ADCSampleResolution sample_resolution = ADCSampleResolution::RES_15_BIT; // bits 5:4
            bool average_enable = false;                                             // bit 3
            bool average_init = false;                                               // bit 2
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xFC; } // bits 1:0 réservés
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ADCControlRegister";
        uint8_t raw_ = 0;
    };

    // REG2Fh - ADC Function Disable 0
    class ADCFunctionDisable0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x2F;

        struct Values
        {
            bool ibus_adc_disable = false; // bit 7
            bool ibat_adc_disable = false; // bit 6
            bool vbus_adc_disable = false; // bit 5
            bool vbat_adc_disable = false; // bit 4
            bool vsys_adc_disable = false; // bit 3
            bool ts_adc_disable = false;   // bit 2
            bool tdie_adc_disable = false; // bit 1
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xFE; } // bit 0 réservé
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ADCFunctionDisable0Register";
        uint8_t raw_ = 0;
    };

    // REG30h - ADC Function Disable 1
    class ADCFunctionDisable1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x30;

        struct Values
        {
            bool dp_adc_disable = false;   // bit 7
            bool dm_adc_disable = false;   // bit 6
            bool vac2_adc_disable = false; // bit 5
            bool vac1_adc_disable = false; // bit 4
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xF0; } // bits 3:0 réservés
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ADCFunctionDisable1Register";
        uint8_t raw_ = 0;
    };

    struct ADCFunctionDisableRegister
    {
        ADCFunctionDisable0Register adc_function_disable0 = {};
        ADCFunctionDisable1Register adc_function_disable1 = {};

        void log() const;
        std::string to_json() const;
    };

    struct ConfigADC
    {
        ADCControlRegister acd = {};
        ADCFunctionDisableRegister adc_function_disable = {};

        void log() const;
        std::string to_json() const;
    };
}