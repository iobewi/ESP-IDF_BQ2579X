#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
    // REG17h - NTC Control 0
    class NTCControl0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x17;

        enum class JEITAVoltage : uint8_t
        {
            Suspend = 0b000,
            VREGm800mV = 0b001,
            VREGm600mV = 0b010,
            VREGm400mV = 0b011, // default
            VREGm300mV = 0b100,
            VREGm200mV = 0b101,
            VREGm100mV = 0b110,
            Unchanged = 0b111
        };

        enum class JEITACurrent : uint8_t
        {
            Suspend = 0b00,
            Pct20 = 0b01,
            Pct40 = 0b10,
            Unchanged = 0b11
        };

        struct Values
        {
            JEITAVoltage jeita_vset = JEITAVoltage::VREGm400mV;         // bits 7:5
            JEITACurrent jeita_iseth = JEITACurrent::Unchanged; // bits 4:3
            JEITACurrent jeita_isetc = JEITACurrent::Pct20;       // bits 2:1
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xFE; } // ignore reserved bit 0
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_NTCControl0Register";
        uint8_t raw_ = 0;
    };

    // REG18h - NTC Control 1
    class NTCControl1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x18;

        enum class TSCOOL : uint8_t
        {
            PCT_71_1 = 0b00, // ~5°C
            PCT_68_4 = 0b01, // ~10°C (default)
            PCT_65_5 = 0b10, // ~15°C
            PCT_62_4 = 0b11  // ~20°C
        };

        enum class TSWARM : uint8_t
        {
            PCT_48_4 = 0b00, // ~40°C
            PCT_44_8 = 0b01, // ~45°C (default)
            PCT_41_2 = 0b10, // ~50°C
            PCT_37_7 = 0b11  // ~55°C
        };

        enum class BHOT : uint8_t
        {
            Deg55 = 0b00,
            Deg60 = 0b01, // default
            Deg65 = 0b10,
            Disabled = 0b11
        };

        enum class BCOLD : uint8_t
        {
            DegMinus10 = 0b0, // default
            DegMinus20 = 0b1
        };

        struct Values
        {
            TSCOOL ts_cool = TSCOOL::PCT_68_4; // bits 7:6
            TSWARM ts_warm = TSWARM::PCT_44_8; // bits 5:4
            BHOT bhot = BHOT::Deg60;           // bits 3:2
            BCOLD bcold = BCOLD::DegMinus10;   // bit 1
            bool ts_ignore = false;            // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_NTCControl1Register";
        uint8_t raw_ = 0;
    };
    
    struct NTCControlRegister
    {
        NTCControl0Register ntc_control0 = {};
        NTCControl1Register ntc_control1 = {};

        void log() const;
        std::string to_json() const;
    };
}