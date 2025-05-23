#include "config/bq2579x-config_mask_types.hpp"
#include <esp_log.h>

namespace bq2579x
{

    void ChargerMask0Register::set_values(const ChargerMask0Register::Values &v)
    {
        raw_ = (v.iindpm_mask ? 1 << 7 : 0) | (v.vindpm_mask ? 1 << 6 : 0) | (v.wd_mask ? 1 << 5 : 0) | (v.poorsrc_mask ? 1 << 4 : 0) | (v.pg_mask ? 1 << 3 : 0) | (v.ac2_present_mask ? 1 << 2 : 0) | (v.ac1_present_mask ? 1 << 1 : 0) | (v.vbus_present_mask ? 1 : 0);
    }

    ChargerMask0Register::Values ChargerMask0Register::get_values() const
    {
        Values v;
        v.iindpm_mask = (raw_ >> 7) & 0x01;
        v.vindpm_mask = (raw_ >> 6) & 0x01;
        v.wd_mask = (raw_ >> 5) & 0x01;
        v.poorsrc_mask = (raw_ >> 4) & 0x01;
        v.pg_mask = (raw_ >> 3) & 0x01;
        v.ac2_present_mask = (raw_ >> 2) & 0x01;
        v.ac1_present_mask = (raw_ >> 1) & 0x01;
        v.vbus_present_mask = raw_ & 0x01;
        return v;
    }

    void ChargerMask1Register::set_values(const ChargerMask1Register::Values &v)
    {
        raw_ = (v.chg_mask ? 1 << 7 : 0) | (v.ico_mask ? 1 << 6 : 0) | (v.vbus_mask ? 1 << 4 : 0) | (v.treg_mask ? 1 << 2 : 0) | (v.vbat_present_mask ? 1 << 1 : 0) | (v.bc1_2_done_mask ? 1 : 0);
    }

