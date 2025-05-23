#include "status/bq2579x-status_types.hpp"

#include <esp_log.h>

namespace bq2579x
{

    ChargerStatus0Register::Values ChargerStatus0Register::get_values() const
    {
        Values v;
        v.iindpm_stat = (raw_ >> 7) & 0x01;
        v.vindpm_stat = (raw_ >> 6) & 0x01;
        v.wd_stat = (raw_ >> 5) & 0x01;
        v.pg_stat = (raw_ >> 3) & 0x01;
        v.ac2_present = (raw_ >> 2) & 0x01;
        v.ac1_present = (raw_ >> 1) & 0x01;
        v.vbus_present = (raw_ >> 0) & 0x01;
        return v;
    }

    void ChargerStatus0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);

        std::string active_flags;
        if (v.iindpm_stat)
            active_flags += "IINDPM ";
        if (v.vindpm_stat)
            active_flags += "VINDPM ";
        if (v.wd_stat)
            active_flags += "WD ";
        if (v.pg_stat)
            active_flags += "PG ";
        if (v.ac2_present)
            active_flags += "AC2 ";
        if (v.ac1_present)
            active_flags += "AC1 ";
        if (v.vbus_present)
            active_flags += "VBUS ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Active Flags : %s", active_flags.c_str());
        }
        else
        {
            ESP_LOGI(TAG, " No active flags.");
        }
    }

    std::string ChargerStatus0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"iindpm\": " + (v.iindpm_stat ? "true" : "false") + "," +
               "\"vindpm\": " + (v.vindpm_stat ? "true" : "false") + "," +
               "\"wd\": " + (v.wd_stat ? "true" : "false") + "," +
               "\"pg\": " + (v.pg_stat ? "true" : "false") + "," +
               "\"ac2\": " + (v.ac2_present ? "true" : "false") + "," +
               "\"ac1\": " + (v.ac1_present ? "true" : "false") + "," +
               "\"vbus\": " + (v.vbus_present ? "true" : "false") +
               "}";
    }

    ChargerStatus1Register::Values ChargerStatus1Register::get_values() const
    {
        Values v;
        v.charge_status = static_cast<ChargeStatus>((raw_ >> 5) & 0b111);
        v.vbus_status = static_cast<VbusStatus>((raw_ >> 1) & 0b1111);
        v.bc12_done = raw_ & 0x01;
        return v;
    }

    const char *to_string(ChargerStatus1Register::ChargeStatus status)
    {
        using CS = ChargerStatus1Register::ChargeStatus;
        switch (status)
        {
        case CS::NotCharging:
            return "Not Charging";
        case CS::TrickleCharge:
            return "Trickle Charge";
        case CS::PreCharge:
            return "Pre-Charge";
        case CS::FastCharge:
            return "Fast Charge";
        case CS::TaperCharge:
            return "Taper Charge";
        case CS::Reserved:
            return "Reserved";
        case CS::TopOffCharge:
            return "Top-Off Charge";
        case CS::TerminationDone:
            return "Charge Termination Done";
        default:
            return "Unknown";
        }
    }

    const char *to_string(ChargerStatus1Register::VbusStatus status)
    {
        using VS = ChargerStatus1Register::VbusStatus;
        switch (status)
        {
        case VS::NoInput:
            return "No Input";
        case VS::USB_SDP:
            return "USB SDP (500mA)";
        case VS::USB_CDP:
            return "USB CDP (1.5A)";
        case VS::USB_DCP:
            return "USB DCP (3.25A)";
        case VS::AdjustableHV_DCP:
            return "Adjustable HV DCP (1.5A)";
        case VS::UnknownAdapter:
            return "Unknown Adapter (3A)";
        case VS::NonStandardAdapter:
            return "Non-Standard Adapter";
        case VS::OTGMode:
            return "OTG Mode";
        case VS::NotQualifiedAdapter:
            return "Not Qualified Adapter";
        case VS::Reserved_9:
            return "Reserved (0x9)";
        case VS::Reserved_A:
            return "Reserved (0xA)";
        case VS::DirectVBUS:
            return "Direct VBUS";
        case VS::BackupMode:
            return "Backup Mode";
        case VS::Reserved_D:
            return "Reserved (0xD)";
        case VS::Reserved_E:
            return "Reserved (0xE)";
        case VS::Reserved_F:
            return "Reserved (0xF)";
        default:
            return "Unknown";
        }
    }

    void ChargerStatus1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " Charge Status : %d (%s)", static_cast<uint8_t>(v.charge_status), to_string(v.charge_status));
        ESP_LOGI(TAG, " VBUS Status   : %d (%s)", static_cast<uint8_t>(v.vbus_status), to_string(v.vbus_status));
        if (v.bc12_done)
        {
            ESP_LOGI(TAG, " BC1.2 Done    : true");
        }
    }

    std::string ChargerStatus1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"charge_status\": \"" + to_string(v.charge_status) + "\"," +
               "\"vbus_status\": \"" + to_string(v.vbus_status) + "\"," +
               "\"bc12_done\": " + (v.bc12_done ? "true" : "false") +
               "}";
    }

    ChargerStatus2Register::Values ChargerStatus2Register::get_values() const
    {
        Values v;
        v.ico_status = static_cast<ICOStatus>((raw_ >> 6) & 0b11);
        v.treg_stat = (raw_ >> 2) & 0x01;
        v.dpdm_stat = (raw_ >> 1) & 0x01;
        v.vbat_present = raw_ & 0x01;
        return v;
    }

    const char *to_string(ChargerStatus2Register::ICOStatus status)
    {
        using IS = ChargerStatus2Register::ICOStatus;
        switch (status)
        {
        case IS::Disabled:
            return "Disabled";
        case IS::OptimizationInProgress:
            return "Optimization in Progress";
        case IS::MaxInputCurrentDetected:
            return "Max Input Current Detected";
        case IS::Reserved:
            return "Reserved";
        default:
            return "Unknown";
        }
    }

    void ChargerStatus2Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " ICO Status : %s", to_string(v.ico_status));
        std::string active_flags;
        if (v.treg_stat)
            active_flags += "TREG ";
        if (v.dpdm_stat)
            active_flags += "DPDM ";
        if (v.vbat_present)
            active_flags += "VBAT ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Flags       : %s", active_flags.c_str());
        }
    }

    std::string ChargerStatus2Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"ico_status\": \"" + to_string(v.ico_status) + "\"," +
               "\"treg\": " + (v.treg_stat ? "true" : "false") + "," +
               "\"dpdm\": " + (v.dpdm_stat ? "true" : "false") + "," +
               "\"vbat\": " + (v.vbat_present ? "true" : "false") +
               "}";
    }

    ChargerStatus3Register::Values ChargerStatus3Register::get_values() const
    {
        Values v;
        v.acrb2_stat = (raw_ >> 7) & 0x01;
        v.acrb1_stat = (raw_ >> 6) & 0x01;
        v.adc_done_stat = (raw_ >> 5) & 0x01;
        v.vsys_stat = (raw_ >> 4) & 0x01;
        v.chg_tmr_stat = (raw_ >> 3) & 0x01;
        v.trichg_tmr_stat = (raw_ >> 2) & 0x01;
        v.prechg_tmr_stat = (raw_ >> 1) & 0x01;
        return v;
    }

    void ChargerStatus3Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);

        std::string active_flags;
        if (v.acrb2_stat)
            active_flags += "ACRB2 ";
        if (v.acrb1_stat)
            active_flags += "ACRB1 ";
        if (v.adc_done_stat)
            active_flags += "ADC_DONE ";
        if (v.vsys_stat)
            active_flags += "VSYS ";
        if (v.chg_tmr_stat)
            active_flags += "CHG_TMR ";
        if (v.trichg_tmr_stat)
            active_flags += "TRICHG_TMR ";
        if (v.prechg_tmr_stat)
            active_flags += "PRECHG_TMR ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Flags       : %s", active_flags.c_str());
        }
    }

    std::string ChargerStatus3Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"acrb2\": " + (v.acrb2_stat ? "true" : "false") + "," +
               "\"acrb1\": " + (v.acrb1_stat ? "true" : "false") + "," +
               "\"adc_done\": " + (v.adc_done_stat ? "true" : "false") + "," +
               "\"vsys\": " + (v.vsys_stat ? "true" : "false") + "," +
               "\"chg_tmr\": " + (v.chg_tmr_stat ? "true" : "false") + "," +
               "\"trichg_tmr\": " + (v.trichg_tmr_stat ? "true" : "false") + "," +
               "\"prechg_tmr\": " + (v.prechg_tmr_stat ? "true" : "false") +
               "}";
    }

    ChargerStatus4Register::Values ChargerStatus4Register::get_values() const
    {
        Values v;
        v.vbatotg_low_stat = (raw_ >> 4) & 0x01;
        v.ts_cold_stat = (raw_ >> 3) & 0x01;
        v.ts_cool_stat = (raw_ >> 2) & 0x01;
        v.ts_warm_stat = (raw_ >> 1) & 0x01;
        v.ts_hot_stat = (raw_ >> 0) & 0x01;
        return v;
    }

    void ChargerStatus4Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);

        std::string active_flags;
        if (v.vbatotg_low_stat)
            active_flags += "VBATOTG_LOW ";
        if (v.ts_cold_stat)
            active_flags += "TS_COLD ";
        if (v.ts_cool_stat)
            active_flags += "TS_COOL ";
        if (v.ts_warm_stat)
            active_flags += "TS_WARM ";
        if (v.ts_hot_stat)
            active_flags += "TS_HOT ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Flags       : %s", active_flags.c_str());
        }
    }

    std::string ChargerStatus4Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"vbatotg_low\": " + (v.vbatotg_low_stat ? "true" : "false") + "," +
               "\"ts_cold\": " + (v.ts_cold_stat ? "true" : "false") + "," +
               "\"ts_cool\": " + (v.ts_cool_stat ? "true" : "false") + "," +
               "\"ts_warm\": " + (v.ts_warm_stat ? "true" : "false") + "," +
               "\"ts_hot\": " + (v.ts_hot_stat ? "true" : "false") +
               "}";
    }

    FaultStatus0Register::Values FaultStatus0Register::get_values() const
    {
        Values v;
        v.ibat_reg_stat = (raw_ >> 7) & 0x01;
        v.vbus_ovp_stat = (raw_ >> 6) & 0x01;
        v.vbat_ovp_stat = (raw_ >> 5) & 0x01;
        v.ibus_ocp_stat = (raw_ >> 4) & 0x01;
        v.ibat_ocp_stat = (raw_ >> 3) & 0x01;
        v.conv_ocp_stat = (raw_ >> 2) & 0x01;
        v.vac2_ovp_stat = (raw_ >> 1) & 0x01;
        v.vac1_ovp_stat = (raw_ >> 0) & 0x01;
        return v;
    }

    void FaultStatus0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);

        std::string active_flags;
        if (v.ibat_reg_stat)
            active_flags += "IBAT_REG ";
        if (v.vbus_ovp_stat)
            active_flags += "VBUS_OVP ";
        if (v.vbat_ovp_stat)
            active_flags += "VBAT_OVP ";
        if (v.ibus_ocp_stat)
            active_flags += "IBUS_OCP ";
        if (v.ibat_ocp_stat)
            active_flags += "IBAT_OCP ";
        if (v.conv_ocp_stat)
            active_flags += "CONV_OCP ";
        if (v.vac2_ovp_stat)
            active_flags += "VAC2_OVP ";
        if (v.vac1_ovp_stat)
            active_flags += "VAC1_OVP ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Faults      : %s", active_flags.c_str());
        }
    }

    std::string FaultStatus0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"ibat_reg\": " + (v.ibat_reg_stat ? "true" : "false") + "," +
               "\"vbus_ovp\": " + (v.vbus_ovp_stat ? "true" : "false") + "," +
               "\"vbat_ovp\": " + (v.vbat_ovp_stat ? "true" : "false") + "," +
               "\"ibus_ocp\": " + (v.ibus_ocp_stat ? "true" : "false") + "," +
               "\"ibat_ocp\": " + (v.ibat_ocp_stat ? "true" : "false") + "," +
               "\"conv_ocp\": " + (v.conv_ocp_stat ? "true" : "false") + "," +
               "\"vac2_ovp\": " + (v.vac2_ovp_stat ? "true" : "false") + "," +
               "\"vac1_ovp\": " + (v.vac1_ovp_stat ? "true" : "false") +
               "}";
    }

    FaultStatus1Register::Values FaultStatus1Register::get_values() const
    {
        Values v;
        v.vsys_short_stat = (raw_ >> 7) & 0x01;
        v.vsys_ovp_stat = (raw_ >> 6) & 0x01;
        v.otg_ovp_stat = (raw_ >> 5) & 0x01;
        v.otg_uvp_stat = (raw_ >> 4) & 0x01;
        v.tshut_stat = (raw_ >> 2) & 0x01;
        return v;
    }

    void FaultStatus1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);

        std::string active_flags;
        if (v.vsys_short_stat)
            active_flags += "VSYS_SHORT ";
        if (v.vsys_ovp_stat)
            active_flags += "VSYS_OVP ";
        if (v.otg_ovp_stat)
            active_flags += "OTG_OVP ";
        if (v.otg_uvp_stat)
            active_flags += "OTG_UVP ";
        if (v.tshut_stat)
            active_flags += "TSHUT ";

        if (!active_flags.empty())
        {
            ESP_LOGI(TAG, " Faults      : %s", active_flags.c_str());
        }
    }

    std::string FaultStatus1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"vsys_short\": " + (v.vsys_short_stat ? "true" : "false") + "," +
               "\"vsys_ovp\": " + (v.vsys_ovp_stat ? "true" : "false") + "," +
               "\"otg_ovp\": " + (v.otg_ovp_stat ? "true" : "false") + "," +
               "\"otg_uvp\": " + (v.otg_uvp_stat ? "true" : "false") + "," +
               "\"tshut\": " + (v.tshut_stat ? "true" : "false") +
               "}";
    }

}