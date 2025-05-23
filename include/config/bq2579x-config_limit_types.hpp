#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
    // REG00h - Minimal System Voltage (VSYSMIN)
    class MinimalSystemVoltageRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x00;

        void set_value(uint16_t mv);
        uint16_t get_value() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG01h - Charge Voltage Limit (VREG)
    class ChargeVoltageLimitRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x01;

        void set_value(uint16_t mv);
        uint16_t get_value() const;

        void set_raw(uint16_t raw) { raw_ = raw & 0x07FF; }
        uint16_t get_raw() const { return raw_; }

    private:
        uint16_t raw_ = 0;
    };

    // REG03h - Charge Current Limit (ICHG)
    class ChargeCurrentLimitRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x03;

        void set_value(uint16_t ma);
        uint16_t get_value() const;

        void set_raw(uint16_t raw) { raw_ = raw & 0x03FF; }
        uint16_t get_raw() const { return raw_; }

    private:
        uint16_t raw_ = 0;
    };

    // REG05h - Input Voltage Limit (VINDPM)
    class InputVoltageLimitRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x05;

        void set_value(uint16_t mv);
        uint16_t get_value() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG06h - Input Current Limit (IINDPM)
    class InputCurrentLimitRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x06;

        void set_value(uint16_t ma);
        uint16_t get_value() const;

        void set_raw(uint16_t raw) { raw_ = raw; }
        uint16_t get_raw() const { return raw_; }

    private:
        uint16_t raw_ = 0;
    };

    // REG0Bh - VOTG Regulation
    class VOTGRegulationRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x0B;

        void set_value(uint16_t mv);
        uint16_t get_value() const;

        void set_raw(uint16_t raw) { raw_ = raw & 0x07FF; } // 11 bits VOTG_10:0
        uint16_t get_raw() const { return raw_; }

    private:
        uint16_t raw_ = 0;
    };

    // REG0Dh - IOTG Regulation
    class IOTGRegulationRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x0D;

        struct Values
        {
            bool precharge_timer_short = false; // bit 7: false = 2h, true = 0.5h
            uint16_t otg_current_ma = 3040;     // bits 6:0 (160–3360mA, 40mA step)
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    struct ConfigLimit
    {
        MinimalSystemVoltageRegister vsysmin_mv = {};
        ChargeVoltageLimitRegister vreg_mv = {};
        ChargeCurrentLimitRegister ichg_ma = {};
        InputVoltageLimitRegister vindpm_mv = {};
        InputCurrentLimitRegister iindpm_ma = {};
        VOTGRegulationRegister votg_mv = {};
        IOTGRegulationRegister iotg_values = {};

        void log() const;
        std::string to_json() const;
    };

}