    void ChargerMask0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X)  RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " IINDPM_MASK=%d VINDPM_MASK=%d WD_MASK=%d POORSRC_MASK=%d PG_MASK=%d AC2_PRESENT_MASK=%d AC1_PRESENT_MASK=%d VBUS_PRESENT_MASK=%d",
                 v.iindpm_mask, v.vindpm_mask, v.wd_mask, v.poorsrc_mask, v.pg_mask, v.ac2_present_mask, v.ac1_present_mask, v.vbus_present_mask);
    }

    std::string ChargerMask0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"IINDPM_MASK\": " + std::to_string(v.iindpm_mask) + "," +
               "\"VINDPM_MASK\": " + std::to_string(v.vindpm_mask) + "," +
               "\"WD_MASK\": " + std::to_string(v.wd_mask) + "," +
               "\"POORSRC_MASK\": " + std::to_string(v.poorsrc_mask) + "," +
               "\"PG_MASK\": " + std::to_string(v.pg_mask) + "," +
               "\"AC2_PRESENT_MASK\": " + std::to_string(v.ac2_present_mask) + "," +
               "\"AC1_PRESENT_MASK\": " + std::to_string(v.ac1_present_mask) + "," +
               "\"VBUS_PRESENT_MASK\": " + std::to_string(v.vbus_present_mask) +
               "}";
    }

    ChargerMask1Register::Values ChargerMask1Register::get_values() const
    {
        Values v;
        v.chg_mask = (raw_ >> 7) & 0x01;
        v.ico_mask = (raw_ >> 6) & 0x01;
        v.vbus_mask = (raw_ >> 4) & 0x01;
        v.treg_mask = (raw_ >> 2) & 0x01;
        v.vbat_present_mask = (raw_ >> 1) & 0x01;
        v.bc1_2_done_mask = raw_ & 0x01;
        return v;
    }

    void ChargerMask2Register::set_values(const ChargerMask2Register::Values &v)
    {
        raw_ = (v.dpdm_done_mask ? 1 << 6 : 0) | (v.adc_done_mask ? 1 << 5 : 0) | (v.vsys_mask ? 1 << 4 : 0) | (v.chg_tmr_mask ? 1 << 3 : 0) | (v.trichg_tmr_mask ? 1 << 2 : 0) | (v.prechg_tmr_mask ? 1 << 1 : 0) | (v.topoff_tmr_mask ? 1 : 0);
    }

    void ChargerMask1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " CHG_MASK=%d ICO_MASK=%d VBUS_MASK=%d TREG_MASK=%d VBAT_PRESENT_MASK=%d BC1_2_DONE_MASK=%d",
                 v.chg_mask, v.ico_mask, v.vbus_mask, v.treg_mask, v.vbat_present_mask, v.bc1_2_done_mask);
    }

    std::string ChargerMask1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"CHG_MASK\": " + std::to_string(v.chg_mask) + "," +
               "\"ICO_MASK\": " + std::to_string(v.ico_mask) + "," +
               "\"VBUS_MASK\": " + std::to_string(v.vbus_mask) + "," +
               "\"TREG_MASK\": " + std::to_string(v.treg_mask) + "," +
               "\"VBAT_PRESENT_MASK\": " + std::to_string(v.vbat_present_mask) + "," +
               "\"BC1_2_DONE_MASK\": " + std::to_string(v.bc1_2_done_mask) +
               "}";
    }

    ChargerMask2Register::Values ChargerMask2Register::get_values() const
    {
        Values v;
        v.dpdm_done_mask = (raw_ >> 6) & 0x01;
        v.adc_done_mask = (raw_ >> 5) & 0x01;
        v.vsys_mask = (raw_ >> 4) & 0x01;
        v.chg_tmr_mask = (raw_ >> 3) & 0x01;
        v.trichg_tmr_mask = (raw_ >> 2) & 0x01;
        v.prechg_tmr_mask = (raw_ >> 1) & 0x01;
        v.topoff_tmr_mask = raw_ & 0x01;
        return v;
    }

    void ChargerMask3Register::set_values(const ChargerMask3Register::Values &v)
    {
        raw_ = (v.vbatotg_low_mask ? 1 << 4 : 0) | (v.ts_cold_mask ? 1 << 3 : 0) | (v.ts_cool_mask ? 1 << 2 : 0) | (v.ts_warm_mask ? 1 << 1 : 0) | (v.ts_hot_mask ? 1 : 0);
    }

    void ChargerMask2Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " DPDM_DONE_MASK=%d ADC_DONE_MASK=%d VSYS_MASK=%d CHG_TMR_MASK=%d TRICHG_TMR_MASK=%d PRECHG_TMR_MASK=%d TOPOFF_TMR_MASK=%d",
                 v.dpdm_done_mask, v.adc_done_mask, v.vsys_mask, v.chg_tmr_mask, v.trichg_tmr_mask, v.prechg_tmr_mask, v.topoff_tmr_mask);
    }

    std::string ChargerMask2Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"DPDM_DONE_MASK\": " + std::to_string(v.dpdm_done_mask) + "," +
               "\"ADC_DONE_MASK\": " + std::to_string(v.adc_done_mask) + "," +
               "\"VSYS_MASK\": " + std::to_string(v.vsys_mask) + "," +
               "\"CHG_TMR_MASK\": " + std::to_string(v.chg_tmr_mask) + "," +
               "\"TRICHG_TMR_MASK\": " + std::to_string(v.trichg_tmr_mask) + "," +
               "\"PRECHG_TMR_MASK\": " + std::to_string(v.prechg_tmr_mask) + "," +
               "\"TOPOFF_TMR_MASK\": " + std::to_string(v.topoff_tmr_mask) +
               "}";
    }

    ChargerMask3Register::Values ChargerMask3Register::get_values() const
    {
        Values v;
        v.vbatotg_low_mask = (raw_ >> 4) & 0x01;
        v.ts_cold_mask = (raw_ >> 3) & 0x01;
        v.ts_cool_mask = (raw_ >> 2) & 0x01;
        v.ts_warm_mask = (raw_ >> 1) & 0x01;
        v.ts_hot_mask = raw_ & 0x01;
        return v;
    }

    void ChargerMask3Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " VBATOTG_LOW_MASK=%d TS_COLD_MASK=%d TS_COOL_MASK=%d TS_WARM_MASK=%d TS_HOT_MASK=%d",
                 v.vbatotg_low_mask, v.ts_cold_mask, v.ts_cool_mask, v.ts_warm_mask, v.ts_hot_mask);
    }

    std::string ChargerMask3Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"VBATOTG_LOW_MASK\": " + std::to_string(v.vbatotg_low_mask) + "," +
               "\"TS_COLD_MASK\": " + std::to_string(v.ts_cold_mask) + "," +
               "\"TS_COOL_MASK\": " + std::to_string(v.ts_cool_mask) + "," +
               "\"TS_WARM_MASK\": " + std::to_string(v.ts_warm_mask) + "," +
               "\"TS_HOT_MASK\": " + std::to_string(v.ts_hot_mask) +
               "}";
    }

    void FaultMask0Register::set_values(const FaultMask0Register::Values &v)
    {
        raw_ = (v.ibat_reg_mask ? 1 << 7 : 0) | (v.vbus_ovp_mask ? 1 << 6 : 0) | (v.vbat_ovp_mask ? 1 << 5 : 0) | (v.ibus_ocp_mask ? 1 << 4 : 0) | (v.ibat_ocp_mask ? 1 << 3 : 0) | (v.conv_ocp_mask ? 1 << 2 : 0) | (v.vac2_ovp_mask ? 1 << 1 : 0) | (v.vac1_ovp_mask ? 1 : 0);
    }

    FaultMask0Register::Values FaultMask0Register::get_values() const
    {
        Values v;
        v.ibat_reg_mask = (raw_ >> 7) & 0x01;
        v.vbus_ovp_mask = (raw_ >> 6) & 0x01;
        v.vbat_ovp_mask = (raw_ >> 5) & 0x01;
        v.ibus_ocp_mask = (raw_ >> 4) & 0x01;
        v.ibat_ocp_mask = (raw_ >> 3) & 0x01;
        v.conv_ocp_mask = (raw_ >> 2) & 0x01;
        v.vac2_ovp_mask = (raw_ >> 1) & 0x01;
        v.vac1_ovp_mask = raw_ & 0x01;
        return v;
    }

    void FaultMask0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " IBAT_REG_MASK=%d VBUS_OVP_MASK=%d VBAT_OVP_MASK=%d IBUS_OCP_MASK=%d IBAT_OCP_MASK=%d CONV_OCP_MASK=%d VAC2_OVP_MASK=%d VAC1_OVP_MASK=%d",
                 v.ibat_reg_mask, v.vbus_ovp_mask, v.vbat_ovp_mask, v.ibus_ocp_mask, v.ibat_ocp_mask, v.conv_ocp_mask, v.vac2_ovp_mask, v.vac1_ovp_mask);
    }

    std::string FaultMask0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"IBAT_REG_MASK\": " + std::to_string(v.ibat_reg_mask) + "," +
               "\"VBUS_OVP_MASK\": " + std::to_string(v.vbus_ovp_mask) + "," +
               "\"VBAT_OVP_MASK\": " + std::to_string(v.vbat_ovp_mask) + "," +
               "\"IBUS_OCP_MASK\": " + std::to_string(v.ibus_ocp_mask) + "," +
               "\"IBAT_OCP_MASK\": " + std::to_string(v.ibat_ocp_mask) + "," +
               "\"CONV_OCP_MASK\": " + std::to_string(v.conv_ocp_mask) + "," +
               "\"VAC2_OVP_MASK\": " + std::to_string(v.vac2_ovp_mask) + "," +
               "\"VAC1_OVP_MASK\": " + std::to_string(v.vac1_ovp_mask) +
               "}";
    }

    void FaultMask1Register::set_values(const FaultMask1Register::Values &v)
    {
        raw_ = (v.vsys_short_mask ? 1 << 7 : 0) | (v.vsys_ovp_mask ? 1 << 6 : 0) | (v.otg_ovp_mask ? 1 << 5 : 0) | (v.otg_uvp_mask ? 1 << 4 : 0) | (v.tshut_mask ? 1 << 2 : 0);
        // bits 3, 1, 0 sont réservés (forcés à 0)
    }

    FaultMask1Register::Values FaultMask1Register::get_values() const
    {
        Values v;
        v.vsys_short_mask = (raw_ >> 7) & 0x01;
        v.vsys_ovp_mask = (raw_ >> 6) & 0x01;
        v.otg_ovp_mask = (raw_ >> 5) & 0x01;
        v.otg_uvp_mask = (raw_ >> 4) & 0x01;
        v.tshut_mask = (raw_ >> 2) & 0x01;
        return v;
    }

    void FaultMask1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, " (0x%02X) RAW : 0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " VSYS_SHORT_MASK=%d VSYS_OVP_MASK=%d OTG_OVP_MASK=%d OTG_UVP_MASK=%d TSHUT_MASK=%d",
                 v.vsys_short_mask, v.vsys_ovp_mask, v.otg_ovp_mask, v.otg_uvp_mask, v.tshut_mask);
    }

    std::string FaultMask1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"VSYS_SHORT_MASK\": " + std::to_string(v.vsys_short_mask) + "," +
               "\"VSYS_OVP_MASK\": " + std::to_string(v.vsys_ovp_mask) + "," +
               "\"OTG_OVP_MASK\": " + std::to_string(v.otg_ovp_mask) + "," +
               "\"OTG_UVP_MASK\": " + std::to_string(v.otg_uvp_mask) + "," +
               "\"TSHUT_MASK\": " + std::to_string(v.tshut_mask) +
               "}";
    }

    void ChargerMaskRegister::log() const
    {
        charger_mask0.log();
        charger_mask1.log();
        charger_mask2.log();
        charger_mask3.log();
    };

    std::string ChargerMaskRegister::to_json() const
    {
        return std::string("{") +
               "\"charger_mask0\": " + charger_mask0.to_json() + "," +
               "\"charger_mask1\": " + charger_mask1.to_json() + "," +
               "\"charger_mask2\": " + charger_mask2.to_json() + "," +
               "\"charger_mask3\": " + charger_mask3.to_json() +
               "}";
    }

    void FaultMaskRegister::log() const
    {
        fault_mask0.log();
        fault_mask1.log();
    };

    std::string FaultMaskRegister::to_json() const
    {
        return std::string("{") +
               "\"fault_mask0\": " + fault_mask0.to_json() + "," +
               "\"fault_mask1\": " + fault_mask1.to_json() +
               "}";
    }

    void ConfigMask::log() const
    {
        charger_mask.log();
        fault_mask.log();
    };

    std::string ConfigMask::to_json() const
    {
        return std::string("{") +
               "\"charger_mask\": " + charger_mask.to_json() + "," +
               "\"fault_mask\": " + fault_mask.to_json() +
               "}";
    }

}