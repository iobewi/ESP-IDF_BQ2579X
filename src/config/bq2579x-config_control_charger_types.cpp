#include "config/bq2579x-config_control_charger_types.hpp"
#include <esp_log.h>

namespace bq2579x
{
    void ChargerControl0Register::set_values(const ChargerControl0Register::Values &v)
    {
        raw_ = (v.en_auto_ibatdis ? 1 << 7 : 0) | (v.force_ibatdis ? 1 << 6 : 0) | (v.en_chg ? 1 << 5 : 0) | (v.en_ico ? 1 << 4 : 0) | (v.force_ico ? 1 << 3 : 0) | (v.en_hiz ? 1 << 2 : 0) | (v.en_term ? 1 << 1 : 0) | (v.en_backup ? 1 : 0);
    }

    ChargerControl0Register::Values ChargerControl0Register::get_values() const
    {
        Values v;
        v.en_auto_ibatdis = (raw_ >> 7) & 0x01;
        v.force_ibatdis = (raw_ >> 6) & 0x01;
        v.en_chg = (raw_ >> 5) & 0x01;
        v.en_ico = (raw_ >> 4) & 0x01;
        v.force_ico = (raw_ >> 3) & 0x01;
        v.en_hiz = (raw_ >> 2) & 0x01;
        v.en_term = (raw_ >> 1) & 0x01;
        v.en_backup = raw_ & 0x01;
        return v;
    }

