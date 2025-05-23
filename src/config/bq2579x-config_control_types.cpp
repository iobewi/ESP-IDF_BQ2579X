#include "config/bq2579x-config_control_types.hpp"
#include <esp_log.h>

namespace bq2579x
{

    void PrechargeControlRegister::set_values(const PrechargeControlRegister::Values &v)
    {
        uint8_t iprechg = (v.precharge_current_ma / 40) & 0x3F;
        uint8_t vbat = (static_cast<uint8_t>(v.threshold) & 0x03) << 6;
        raw_ = vbat | iprechg;
    }

    PrechargeControlRegister::Values PrechargeControlRegister::get_values() const
    {
        Values v;
        v.precharge_current_ma = (raw_ & 0x3F) * 40;
        v.threshold = static_cast<VBATLowThreshold>((raw_ >> 6) & 0x03);
        return v;
    }

    const char *to_string(PrechargeControlRegister::VBATLowThreshold v)
    {
        using Thresh = PrechargeControlRegister::VBATLowThreshold;
        switch (v)
        {
        case Thresh::THRESH_15:
            return "15% VREG";
        case Thresh::THRESH_622:
            return "62.2% VREG";
        case Thresh::THRESH_667:
            return "66.7% VREG";
        case Thresh::THRESH_714:
            return "71.4% VREG";
        default:
            return "Unknown";
        }
    }

