#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{

    // REG1Bh - Charger Status 0
    class ChargerStatus0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x1B;

        struct Values
        {
            bool iindpm_stat = false;
            bool vindpm_stat = false;
            bool wd_stat = false;
            bool pg_stat = false;
            bool ac2_present = false;
            bool ac1_present = false;
            bool vbus_present = false;
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerStatus0Register";
        uint8_t raw_ = 0;
    };

    // REG1Ch - Charger Status 1
    class ChargerStatus1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x1C;

        enum class ChargeStatus : uint8_t
        {
            NotCharging = 0b000,
            TrickleCharge = 0b001,
            PreCharge = 0b010,
            FastCharge = 0b011,
            TaperCharge = 0b100,
            Reserved = 0b101,
            TopOffCharge = 0b110,
            TerminationDone = 0b111
        };

        enum class VbusStatus : uint8_t
        {
            NoInput = 0x0,
            USB_SDP = 0x1,            // 500 mA
            USB_CDP = 0x2,            // 1.5 A
            USB_DCP = 0x3,            // 3.25 A
            AdjustableHV_DCP = 0x4,   // 1.5 A
            UnknownAdapter = 0x5,     // 3 A
            NonStandardAdapter = 0x6, // 1A/2A/2.1A/2.4A
            OTGMode = 0x7,
            NotQualifiedAdapter = 0x8,
            Reserved_9 = 0x9,
            Reserved_A = 0xA,
            DirectVBUS = 0xB,
            BackupMode = 0xC,
            Reserved_D = 0xD,
            Reserved_E = 0xE,
            Reserved_F = 0xF,
        };

        struct Values
        {
            ChargeStatus charge_status;
            VbusStatus vbus_status;
            bool bc12_done;
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerStatus1Register";
        uint8_t raw_ = 0;
    };

    // REG1Dh - Charger Status 2
    class ChargerStatus2Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x1D;

        enum class ICOStatus : uint8_t
        {
            Disabled = 0b00,
            OptimizationInProgress = 0b01,
            MaxInputCurrentDetected = 0b10,
            Reserved = 0b11
        };

        struct Values
        {
            ICOStatus ico_status;
            bool treg_stat;
            bool dpdm_stat;
            bool vbat_present;
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerStatus2Register";
        uint8_t raw_ = 0;
    };

    // REG1Eh - Charger Status 3
    class ChargerStatus3Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x1E;

        struct Values
        {
            bool acrb2_stat;      // Bit 7
            bool acrb1_stat;      // Bit 6
            bool adc_done_stat;   // Bit 5
            bool vsys_stat;       // Bit 4
            bool chg_tmr_stat;    // Bit 3
            bool trichg_tmr_stat; // Bit 2
            bool prechg_tmr_stat; // Bit 1
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerStatus3Register";
        uint8_t raw_ = 0;
    };

    // REG1Fh - Charger Status 4
    class ChargerStatus4Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x1F;

        struct Values
        {
            bool vbatotg_low_stat; // Bit 4
            bool ts_cold_stat;     // Bit 3
            bool ts_cool_stat;     // Bit 2
            bool ts_warm_stat;     // Bit 1
            bool ts_hot_stat;      // Bit 0
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerStatus4Register";
        uint8_t raw_ = 0;
    };

    // REG20h - FAULT Status 0
    class FaultStatus0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x20;

        struct Values
        {
            bool ibat_reg_stat; // Bit 7
            bool vbus_ovp_stat; // Bit 6
            bool vbat_ovp_stat; // Bit 5
            bool ibus_ocp_stat; // Bit 4
            bool ibat_ocp_stat; // Bit 3
            bool conv_ocp_stat; // Bit 2
            bool vac2_ovp_stat; // Bit 1
            bool vac1_ovp_stat; // Bit 0
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_FaultStatus0Register";
        uint8_t raw_ = 0;
    };

    // REG21h - FAULT Status 1
    class FaultStatus1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x21;

        struct Values
        {
            bool vsys_short_stat; // Bit 7
            bool vsys_ovp_stat;   // Bit 6
            bool otg_ovp_stat;    // Bit 5
            bool otg_uvp_stat;    // Bit 4
            bool tshut_stat;      // Bit 2
        };

        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_FaultStatus1Register";
        uint8_t raw_ = 0;
    };

}