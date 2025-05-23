#include "ctrl/bq2579x-ctrl.hpp"

#include "esp_log.h"

#define RETURN_IF_ERROR(x)                       \
    do                                           \
    {                                            \
        esp_err_t __err_rc = (x);                \
        if (__err_rc != ESP_OK)                  \
        {                                        \
            ESP_LOGE("RETURN_IF_ERROR",          \
                     "%s failed at %s:%d → %s",  \
                     #x, __FILE__, __LINE__,     \
                     esp_err_to_name(__err_rc)); \
            return __err_rc;                     \
        }                                        \
    } while (0)

namespace bq2579x
{
    esp_err_t CTRL::ready()
    {
        uint8_t val;
        Part_Information_Register part_information;
        RETURN_IF_ERROR(read_u8(part_information.reg_addr, val));
        part_information.set_raw(val);

        if (part_information.get_values().part_number != VALUE_DEVICE_ID)

            return ESP_ERR_INVALID_RESPONSE;
        return ESP_OK;
    }

    esp_err_t CTRL::send_reset()
    {
        uint8_t control;
        RETURN_IF_ERROR(read_u8(REG_RESET, control));
        control |= RESET_COMMAND;
        RETURN_IF_ERROR(write_u8(REG_RESET, control));
        return ESP_OK;
    }

    esp_err_t CTRL::en_adc()
    {
        uint8_t control;
        RETURN_IF_ERROR(read_u8(REG_ADC_CONTROL, control));
        control |= EN_ADC_COMMAND;
        RETURN_IF_ERROR(write_u8(REG_ADC_CONTROL, control));
        return ESP_OK;
    }

    esp_err_t CTRL::get_ico_current_limit()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(ico_current_limit_ma.reg_addr, val));
        ico_current_limit_ma.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_ibus_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(ibus_adc_ma.reg_addr, val));
        ibus_adc_ma.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_ibat_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(ibat_adc_ma.reg_addr, val));
        ibat_adc_ma.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_vbus_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(vbus_adc_mv.reg_addr, val));
        vbus_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_vac1_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(vac1_adc_mv.reg_addr, val));
        vac1_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_vacd2_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(vacd2_adc_mv.reg_addr, val));
        vacd2_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_vbat_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(vbat_adc_mv.reg_addr, val));
        vbat_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_vsys_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(vsys_adc_mv.reg_addr, val));
        vsys_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_ts_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(ts_adc_mp.reg_addr, val));
        ts_adc_mp.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_tdie_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(tdie_adc_dc.reg_addr, val));
        tdie_adc_dc.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_dplus_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(dplus_adc_mv.reg_addr, val));
        dplus_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get_dminus_adc()
    {
        uint16_t val;
        RETURN_IF_ERROR(read_u16(dminus_adc_mv.reg_addr, val));
        dminus_adc_mv.set_raw(val);
        return ESP_OK;
    }

    esp_err_t CTRL::get()
    {
        RETURN_IF_ERROR(get_ico_current_limit());
        RETURN_IF_ERROR(get_ibus_adc());
        RETURN_IF_ERROR(get_ibat_adc());
        RETURN_IF_ERROR(get_vbus_adc());
        RETURN_IF_ERROR(get_vac1_adc());
        RETURN_IF_ERROR(get_vacd2_adc());
        RETURN_IF_ERROR(get_vbat_adc());
        RETURN_IF_ERROR(get_vsys_adc());
        RETURN_IF_ERROR(get_ts_adc());
        RETURN_IF_ERROR(get_tdie_adc());
        RETURN_IF_ERROR(get_dplus_adc());
        RETURN_IF_ERROR(get_dminus_adc());
        return ESP_OK;
    }

    void CTRL::log() const
    {
        ESP_LOGI("BQ2579X_CTRL", "ICO_Current_Limit = %dmA", ico_current_limit_ma.get_value());

        ESP_LOGI("BQ2579X_CTRL", "ADC Readings:");
        ESP_LOGI("BQ2579X_CTRL", " IBUS  = %dmA", ibus_adc_ma.get_value());
        ESP_LOGI("BQ2579X_CTRL", " IBAT  = %dmA", ibat_adc_ma.get_value());
        ESP_LOGI("BQ2579X_CTRL", " VBUS  = %dmV", vbus_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " VAC1  = %dmV", vac1_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " VAC2  = %dmV", vacd2_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " VBAT  = %dmV", vbat_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " VSYS  = %dmV", vsys_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " TS    = %.3f %%", ts_adc_mp.get_value() / 1000.0f); // TS en millièmes de pourcent (par exemple 23200 -> 23.200%)
        ESP_LOGI("BQ2579X_CTRL", " TDIE  = %.1f °C", tdie_adc_dc.get_value() / 10.0f); // TDIE en dixièmes de degré (ex: 423 = 42.3 °C)
        ESP_LOGI("BQ2579X_CTRL", " D+    = %dmV", dplus_adc_mv.get_value());
        ESP_LOGI("BQ2579X_CTRL", " D-    = %dmV", dminus_adc_mv.get_value());
    }

    std::string CTRL::to_json() const
    {
        return std::string("{") +
               "\"ico_current_ma\": " + std::to_string(ico_current_limit_ma.get_value()) + "," +
               "\"ibus_ma\": " + std::to_string(ibus_adc_ma.get_value()) + "," +
               "\"ibat_ma\": " + std::to_string(ibat_adc_ma.get_value()) + "," +
               "\"vbus_mv\": " + std::to_string(vbus_adc_mv.get_value()) + "," +
               "\"vac1_mv\": " + std::to_string(vac1_adc_mv.get_value()) + "," +
               "\"vac2_mv\": " + std::to_string(vacd2_adc_mv.get_value()) + "," +
               "\"vbat_mv\": " + std::to_string(vbat_adc_mv.get_value()) + "," +
               "\"vsys_mv\": " + std::to_string(vsys_adc_mv.get_value()) + "," +
               "\"ts_celsius_pct\": " + std::to_string(ts_adc_mp.get_value() / 1000.0f) + "," +
               "\"tdie_celsius\": " + std::to_string(tdie_adc_dc.get_value() / 10.0f) + "," +
               "\"dplus_mv\": " + std::to_string(dplus_adc_mv.get_value()) + "," +
               "\"dminus_mv\": " + std::to_string(dminus_adc_mv.get_value()) +
               "}";
    }

} // namespace bq2579x
