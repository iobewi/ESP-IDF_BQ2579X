#include "config/bq2579x-config_control_ntc_types.hpp"
#include <esp_log.h>

namespace bq2579x
{
    void NTCControl0Register::set_values(const NTCControl0Register::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.jeita_vset) << 5) | (static_cast<uint8_t>(v.jeita_iseth) << 3) | (static_cast<uint8_t>(v.jeita_isetc) << 1);
    }

    NTCControl0Register::Values NTCControl0Register::get_values() const
    {
        Values v;
        v.jeita_vset = static_cast<JEITAVoltage>((raw_ >> 5) & 0x07);
        v.jeita_iseth = static_cast<JEITACurrent>((raw_ >> 3) & 0x03);
        v.jeita_isetc = static_cast<JEITACurrent>((raw_ >> 1) & 0x03);
        return v;
    }

    const char *to_string(NTCControl0Register::JEITAVoltage v)
    {
        using V = NTCControl0Register::JEITAVoltage;
        switch (v)
        {
        case V::Suspend:
            return "Suspend";
        case V::VREGm800mV:
            return "VREG -800 mV";
        case V::VREGm600mV:
            return "VREG -600 mV";
        case V::VREGm400mV:
            return "VREG -400 mV";
        case V::VREGm300mV:
            return "VREG -300 mV";
        case V::VREGm200mV:
            return "VREG -200 mV";
        case V::VREGm100mV:
            return "VREG -100 mV";
        case V::Unchanged:
            return "Unchanged";
        default:
            return "Unknown";
        }
    }

    const char *to_string(NTCControl0Register::JEITACurrent c)
    {
        using C = NTCControl0Register::JEITACurrent;
        switch (c)
        {
        case C::Suspend:
            return "Suspend";
        case C::Pct20:
            return "20%";
        case C::Pct40:
            return "40%";
        case C::Unchanged:
            return "Unchanged";
        default:
            return "Unknown";
        }
    }

    void NTCControl0Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " JEITA_VSET  : %s", to_string(v.jeita_vset));
        ESP_LOGI(TAG, " JEITA_ISETH : %s", to_string(v.jeita_iseth));
        ESP_LOGI(TAG, " JEITA_ISETC : %s", to_string(v.jeita_isetc));
    }

    std::string NTCControl0Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"JEITA_VSET\": \"" + to_string(v.jeita_vset) + "\"," +
               "\"JEITA_ISETH\": \"" + to_string(v.jeita_iseth) + "\"," +
               "\"JEITA_ISETC\": \"" + to_string(v.jeita_isetc) + "\"" +
               "}";
    }

    void NTCControl1Register::set_values(const NTCControl1Register::Values &v)
    {
        raw_ = (static_cast<uint8_t>(v.ts_cool) << 6) | (static_cast<uint8_t>(v.ts_warm) << 4) | (static_cast<uint8_t>(v.bhot) << 2) | (static_cast<uint8_t>(v.bcold) << 1) | (v.ts_ignore ? 1 : 0);
    }

    NTCControl1Register::Values NTCControl1Register::get_values() const
    {
        Values v;
        v.ts_cool = static_cast<TSCOOL>((raw_ >> 6) & 0x03);
        v.ts_warm = static_cast<TSWARM>((raw_ >> 4) & 0x03);
        v.bhot = static_cast<BHOT>((raw_ >> 2) & 0x03);
        v.bcold = static_cast<BCOLD>((raw_ >> 1) & 0x01);
        v.ts_ignore = raw_ & 0x01;
        return v;
    }

    const char *to_string(NTCControl1Register::TSCOOL v)
    {
        using T = NTCControl1Register::TSCOOL;
        switch (v)
        {
        case T::PCT_71_1:
            return "71.1% (~5°C)";
        case T::PCT_68_4:
            return "68.4% (~10°C)";
        case T::PCT_65_5:
            return "65.5% (~15°C)";
        case T::PCT_62_4:
            return "62.4% (~20°C)";
        default:
            return "Unknown";
        }
    }

    const char *to_string(NTCControl1Register::TSWARM v)
    {
        using T = NTCControl1Register::TSWARM;
        switch (v)
        {
        case T::PCT_48_4:
            return "48.4% (~40°C)";
        case T::PCT_44_8:
            return "44.8% (~45°C)";
        case T::PCT_41_2:
            return "41.2% (~50°C)";
        case T::PCT_37_7:
            return "37.7% (~55°C)";
        default:
            return "Unknown";
        }
    }

    const char *to_string(NTCControl1Register::BHOT v)
    {
        using T = NTCControl1Register::BHOT;
        switch (v)
        {
        case T::Deg55:
            return "55°C";
        case T::Deg60:
            return "60°C";
        case T::Deg65:
            return "65°C";
        case T::Disabled:
            return "Disabled";
        default:
            return "Unknown";
        }
    }

    const char *to_string(NTCControl1Register::BCOLD v)
    {
        using T = NTCControl1Register::BCOLD;
        switch (v)
        {
        case T::DegMinus10:
            return "-10°C";
        case T::DegMinus20:
            return "-20°C";
        default:
            return "Unknown";
        }
    }

    void NTCControl1Register::log() const
    {
        Values v = get_values();
        ESP_LOGI(TAG, "(0x%02X) RAW=0x%02X", reg_addr, raw_);
        ESP_LOGI(TAG, " TS_COOL  : %s", to_string(v.ts_cool));
        ESP_LOGI(TAG, " TS_WARM  : %s", to_string(v.ts_warm));
        ESP_LOGI(TAG, " BHOT     : %s", to_string(v.bhot));
        ESP_LOGI(TAG, " BCOLD    : %s", to_string(v.bcold));
        ESP_LOGI(TAG, " TS_IGNORE: %d", v.ts_ignore);
    }

    std::string NTCControl1Register::to_json() const
    {
        Values v = get_values();
        return std::string("{") +
               "\"value\": " + std::to_string(raw_) + "," +
               "\"TS_COOL\": \"" + to_string(v.ts_cool) + "\"," +
               "\"TS_WARM\": \"" + to_string(v.ts_warm) + "\"," +
               "\"BHOT\": \"" + to_string(v.bhot) + "\"," +
               "\"BCOLD\": \"" + to_string(v.bcold) + "\"," +
               "\"TS_IGNORE\": " + std::to_string(v.ts_ignore) +
               "}";
    }

    void NTCControlRegister::log() const
    {
        ntc_control0.log();
        ntc_control1.log();
    }

    std::string NTCControlRegister::to_json() const
    {
        return std::string("{") +
               "\"ntc_control0\": " + ntc_control0.to_json() + "," +
               "\"ntc_control1\": " + ntc_control1.to_json() +
               "}";
    }
}