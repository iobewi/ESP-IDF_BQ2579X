#pragma once
#include <vector>
#include <cstdint>
#include <string>

#include "config/bq2579x-config_control_charger_types.hpp"
#include "config/bq2579x-config_control_ntc_types.hpp"

namespace bq2579x
{

    // REG08h - Precharge Control
    class PrechargeControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x08;

        enum class VBATLowThreshold : uint8_t
        {
            THRESH_15 = 0b00,
            THRESH_622 = 0b01,
            THRESH_667 = 0b10,
            THRESH_714 = 0b11
        };

        struct Values
        {
            uint16_t precharge_current_ma = 120;                       // IPRECHG
            VBATLowThreshold threshold = VBATLowThreshold::THRESH_714; // VBAT_LOWV
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_PrechargeControlRegister";
        uint8_t raw_ = 0;
    };

    // REG09h - Termination Control
    class TerminationControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x09;

        struct Values
        {
            bool reg_rst = false;     // Bit 6
            bool stop_wd_chg = false; // Bit 5
            uint16_t iterm_ma = 200;  // Bits 4:0 (40–1000 mA, 40 mA step)
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_TerminationControlRegister";
        uint8_t raw_ = 0;
    };

    // REG0Ah - Re-charge Control
    class RechargeControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x0A;

        enum class CellCount : uint8_t
        {
            One = 0b00,
            Two = 0b01,
            Three = 0b10,
            Four = 0b11
        };

        enum class DeglitchTime : uint8_t
        {
            T_64ms = 0b00,
            T_256ms = 0b01,
            T_1024ms = 0b10,
            T_2048ms = 0b11
        };

        struct Values
        {
            CellCount cell_count = CellCount::Four;       // bits 7:6
            DeglitchTime trechg = DeglitchTime::T_1024ms; // bits 5:4
            uint16_t vrechg_offset_mv = 200;              // bits 3:0, 50 mV/LSB
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_RechargeControlRegister";
        uint8_t raw_ = 0;
    };

    // REG0Eh - Timer Control
    class TimerControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x0E;

        enum class TopOffTimer : uint8_t
        {
            Disabled = 0b00,
            Min15 = 0b01,
            Min30 = 0b10,
            Min45 = 0b11
        };

        enum class ChargeTimer : uint8_t
        {
            Hr5 = 0b00,
            Hr8 = 0b01,
            Hr12 = 0b10,
            Hr24 = 0b11
        };

        struct Values
        {
            TopOffTimer topoff_timer = TopOffTimer::Disabled; // bits 7:6
            bool en_trichg_timer = true;                      // bit 5
            bool en_prechg_timer = true;                      // bit 4
            bool en_chg_timer = true;                         // bit 3
            ChargeTimer chg_timer = ChargeTimer::Hr12;        // bits 2:1
            bool tmr2x_en = true;                             // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_TimerControlRegister";
        uint8_t raw_ = 0;
    };

    // REG15h - MPPT Control
    class MPPTControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x15;

        enum class VOCPct : uint8_t
        {
            PCT_0_5625 = 0b000,
            PCT_0_6250 = 0b001,
            PCT_0_6875 = 0b010,
            PCT_0_7500 = 0b011,
            PCT_0_8125 = 0b100,
            PCT_0_8750 = 0b101, // default
            PCT_0_9375 = 0b110,
            PCT_1_0000 = 0b111
        };

        enum class VOCDelay : uint8_t
        {
            Delay_50ms = 0b00,
            Delay_300ms = 0b01, // default
            Delay_2s = 0b10,
            Delay_5s = 0b11
        };

        enum class VOCRate : uint8_t
        {
            Interval_30s = 0b00,
            Interval_2min = 0b01, // default
            Interval_10min = 0b10,
            Interval_30min = 0b11
        };

        struct Values
        {
            VOCPct voc_pct = VOCPct::PCT_0_8750;       // bits 7:5
            VOCDelay voc_dly = VOCDelay::Delay_300ms;  // bits 4:3
            VOCRate voc_rate = VOCRate::Interval_2min; // bits 2:1
            bool en_mppt = false;                      // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_MPPTControlRegister";
        uint8_t raw_ = 0;
    };

    // REG16h - Temperature Control
    class TemperatureControlRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x16;

        enum class ThermalRegulation : uint8_t
        {
            Deg60 = 0b00,
            Deg80 = 0b01,
            Deg100 = 0b10,
            Deg120 = 0b11 // default
        };

        enum class ThermalShutdown : uint8_t
        {
            Deg150 = 0b00, // default
            Deg130 = 0b01,
            Deg120 = 0b10,
            Deg85 = 0b11
        };

        struct Values
        {
            ThermalRegulation treg = ThermalRegulation::Deg120; // bits 7:6
            ThermalShutdown tshut = ThermalShutdown::Deg150;    // bits 5:4
            bool vbus_pd_en = false;                            // bit 3
            bool vac1_pd_en = false;                            // bit 2
            bool vac2_pd_en = false;                            // bit 1
            bool bkup_acfet1_on = false;                        // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_TemperatureControlRegister";
        uint8_t raw_ = 0;
    };

    // REG47h - DPDM Driver Register
    class DPDMDriverRegister
    {
    public:
        static constexpr uint8_t reg_addr = 0x47;

        enum class OutputLevel : uint8_t
        {
            HIZ = 0b000,
            VOLT_0V = 0b001,
            VOLT_0V6 = 0b010,
            VOLT_1V2 = 0b011,
            VOLT_2V0 = 0b100,
            VOLT_2V7 = 0b101,
            VOLT_3V3 = 0b110,
            DP_DM_SHORT = 0b111 // pour D+ uniquement, réservé pour D-
        };

        struct Values
        {
            OutputLevel dplus = OutputLevel::HIZ;
            OutputLevel dminus = OutputLevel::HIZ; // 0b111 est réservé et ne doit pas être utilisé ici
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xFC; } // bits 1-0 réservés
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_DPDMDriverRegister";
        uint8_t raw_ = 0;
    };

    struct ConfigControl
    {
        PrechargeControlRegister pre_charge = {};
        TerminationControlRegister termination = {};
        RechargeControlRegister re_charge = {};
        TimerControlRegister timer = {};
        ChargerControlRegister charger = {};
        MPPTControlRegister mppt = {};
        TemperatureControlRegister temperature = {};
        NTCControlRegister ntc = {};
        DPDMDriverRegister dpdm = {};

        void log() const;
        std::string to_json() const;
    };
}