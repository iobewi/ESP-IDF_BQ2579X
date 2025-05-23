#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace bq2579x
{

    // REG22h - Charger Flag 0
    class ChargerFlag0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x22;

        struct Values
        {
            bool iindpm_flag;       // Bit 7
            bool vindpm_flag;       // Bit 6
            bool wd_flag;           // Bit 5
            bool poorsrc_flag;      // Bit 4
            bool pg_flag;           // Bit 3
            bool ac2_present_flag;  // Bit 2
            bool ac1_present_flag;  // Bit 1
            bool vbus_present_flag; // Bit 0
        };

        Values get_values() const
        {
            Values v;
            v.iindpm_flag = (raw_ >> 7) & 0x01;
            v.vindpm_flag = (raw_ >> 6) & 0x01;
            v.wd_flag = (raw_ >> 5) & 0x01;
            v.poorsrc_flag = (raw_ >> 4) & 0x01;
            v.pg_flag = (raw_ >> 3) & 0x01;
            v.ac2_present_flag = (raw_ >> 2) & 0x01;
            v.ac1_present_flag = (raw_ >> 1) & 0x01;
            v.vbus_present_flag = (raw_ >> 0) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG23h - Charger Flag 1
    class ChargerFlag1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x23;

        struct Values
        {
            bool chg_flag;          // Bit 7
            bool ico_flag;          // Bit 6
            bool vbus_flag;         // Bit 4
            bool treg_flag;         // Bit 2
            bool vbat_present_flag; // Bit 1
            bool bc12_done_flag;    // Bit 0
        };

        Values get_values() const
        {
            Values v;
            v.chg_flag = (raw_ >> 7) & 0x01;
            v.ico_flag = (raw_ >> 6) & 0x01;
            v.vbus_flag = (raw_ >> 4) & 0x01;
            v.treg_flag = (raw_ >> 2) & 0x01;
            v.vbat_present_flag = (raw_ >> 1) & 0x01;
            v.bc12_done_flag = (raw_ >> 0) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG24h - Charger Flag 2
    class ChargerFlag2Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x24;

        struct Values
        {
            bool dpdm_done_flag;  // Bit 6
            bool adc_done_flag;   // Bit 5
            bool vsys_flag;       // Bit 4
            bool chg_tmr_flag;    // Bit 3
            bool trichg_tmr_flag; // Bit 2
            bool prechg_tmr_flag; // Bit 1
            bool topoff_tmr_flag; // Bit 0
        };

        Values get_values() const
        {
            Values v;
            v.dpdm_done_flag = (raw_ >> 6) & 0x01;
            v.adc_done_flag = (raw_ >> 5) & 0x01;
            v.vsys_flag = (raw_ >> 4) & 0x01;
            v.chg_tmr_flag = (raw_ >> 3) & 0x01;
            v.trichg_tmr_flag = (raw_ >> 2) & 0x01;
            v.prechg_tmr_flag = (raw_ >> 1) & 0x01;
            v.topoff_tmr_flag = (raw_ >> 0) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG25h - Charger Flag 3
    class ChargerFlag3Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x25;

        struct Values
        {
            bool vbatotg_low_flag; // Bit 4
            bool ts_cold_flag;     // Bit 3
            bool ts_cool_flag;     // Bit 2
            bool ts_warm_flag;     // Bit 1
            bool ts_hot_flag;      // Bit 0
        };

        Values get_values() const
        {
            Values v;
            v.vbatotg_low_flag = (raw_ >> 4) & 0x01;
            v.ts_cold_flag = (raw_ >> 3) & 0x01;
            v.ts_cool_flag = (raw_ >> 2) & 0x01;
            v.ts_warm_flag = (raw_ >> 1) & 0x01;
            v.ts_hot_flag = (raw_ >> 0) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG26h - Fault Flag 0
    class FaultFlag0Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x26;

        struct Values
        {
            bool ibat_reg_flag; // Bit 7
            bool vbus_ovp_flag; // Bit 6
            bool vbat_ovp_flag; // Bit 5
            bool ibus_ocp_flag; // Bit 4
            bool ibat_ocp_flag; // Bit 3
            bool conv_ocp_flag; // Bit 2
            bool vac2_ovp_flag; // Bit 1
            bool vac1_ovp_flag; // Bit 0
        };

        Values get_values() const
        {
            Values v;
            v.ibat_reg_flag = (raw_ >> 7) & 0x01;
            v.vbus_ovp_flag = (raw_ >> 6) & 0x01;
            v.vbat_ovp_flag = (raw_ >> 5) & 0x01;
            v.ibus_ocp_flag = (raw_ >> 4) & 0x01;
            v.ibat_ocp_flag = (raw_ >> 3) & 0x01;
            v.conv_ocp_flag = (raw_ >> 2) & 0x01;
            v.vac2_ovp_flag = (raw_ >> 1) & 0x01;
            v.vac1_ovp_flag = (raw_ >> 0) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }

    private:
        uint8_t raw_ = 0;
    };

    // REG27h - FAULT Flag 1
    class FaultFlag1Register
    {
    public:
        static constexpr uint8_t reg_addr = 0x27;

        struct Values
        {
            bool vsys_short_flag; // Bit 7
            bool vsys_ovp_flag;   // Bit 6
            bool otg_ovp_flag;    // Bit 5
            bool otg_uvp_flag;    // Bit 4
            bool tshut_flag;      // Bit 2
        };

        Values get_values() const
        {
            Values v;
            v.vsys_short_flag = (raw_ >> 7) & 0x01;
            v.vsys_ovp_flag = (raw_ >> 6) & 0x01;
            v.otg_ovp_flag = (raw_ >> 5) & 0x01;
            v.otg_uvp_flag = (raw_ >> 4) & 0x01;
            v.tshut_flag = (raw_ >> 2) & 0x01;
            return v;
        }

        void set_raw(uint8_t raw) { raw_ = raw; }
        uint8_t get_raw() const { return raw_; }
        
    private:
        uint8_t raw_ = 0;
    };

}