    void ChargerControl1Register::set_values(const ChargerControl1Register::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.vbus_backup) << 6) | (static_cast<uint8_t>(v.vac_ovp) << 4) | (v.wd_rst ? 1 << 3 : 0) | (static_cast<uint8_t>(v.watchdog) & 0x07);
    }

    void ChargerControl0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " EN_AUTO_IBATDIS : %d", v.en_auto_ibatdis);
        ESP_LOGI(TAG, " FORCE_IBATDIS   : %d", v.force_ibatdis);
        ESP_LOGI(TAG, " EN_CHG          : %d", v.en_chg);
        ESP_LOGI(TAG, " EN_ICO          : %d", v.en_ico);
        ESP_LOGI(TAG, " FORCE_ICO       : %d", v.force_ico);
        ESP_LOGI(TAG, " EN_HIZ          : %d", v.en_hiz);
        ESP_LOGI(TAG, " EN_TERM         : %d", v.en_term);
        ESP_LOGI(TAG, " EN_BACKUP       : %d", v.en_backup);
    }

    std::string ChargerControl0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"EN_AUTO_IBATDIS\": " + std::to_string(v.en_auto_ibatdis) + "," +
               "\"FORCE_IBATDIS\": " + std::to_string(v.force_ibatdis) + "," +
               "\"EN_CHG\": " + std::to_string(v.en_chg) + "," +
               "\"EN_ICO\": " + std::to_string(v.en_ico) + "," +
               "\"FORCE_ICO\": " + std::to_string(v.force_ico) + "," +
               "\"EN_HIZ\": " + std::to_string(v.en_hiz) + "," +
               "\"EN_TERM\": " + std::to_string(v.en_term) + "," +
               "\"EN_BACKUP\": " + std::to_string(v.en_backup) +
               "}";
    }

    ChargerControl1Register::Values ChargerControl1Register::get_values() const
    {
        Values v;
        v.vbus_backup = static_cast<VBUSBackupRatio>((raw_ >> 6) & 0x03);
        v.vac_ovp = static_cast<VACOVPThreshold>((raw_ >> 4) & 0x03);
        v.wd_rst = (raw_ >> 3) & 0x01;
        v.watchdog = static_cast<WatchdogTimeout>(raw_ & 0x07);
        return v;
    }

    const char *to_string(ChargerControl1Register::VBUSBackupRatio r)
    {
        using R = ChargerControl1Register::VBUSBackupRatio;
        switch (r)
        {
        case R::Ratio40:
            return "40% VINDPM";
        case R::Ratio60:
            return "60% VINDPM";
        case R::Ratio80:
            return "80% VINDPM";
        case R::Ratio100:
            return "100% VINDPM";
        default:
            return "Unknown";
        }
    }

    const char *to_string(ChargerControl1Register::VACOVPThreshold t)
    {
        using T = ChargerControl1Register::VACOVPThreshold;
        switch (t)
        {
        case T::V26:
            return "26 V";
        case T::V22:
            return "22 V";
        case T::V12:
            return "12 V";
        case T::V7:
            return "7 V";
        default:
            return "Unknown";
        }
    }

    const char *to_string(ChargerControl1Register::WatchdogTimeout t)
    {
        using T = ChargerControl1Register::WatchdogTimeout;
        switch (t)
        {
        case T::Disable:
            return "Disabled";
        case T::Sec0_5:
            return "0.5 s";
        case T::Sec1:
            return "1 s";
        case T::Sec2:
            return "2 s";
        case T::Sec20:
            return "20 s";
        case T::Sec40:
            return "40 s";
        case T::Sec80:
            return "80 s";
        case T::Sec160:
            return "160 s";
        default:
            return "Unknown";
        }
    }

    void ChargerControl1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " VBUS_BACKUP : %s", to_string(v.vbus_backup));
        ESP_LOGI(TAG, " VAC_OVP     : %s", to_string(v.vac_ovp));
        ESP_LOGI(TAG, " WD_RST      : %d", v.wd_rst);
        ESP_LOGI(TAG, " WATCHDOG    : %s", to_string(v.watchdog));
    }

    std::string ChargerControl1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"VBUS_BACKUP\": \"" + to_string(v.vbus_backup) + "\"," +
               "\"VAC_OVP\": \"" + to_string(v.vac_ovp) + "\"," +
               "\"WD_RST\": " + std::to_string(v.wd_rst) + "," +
               "\"WATCHDOG\": \"" + to_string(v.watchdog) + "\"" +
               "}";
    }

    void ChargerControl2Register::set_values(const ChargerControl2Register::Values &v)
    {
        raw_ = (v.force_indet ? 1 << 7 : 0) | (v.auto_indet_en ? 1 << 6 : 0) | (v.en_12v ? 1 << 5 : 0) | (v.en_9v ? 1 << 4 : 0) | (v.hvdcp_en ? 1 << 3 : 0) | (static_cast<uint8_t>(v.sdrv_ctrl) << 1) | (v.sdrv_dly ? 1 : 0);
    }

    ChargerControl2Register::Values ChargerControl2Register::get_values() const
    {
        Values v;
        v.force_indet = (raw_ >> 7) & 0x01;
        v.auto_indet_en = (raw_ >> 6) & 0x01;
        v.en_12v = (raw_ >> 5) & 0x01;
        v.en_9v = (raw_ >> 4) & 0x01;
        v.hvdcp_en = (raw_ >> 3) & 0x01;
        v.sdrv_ctrl = static_cast<SFETControl>((raw_ >> 1) & 0x03);
        v.sdrv_dly = raw_ & 0x01;
        return v;
    }

    const char *to_string(ChargerControl2Register::SFETControl v)
    {
        using S = ChargerControl2Register::SFETControl;
        switch (v)
        {
        case S::Idle:
            return "Idle";
        case S::Shutdown:
            return "Shutdown";
        case S::Ship:
            return "Ship Mode";
        case S::Reset:
            return "Reset";
        default:
            return "Unknown";
        }
    }

    void ChargerControl2Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG,
                 " FORCE_INDET=%d AUTO_INDET_EN=%d EN_12V=%d EN_9V=%d HVDCP_EN=%d SDRV_DLY=%d",
                 v.force_indet,
                 v.auto_indet_en,
                 v.en_12v,
                 v.en_9v,
                 v.hvdcp_en,
                 v.sdrv_dly);
        ESP_LOGI(TAG, " SDRV_CTRL=%s", to_string(v.sdrv_ctrl));
    }

    std::string ChargerControl2Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"FORCE_INDET\": " + std::to_string(v.force_indet) + "," +
               "\"AUTO_INDET_EN\": " + std::to_string(v.auto_indet_en) + "," +
               "\"EN_12V\": " + std::to_string(v.en_12v) + "," +
               "\"EN_9V\": " + std::to_string(v.en_9v) + "," +
               "\"HVDCP_EN\": " + std::to_string(v.hvdcp_en) + "," +
               "\"SDRV_CTRL\": \"" + to_string(v.sdrv_ctrl) + "\"," +
               "\"SDRV_DLY\": " + std::to_string(v.sdrv_dly) +
               "}";
    }

    void ChargerControl3Register::set_values(const ChargerControl3Register::Values &v)
    {
        raw_ = (v.dis_acdrv ? 1 << 7 : 0) | (v.en_otg ? 1 << 6 : 0) | (v.pfm_otg_dis ? 1 << 5 : 0) | (v.pfm_fwd_dis ? 1 << 4 : 0) | (v.wkup_dly ? 1 << 3 : 0) | (v.dis_ldo ? 1 << 2 : 0) | (v.dis_otg_ooa ? 1 << 1 : 0) | (v.dis_fwd_ooa ? 1 : 0);
    }

    ChargerControl3Register::Values ChargerControl3Register::get_values() const
    {
        Values v;
        v.dis_acdrv = (raw_ >> 7) & 0x01;
        v.en_otg = (raw_ >> 6) & 0x01;
        v.pfm_otg_dis = (raw_ >> 5) & 0x01;
        v.pfm_fwd_dis = (raw_ >> 4) & 0x01;
        v.wkup_dly = (raw_ >> 3) & 0x01;
        v.dis_ldo = (raw_ >> 2) & 0x01;
        v.dis_otg_ooa = (raw_ >> 1) & 0x01;
        v.dis_fwd_ooa = raw_ & 0x01;
        return v;
    }

    void ChargerControl3Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG,
                 " DIS_ACDRV=%d EN_OTG=%d PFM_OTG_DIS=%d PFM_FWD_DIS=%d",
                 v.dis_acdrv,
                 v.en_otg,
                 v.pfm_otg_dis,
                 v.pfm_fwd_dis);
        ESP_LOGI(TAG,
                 " WKUP_DLY=%s DIS_LDO=%d DIS_OTG_OOA=%d DIS_FWD_OOA=%d",
                 v.wkup_dly ? "15 ms" : "1 s",
                 v.dis_ldo,
                 v.dis_otg_ooa,
                 v.dis_fwd_ooa);
    }

    std::string ChargerControl3Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"DIS_ACDRV\": " + std::to_string(v.dis_acdrv) + "," +
               "\"EN_OTG\": " + std::to_string(v.en_otg) + "," +
               "\"PFM_OTG_DIS\": " + std::to_string(v.pfm_otg_dis) + "," +
               "\"PFM_FWD_DIS\": " + std::to_string(v.pfm_fwd_dis) + "," +
               "\"WKUP_DLY\": \"" + std::string(v.wkup_dly ? "15 ms" : "1 s") + "\"," +
               "\"DIS_LDO\": " + std::to_string(v.dis_ldo) + "," +
               "\"DIS_OTG_OOA\": " + std::to_string(v.dis_otg_ooa) + "," +
               "\"DIS_FWD_OOA\": " + std::to_string(v.dis_fwd_ooa) +
               "}";
    }

    void ChargerControl4Register::set_values(const ChargerControl4Register::Values &v)
    {
        raw_ = (v.en_acdrv2 ? 1 << 7 : 0) | (v.en_acdrv1 ? 1 << 6 : 0) | (v.pwm_freq_750khz ? 1 << 5 : 0) | (v.dis_stat ? 1 << 4 : 0) | (v.dis_vsys_short ? 1 << 3 : 0) | (v.dis_votg_uvp ? 1 << 2 : 0) | (v.force_vindpm_det ? 1 << 1 : 0) | (v.en_ibus_ocp ? 1 : 0);
    }

    ChargerControl4Register::Values ChargerControl4Register::get_values() const
    {
        Values v;
        v.en_acdrv2 = (raw_ >> 7) & 0x01;
        v.en_acdrv1 = (raw_ >> 6) & 0x01;
        v.pwm_freq_750khz = (raw_ >> 5) & 0x01;
        v.dis_stat = (raw_ >> 4) & 0x01;
        v.dis_vsys_short = (raw_ >> 3) & 0x01;
        v.dis_votg_uvp = (raw_ >> 2) & 0x01;
        v.force_vindpm_det = (raw_ >> 1) & 0x01;
        v.en_ibus_ocp = raw_ & 0x01;
        return v;
    }

    void ChargerControl4Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG,
                 " EN_ACDRV2=%d EN_ACDRV1=%d PWM_750KHZ=%d DIS_STAT=%d DIS_VSYS_SHORT=%d DIS_VOTG_UVP=%d FORCE_VINDPM=%d EN_IBUS_OCP=%d",
                 v.en_acdrv2,
                 v.en_acdrv1,
                 v.pwm_freq_750khz,
                 v.dis_stat,
                 v.dis_vsys_short,
                 v.dis_votg_uvp,
                 v.force_vindpm_det,
                 v.en_ibus_ocp);
    }

    std::string ChargerControl4Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"EN_ACDRV2\": " + std::to_string(v.en_acdrv2) + "," +
               "\"EN_ACDRV1\": " + std::to_string(v.en_acdrv1) + "," +
               "\"PWM_750KHZ\": " + std::to_string(v.pwm_freq_750khz) + "," +
               "\"DIS_STAT\": " + std::to_string(v.dis_stat) + "," +
               "\"DIS_VSYS_SHORT\": " + std::to_string(v.dis_vsys_short) + "," +
               "\"DIS_VOTG_UVP\": " + std::to_string(v.dis_votg_uvp) + "," +
               "\"FORCE_VINDPM\": " + std::to_string(v.force_vindpm_det) + "," +
               "\"EN_IBUS_OCP\": " + std::to_string(v.en_ibus_ocp) +
               "}";
    }

    void ChargerControl5Register::set_values(const ChargerControl5Register::Values &v)
    {
        raw_ = (v.sfet_present ? 1 << 7 : 0) | (v.en_ibat ? 1 << 5 : 0) | (static_cast<uint8_t>(v.ibat_reg) << 3) | (v.en_iindpm ? 1 << 2 : 0) | (v.en_extilim ? 1 << 1 : 0) | (v.en_batoc ? 1 : 0);
    }

    ChargerControl5Register::Values ChargerControl5Register::get_values() const
    {
        Values v;
        v.sfet_present = (raw_ >> 7) & 0x01;
        v.en_ibat = (raw_ >> 5) & 0x01;
        v.ibat_reg = static_cast<IBATRegulation>((raw_ >> 3) & 0x03);
        v.en_iindpm = (raw_ >> 2) & 0x01;
        v.en_extilim = (raw_ >> 1) & 0x01;
        v.en_batoc = raw_ & 0x01;
        return v;
    }

    const char *to_string(ChargerControl5Register::IBATRegulation r)
    {
        using R = ChargerControl5Register::IBATRegulation;
        switch (r)
        {
        case R::A3:
            return "3 A";
        case R::A4:
            return "4 A";
        case R::A5:
            return "5 A";
        case R::A6:
            return "6 A";
        default:
            return "Unknown";
        }
    }

    void ChargerControl5Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG,
                 " SFET_PRESENT=%d EN_IBAT=%d EN_IINDPM=%d EN_EXTILIM=%d EN_BATOC=%d",
                 v.sfet_present,
                 v.en_ibat,
                 v.en_iindpm,
                 v.en_extilim,
                 v.en_batoc);
        ESP_LOGI(TAG, " IBAT_REG=%s", to_string(v.ibat_reg));
    }

    std::string ChargerControl5Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"SFET_PRESENT\": " + std::to_string(v.sfet_present) + "," +
               "\"EN_IBAT\": " + std::to_string(v.en_ibat) + "," +
               "\"EN_IINDPM\": " + std::to_string(v.en_iindpm) + "," +
               "\"EN_EXTILIM\": " + std::to_string(v.en_extilim) + "," +
               "\"EN_BATOC\": " + std::to_string(v.en_batoc) + "," +
               "\"IBAT_REG\": \"" + to_string(v.ibat_reg) + "\"" +
               "}";
    }

    void ChargerControlRegister::log() const
    {
        charger_control0.log();
        charger_control1.log();
        charger_control2.log();
        charger_control3.log();
        charger_control4.log();
        charger_control5.log();
    }

    std::string ChargerControlRegister::to_json() const
    {
        return std::string("{") +
               "\"charger_control0\": " + charger_control0.to_json() + "," +
               "\"charger_control1\": " + charger_control1.to_json() + "," +
               "\"charger_control2\": " + charger_control2.to_json() + "," +
               "\"charger_control3\": " + charger_control3.to_json() + "," +
               "\"charger_control4\": " + charger_control4.to_json() + "," +
               "\"charger_control5\": " + charger_control5.to_json() +
               "}";
    }
}