    void PrechargeControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " IPRECHG : %d mA", v.precharge_current_ma);
        ESP_LOGI(TAG, " VBAT_LOWV : %s", to_string(v.threshold));
    }

    std::string PrechargeControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"IPRECHG\": " + std::to_string(v.precharge_current_ma) + "," +
               "\"VBAT_LOWV\": \"" + to_string(v.threshold) + "\"" +
               "}";
    }

    void TerminationControlRegister::set_values(const TerminationControlRegister::Values &v)
    {
        uint8_t iterm = (v.iterm_ma / 40) & 0x1F;
        uint8_t wd = (v.stop_wd_chg ? 1 : 0) << 5;
        uint8_t rst = (v.reg_rst ? 1 : 0) << 6;
        raw_ = rst | wd | iterm;
    }

    TerminationControlRegister::Values TerminationControlRegister::get_values() const
    {
        Values v;
        v.iterm_ma = (raw_ & 0x1F) * 40;
        v.stop_wd_chg = (raw_ >> 5) & 0x01;
        v.reg_rst = (raw_ >> 6) & 0x01;
        return v;
    }

    void TerminationControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " REG_RST=%d STOP_WD_CHG=%d ITERM=%d mA",
                 v.reg_rst,
                 v.stop_wd_chg,
                 v.iterm_ma);
    }

    std::string TerminationControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"REG_RST\": " + std::to_string(v.reg_rst) + "," +
               "\"STOP_WD_CHG\": " + std::to_string(v.stop_wd_chg) + "," +
               "\"ITERM\": " + std::to_string(v.iterm_ma) +
               "}";
    }

    void RechargeControlRegister::set_values(const RechargeControlRegister::Values &v)
    {
        uint8_t cell = (static_cast<uint8_t>(v.cell_count) & 0x03) << 6;
        uint8_t tgl = (static_cast<uint8_t>(v.trechg) & 0x03) << 4;
        uint8_t off = (v.vrechg_offset_mv / 50) & 0x0F;
        raw_ = cell | tgl | off;
    }

    RechargeControlRegister::Values RechargeControlRegister::get_values() const
    {
        Values v;
        v.cell_count = static_cast<CellCount>((raw_ >> 6) & 0x03);
        v.trechg = static_cast<DeglitchTime>((raw_ >> 4) & 0x03);
        v.vrechg_offset_mv = (raw_ & 0x0F) * 50;
        return v;
    }

    const char *to_string(RechargeControlRegister::CellCount v)
    {
        switch (v)
        {
        case RechargeControlRegister::CellCount::One:
            return "1 Cell";
        case RechargeControlRegister::CellCount::Two:
            return "2 Cells";
        case RechargeControlRegister::CellCount::Three:
            return "3 Cells";
        case RechargeControlRegister::CellCount::Four:
            return "4 Cells";
        default:
            return "Unknown";
        }
    }

    const char *to_string(RechargeControlRegister::DeglitchTime v)
    {
        switch (v)
        {
        case RechargeControlRegister::DeglitchTime::T_64ms:
            return "64ms";
        case RechargeControlRegister::DeglitchTime::T_256ms:
            return "256ms";
        case RechargeControlRegister::DeglitchTime::T_1024ms:
            return "1024ms";
        case RechargeControlRegister::DeglitchTime::T_2048ms:
            return "2048ms";
        default:
            return "Unknown";
        }
    }
    void RechargeControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " Cell Count        : %s", to_string(v.cell_count));
        ESP_LOGI(TAG, " Deglitch Time     : %s", to_string(v.trechg));
        ESP_LOGI(TAG, " Recharge Offset   : %d mV", v.vrechg_offset_mv);
    }
    std::string RechargeControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"cell_count\": \"" + to_string(v.cell_count) + "\"," +
               "\"deglitch_time\": \"" + to_string(v.trechg) + "\"," +
               "\"vrechg_offset_mv\": " + std::to_string(v.vrechg_offset_mv) +
               "}";
    }

    void TimerControlRegister::set_values(const TimerControlRegister::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.topoff_timer) << 6) | (v.en_trichg_timer ? 1 << 5 : 0) | (v.en_prechg_timer ? 1 << 4 : 0) | (v.en_chg_timer ? 1 << 3 : 0) | (static_cast<uint8_t>(v.chg_timer) << 1) | (v.tmr2x_en ? 1 : 0);
    }

    TimerControlRegister::Values TimerControlRegister::get_values() const
    {
        Values v;
        v.topoff_timer = static_cast<TopOffTimer>((raw_ >> 6) & 0x03);
        v.en_trichg_timer = (raw_ >> 5) & 0x01;
        v.en_prechg_timer = (raw_ >> 4) & 0x01;
        v.en_chg_timer = (raw_ >> 3) & 0x01;
        v.chg_timer = static_cast<ChargeTimer>((raw_ >> 1) & 0x03);
        v.tmr2x_en = raw_ & 0x01;
        return v;
    }

    const char *to_string(TimerControlRegister::TopOffTimer t)
    {
        using T = TimerControlRegister::TopOffTimer;
        switch (t)
        {
        case T::Disabled:
            return "Disabled";
        case T::Min15:
            return "15 min";
        case T::Min30:
            return "30 min";
        case T::Min45:
            return "45 min";
        default:
            return "Unknown";
        }
    }

    const char *to_string(TimerControlRegister::ChargeTimer t)
    {
        using T = TimerControlRegister::ChargeTimer;
        switch (t)
        {
        case T::Hr5:
            return "5 h";
        case T::Hr8:
            return "8 h";
        case T::Hr12:
            return "12 h";
        case T::Hr24:
            return "24 h";
        default:
            return "Unknown";
        }
    }

    void TimerControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " TOPOFF_TMR  : %s", to_string(v.topoff_timer));
        ESP_LOGI(TAG, " EN_CHG_TMR  : %d", v.en_chg_timer);
        ESP_LOGI(TAG, " EN_PRECHG   : %d", v.en_prechg_timer);
        ESP_LOGI(TAG, " EN_TRICKLE  : %d", v.en_trichg_timer);
        ESP_LOGI(TAG, " CHG_TMR     : %s", to_string(v.chg_timer));
        ESP_LOGI(TAG, " TMR2X_EN    : %d", v.tmr2x_en);
    }

    std::string TimerControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"TOPOFF_TMR\": \"" + to_string(v.topoff_timer) + "\"," +
               "\"EN_CHG_TMR\": " + std::to_string(v.en_chg_timer) + "," +
               "\"EN_PRECHG\": " + std::to_string(v.en_prechg_timer) + "," +
               "\"EN_TRICKLE\": " + std::to_string(v.en_trichg_timer) + "," +
               "\"CHG_TMR\": \"" + to_string(v.chg_timer) + "\"," +
               "\"TMR2X_EN\": " + std::to_string(v.tmr2x_en) +
               "}";
    }

    void MPPTControlRegister::set_values(const MPPTControlRegister::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.voc_pct) << 5) | (static_cast<uint8_t>(v.voc_dly) << 3) | (static_cast<uint8_t>(v.voc_rate) << 1) | (v.en_mppt ? 1 : 0);
    }

    MPPTControlRegister::Values MPPTControlRegister::get_values() const
    {
        Values v;
        v.voc_pct = static_cast<VOCPct>((raw_ >> 5) & 0x07);
        v.voc_dly = static_cast<VOCDelay>((raw_ >> 3) & 0x03);
        v.voc_rate = static_cast<VOCRate>((raw_ >> 1) & 0x03);
        v.en_mppt = raw_ & 0x01;
        return v;
    }

    const char *to_string(MPPTControlRegister::VOCPct v)
    {
        using V = MPPTControlRegister::VOCPct;
        switch (v)
        {
        case V::PCT_0_5625:
            return "56.25%";
        case V::PCT_0_6250:
            return "62.5%";
        case V::PCT_0_6875:
            return "68.75%";
        case V::PCT_0_7500:
            return "75%";
        case V::PCT_0_8125:
            return "81.25%";
        case V::PCT_0_8750:
            return "87.5%";
        case V::PCT_0_9375:
            return "93.75%";
        case V::PCT_1_0000:
            return "100%";
        default:
            return "Unknown";
        }
    }

    const char *to_string(MPPTControlRegister::VOCDelay v)
    {
        using D = MPPTControlRegister::VOCDelay;
        switch (v)
        {
        case D::Delay_50ms:
            return "50 ms";
        case D::Delay_300ms:
            return "300 ms";
        case D::Delay_2s:
            return "2 s";
        case D::Delay_5s:
            return "5 s";
        default:
            return "Unknown";
        }
    }

    const char *to_string(MPPTControlRegister::VOCRate v)
    {
        using R = MPPTControlRegister::VOCRate;
        switch (v)
        {
        case R::Interval_30s:
            return "30 s";
        case R::Interval_2min:
            return "2 min";
        case R::Interval_10min:
            return "10 min";
        case R::Interval_30min:
            return "30 min";
        default:
            return "Unknown";
        }
    }

    void MPPTControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " VOC_PCT  : %s", to_string(v.voc_pct));
        ESP_LOGI(TAG, " VOC_DLY  : %s", to_string(v.voc_dly));
        ESP_LOGI(TAG, " VOC_RATE : %s", to_string(v.voc_rate));
        ESP_LOGI(TAG, " EN_MPPT  : %d", v.en_mppt);
    }

    std::string MPPTControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"VOC_PCT\": \"" + to_string(v.voc_pct) + "\"," +
               "\"VOC_DLY\": \"" + to_string(v.voc_dly) + "\"," +
               "\"VOC_RATE\": \"" + to_string(v.voc_rate) + "\"," +
               "\"EN_MPPT\": " + std::to_string(v.en_mppt) +
               "}";
    }

    void TemperatureControlRegister::set_values(const TemperatureControlRegister::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.treg) << 6) | (static_cast<uint8_t>(v.tshut) << 4) | (v.vbus_pd_en ? 1 << 3 : 0) | (v.vac1_pd_en ? 1 << 2 : 0) | (v.vac2_pd_en ? 1 << 1 : 0) | (v.bkup_acfet1_on ? 1 : 0);
    }

    TemperatureControlRegister::Values TemperatureControlRegister::get_values() const
    {
        Values v;
        v.treg = static_cast<ThermalRegulation>((raw_ >> 6) & 0x03);
        v.tshut = static_cast<ThermalShutdown>((raw_ >> 4) & 0x03);
        v.vbus_pd_en = (raw_ >> 3) & 0x01;
        v.vac1_pd_en = (raw_ >> 2) & 0x01;
        v.vac2_pd_en = (raw_ >> 1) & 0x01;
        v.bkup_acfet1_on = raw_ & 0x01;
        return v;
    }

    const char *to_string(TemperatureControlRegister::ThermalRegulation r)
    {
        using T = TemperatureControlRegister::ThermalRegulation;
        switch (r)
        {
        case T::Deg60:
            return "60 °C";
        case T::Deg80:
            return "80 °C";
        case T::Deg100:
            return "100 °C";
        case T::Deg120:
            return "120 °C";
        default:
            return "Unknown";
        }
    }

    const char *to_string(TemperatureControlRegister::ThermalShutdown s)
    {
        using S = TemperatureControlRegister::ThermalShutdown;
        switch (s)
        {
        case S::Deg150:
            return "150 °C";
        case S::Deg130:
            return "130 °C";
        case S::Deg120:
            return "120 °C";
        case S::Deg85:
            return "85 °C";
        default:
            return "Unknown";
        }
    }

    void TemperatureControlRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " THERM_REG : %s", to_string(v.treg));
        ESP_LOGI(TAG, " THERM_SHDN: %s", to_string(v.tshut));
        ESP_LOGI(TAG,
                 " VBUS_PD_EN=%d VAC1_PD_EN=%d VAC2_PD_EN=%d BKUP_ACFET1_ON=%d",
                 v.vbus_pd_en,
                 v.vac1_pd_en,
                 v.vac2_pd_en,
                 v.bkup_acfet1_on);
    }

    std::string TemperatureControlRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"THERM_REG\": \"" + to_string(v.treg) + "\"," +
               "\"THERM_SHDN\": \"" + to_string(v.tshut) + "\"," +
               "\"VBUS_PD_EN\": " + std::to_string(v.vbus_pd_en) + "," +
               "\"VAC1_PD_EN\": " + std::to_string(v.vac1_pd_en) + "," +
               "\"VAC2_PD_EN\": " + std::to_string(v.vac2_pd_en) + "," +
               "\"BKUP_ACFET1_ON\": " + std::to_string(v.bkup_acfet1_on) +
               "}";
    }

    void DPDMDriverRegister::set_values(const DPDMDriverRegister::Values &v)
    {
        raw_ = ((static_cast<uint8_t>(v.dplus) & 0x07) << 5) |
               ((static_cast<uint8_t>(v.dminus) & 0x07) << 2);
    }

    DPDMDriverRegister::Values DPDMDriverRegister::get_values() const
    {
        Values v;
        v.dplus = static_cast<OutputLevel>((raw_ >> 5) & 0x07);
        v.dminus = static_cast<OutputLevel>((raw_ >> 2) & 0x07);
        return v;
    }

    const char *to_string(DPDMDriverRegister::OutputLevel level)
    {
        using L = DPDMDriverRegister::OutputLevel;
        switch (level)
        {
        case L::HIZ:
            return "Hi-Z";
        case L::VOLT_0V:
            return "0 V";
        case L::VOLT_0V6:
            return "0.6 V";
        case L::VOLT_1V2:
            return "1.2 V";
        case L::VOLT_2V0:
            return "2.0 V";
        case L::VOLT_2V7:
            return "2.7 V";
        case L::VOLT_3V3:
            return "3.3 V";
        case L::DP_DM_SHORT:
            return "Short (DP only)";
        default:
            return "Unknown";
        }
    }

    void DPDMDriverRegister::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " D+ Level : %s", to_string(v.dplus));
        ESP_LOGI(TAG, " D- Level : %s", to_string(v.dminus));
    }

    std::string DPDMDriverRegister::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"DP_LEVEL\": \"" + to_string(v.dplus) + "\"," +
               "\"DM_LEVEL\": \"" + to_string(v.dminus) + "\"" +
               "}";
    }

    void ConfigControl::log() const
    {
        pre_charge.log();
        termination.log();
        re_charge.log();
        timer.log();
        charger.log();
        mppt.log();
        temperature.log();
        ntc.log();
        dpdm.log();
    }

    std::string ConfigControl::to_json() const
    {
        return std::string("{") +
               "\"pre_charge\": " + pre_charge.to_json() + "," +
               "\"termination\": " + termination.to_json() + "," +
               "\"re_charge\": " + re_charge.to_json() + "," +
               "\"timer\": " + timer.to_json() + "," +
               "\"charger\": " + charger.to_json() + "," +
               "\"mppt\": " + mppt.to_json() + "," +
               "\"temperature\": " + temperature.to_json() + "," +
               "\"ntc\": " + ntc.to_json() + "," +
               "\"dpdm\": " + dpdm.to_json() +
               "}";
    }

}