#include "status/bq2579x-status.hpp"
#include <esp_log.h>

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
        esp_err_t STATUS::get_charger_status0()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_status0.reg_addr, val));
        charger_status0.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_status1()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_status1.reg_addr, val));
        charger_status1.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_status2()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_status2.reg_addr, val));
        charger_status2.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_status3()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_status3.reg_addr, val));
        charger_status3.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_status4()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_status4.reg_addr, val));
        charger_status4.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_fault_status0()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(fault_status0.reg_addr, val));
        fault_status0.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_fault_status1()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(fault_status1.reg_addr, val));
        fault_status1.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_flag0()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_flag0.reg_addr, val));
        charger_flag0.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_flag1()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_flag1.reg_addr, val));
        charger_flag1.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_flag2()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_flag2.reg_addr, val));
        charger_flag2.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_charger_flag3()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(charger_flag3.reg_addr, val));
        charger_flag3.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_fault_flag0()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(fault_flag0.reg_addr, val));
        fault_flag0.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_fault_flag1()
    {
        uint8_t val;
        RETURN_IF_ERROR(read_u8(fault_flag1.reg_addr, val));
        fault_flag1.set_raw(val);
        return ESP_OK;
    }

    esp_err_t STATUS::get_flags()
    {
        RETURN_IF_ERROR(get_charger_flag0());
        RETURN_IF_ERROR(get_charger_flag1());
        RETURN_IF_ERROR(get_charger_flag2());
        RETURN_IF_ERROR(get_charger_flag3());
        RETURN_IF_ERROR(get_fault_flag0());
        RETURN_IF_ERROR(get_fault_flag1());
        return ESP_OK;
    }

    esp_err_t STATUS::get_status()
    {
        RETURN_IF_ERROR(get_charger_status0());
        RETURN_IF_ERROR(get_charger_status1());
        RETURN_IF_ERROR(get_charger_status2());
        RETURN_IF_ERROR(get_charger_status3());
        RETURN_IF_ERROR(get_charger_status4());
        RETURN_IF_ERROR(get_fault_status0());
        RETURN_IF_ERROR(get_fault_status1());
        return ESP_OK;
    }

    void STATUS::log() const
    {
        charger_status0.log();
        charger_status1.log();
        charger_status2.log();
        charger_status3.log();
        charger_status4.log();
        fault_status0.log();
        fault_status1.log();
    }

    std::string STATUS::to_json() const
    {
        return std::string("{") +
               "\"charger_status0\": " + charger_status0.to_json() + "," +
               "\"charger_status1\": " + charger_status1.to_json() + "," +
               "\"charger_status2\": " + charger_status2.to_json() + "," +
               "\"charger_status3\": " + charger_status3.to_json() + "," +
               "\"charger_status4\": " + charger_status4.to_json() + "," +
               "\"fault_status0\": " + fault_status0.to_json() + "," +
               "\"fault_status1\": " + fault_status1.to_json() +
               "}";
    }

} // namespace bq2579x
