#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
    // REG0Fh - Charger Control 0
    class ChargerControl0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x0F;

        struct Values
        {
            bool en_auto_ibatdis = true; // bit 7
            bool force_ibatdis = false;  // bit 6
            bool en_chg = true;          // bit 5
            bool en_ico = false;         // bit 4
            bool force_ico = false;      // bit 3
            bool en_hiz = false;         // bit 2
            bool en_term = true;         // bit 1
            bool en_backup = false;      // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl0Register";
        uint8_t raw_ = 0;
    };

    // REG10h - Charger Control 1
    class ChargerControl1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x10;

        enum class VBUSBackupRatio : uint8_t
        {
            Ratio40 = 0b00,
            Ratio60 = 0b01,
            Ratio80 = 0b10,
            Ratio100 = 0b11
        };

        enum class VACOVPThreshold : uint8_t
        {
            V26 = 0b00,
            V22 = 0b01,
            V12 = 0b10,
            V7 = 0b11
        };

        enum class WatchdogTimeout : uint8_t
        {
            Disable = 0b000,
            Sec0_5 = 0b001,
            Sec1 = 0b010,
            Sec2 = 0b011,
            Sec20 = 0b100,
            Sec40 = 0b101,
            Sec80 = 0b110,
            Sec160 = 0b111
        };

        struct Values
        {
            VBUSBackupRatio vbus_backup = VBUSBackupRatio::Ratio80; // bits 7:6
            VACOVPThreshold vac_ovp = VACOVPThreshold::V26;         // bits 5:4
            bool wd_rst = false;                                    // bit 3
            WatchdogTimeout watchdog = WatchdogTimeout::Sec40;      // bits 2:0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl1Register";
        uint8_t raw_ = 0;
    };

    // REG11h - Charger Control 2
    class ChargerControl2Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x11;

        enum class SFETControl : uint8_t
        {
            Idle = 0b00,
            Shutdown = 0b01,
            Ship = 0b10,
            Reset = 0b11
        };

        struct Values
        {
            bool force_indet = false;                  // bit 7
            bool auto_indet_en = true;                 // bit 6
            bool en_12v = false;                       // bit 5
            bool en_9v = false;                        // bit 4
            bool hvdcp_en = false;                     // bit 3
            SFETControl sdrv_ctrl = SFETControl::Idle; // bits 2:1
            bool sdrv_dly = false;                     // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl2Register";
        uint8_t raw_ = 0;
    };

    // REG12h - Charger Control 3
    class ChargerControl3Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x12;

        struct Values
        {
            bool dis_acdrv = false;   // bit 7
            bool en_otg = false;      // bit 6
            bool pfm_otg_dis = false; // bit 5
            bool pfm_fwd_dis = false; // bit 4
            bool wkup_dly = false;    // bit 3 (0 = 1s, 1 = 15ms)
            bool dis_ldo = false;     // bit 2
            bool dis_otg_ooa = false; // bit 1
            bool dis_fwd_ooa = false; // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl3Register";
        uint8_t raw_ = 0;
    };

    // REG13h - Charger Control 4
    class ChargerControl4Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x13;

        struct Values
        {
            bool en_acdrv2 = false;        // bit 7
            bool en_acdrv1 = false;        // bit 6
            bool pwm_freq_750khz = false;  // bit 5 (false = 1.5MHz, true = 750kHz)
            bool dis_stat = false;         // bit 4
            bool dis_vsys_short = false;   // bit 3
            bool dis_votg_uvp = false;     // bit 2
            bool force_vindpm_det = false; // bit 1
            bool en_ibus_ocp = true;       // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl4Register";
        uint8_t raw_ = 0;
    };

    // REG14h - Charger Control 5
    class ChargerControl5Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x14;

        enum class IBATRegulation : uint8_t
        {
            A3 = 0b00,
            A4 = 0b01,
            A5 = 0b10,
            A6 = 0b11
        };

        struct Values
        {
            bool sfet_present = false;                    // bit 7
            bool en_ibat = false;                         // bit 5
            IBATRegulation ibat_reg = IBATRegulation::A6; // bits 4:3
            bool en_iindpm = true;                        // bit 2
            bool en_extilim = true;                       // bit 1
            bool en_batoc = false;                        // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerControl5Register";
        uint8_t raw_ = 0;
    };

    struct ChargerControlRegister
    {
        ChargerControl0Register charger_control0 = {};
        ChargerControl1Register charger_control1 = {};
        ChargerControl2Register charger_control2 = {};
        ChargerControl3Register charger_control3 = {};
        ChargerControl4Register charger_control4 = {};
        ChargerControl5Register charger_control5 = {};

        void log() const;
        std::string to_json() const;
    };
}