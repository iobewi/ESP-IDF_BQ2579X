#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{
    // REG28h - Charger Mask 0
    class ChargerMask0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x28;

        struct Values
        {
            bool iindpm_mask = false;       // bit 7
            bool vindpm_mask = false;       // bit 6
            bool wd_mask = false;           // bit 5
            bool poorsrc_mask = false;      // bit 4
            bool pg_mask = false;           // bit 3
            bool ac2_present_mask = false;  // bit 2
            bool ac1_present_mask = false;  // bit 1
            bool vbus_present_mask = false; // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerMask0Register";
        uint8_t raw_ = 0;
    };

    // REG29h - Charger Mask 1
    class ChargerMask1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x29;

        struct Values
        {
            bool chg_mask = false;          // bit 7
            bool ico_mask = false;          // bit 6
            bool vbus_mask = false;         // bit 4
            bool treg_mask = false;         // bit 2
            bool vbat_present_mask = false; // bit 1
            bool bc1_2_done_mask = false;   // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xF7; } // bits 5 et 3 sont réservés
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerMask1Register";
        uint8_t raw_ = 0;
    };

    // REG2Ah - Charger Mask 2
    class ChargerMask2Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x2A;

        struct Values
        {
            bool dpdm_done_mask = false;  // bit 6
            bool adc_done_mask = false;   // bit 5
            bool vsys_mask = false;       // bit 4
            bool chg_tmr_mask = false;    // bit 3
            bool trichg_tmr_mask = false; // bit 2
            bool prechg_tmr_mask = false; // bit 1
            bool topoff_tmr_mask = false; // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0x7F; } // bit 7 est réservé
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerMask2Register";
        uint8_t raw_ = 0;
    };

    // REG2Bh - Charger Mask 3
    class ChargerMask3Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x2B;

        struct Values
        {
            bool vbatotg_low_mask = false; // bit 4
            bool ts_cold_mask = false;     // bit 3
            bool ts_cool_mask = false;     // bit 2
            bool ts_warm_mask = false;     // bit 1
            bool ts_hot_mask = false;      // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0x1F; } // bits 7:5 réservés
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_ChargerMask3Register";
        uint8_t raw_ = 0;
    };

    // REG2Ch - FAULT Mask 0
    class FaultMask0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x2C;

        struct Values
        {
            bool ibat_reg_mask = false; // bit 7
            bool vbus_ovp_mask = false; // bit 6
            bool vbat_ovp_mask = false; // bit 5
            bool ibus_ocp_mask = false; // bit 4
            bool ibat_ocp_mask = false; // bit 3
            bool conv_ocp_mask = false; // bit 2
            bool vac2_ovp_mask = false; // bit 1
            bool vac1_ovp_mask = false; // bit 0
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_FaultMask0Register";
        uint8_t raw_ = 0;
    };

    // REG2Dh - FAULT Mask 1
    class FaultMask1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x2D;

        struct Values
        {
            bool vsys_short_mask = false; // bit 7
            bool vsys_ovp_mask = false;   // bit 6
            bool otg_ovp_mask = false;    // bit 5
            bool otg_uvp_mask = false;    // bit 4
            bool tshut_mask = false;      // bit 2
        };

        void set_values(const Values &v);
        Values get_values() const;

        void set_raw(uint8_t raw) { raw_ = raw & 0xF4; } // bits réservés : 3,1,0
        uint8_t get_raw() const { return raw_; }

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_FaultMask1Register";
        uint8_t raw_ = 0;
    };

    struct ChargerMaskRegister
    {
        ChargerMask0Register charger_mask0 = {};
        ChargerMask1Register charger_mask1 = {};
        ChargerMask2Register charger_mask2 = {};
        ChargerMask3Register charger_mask3 = {};

        void log() const;

        std::string to_json() const;
    };

    struct FaultMaskRegister
    {
        FaultMask0Register fault_mask0 = {};
        FaultMask1Register fault_mask1 = {};

        void log() const;

        std::string to_json() const;
    };

    struct ConfigMask
    {
        ChargerMaskRegister charger_mask = {};
        FaultMaskRegister fault_mask = {};

        void log() const;

        std::string to_json() const;
    };
}