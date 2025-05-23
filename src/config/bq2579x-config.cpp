#include "config/bq2579x-config.hpp"
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
    Config::Config(I2CDevices &dev, const ConfigParams &params)
        : INTERFACE(dev),
          params_(params)
    {
    }
    esp_err_t Config::get_minimal_system_voltage()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.limit.vsysmin_mv.reg_addr, raw));
        params_.limit.vsysmin_mv.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_minimal_system_voltage()
    {
        uint8_t raw = params_.limit.vsysmin_mv.get_raw();
        RETURN_IF_ERROR(write_u8(params_.limit.vsysmin_mv.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charge_voltage_limit_register()
    {
        uint16_t raw = 0;
        RETURN_IF_ERROR(read_u16(params_.limit.vreg_mv.reg_addr, raw));
        params_.limit.vreg_mv.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charge_voltage_limit_register()
    {
        uint16_t raw = params_.limit.vreg_mv.get_raw();
        RETURN_IF_ERROR(write_u16(params_.limit.vreg_mv.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charge_current_limit_register()
    {
        uint16_t raw = 0;
        RETURN_IF_ERROR(read_u16(params_.limit.ichg_ma.reg_addr, raw));
        params_.limit.ichg_ma.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charge_current_limit_register()
    {
        uint16_t raw = params_.limit.ichg_ma.get_raw();
        RETURN_IF_ERROR(write_u16(params_.limit.ichg_ma.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_input_voltage_limit_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.limit.vindpm_mv.reg_addr, raw));
        params_.limit.vindpm_mv.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_input_voltage_limit_register()
    {
        uint8_t raw = params_.limit.vindpm_mv.get_raw();
        RETURN_IF_ERROR(write_u8(params_.limit.vindpm_mv.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_input_current_limit_register()
    {
        uint16_t raw = 0;
        RETURN_IF_ERROR(read_u16(params_.limit.iindpm_ma.reg_addr, raw));
        params_.limit.iindpm_ma.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_input_current_limit_register()
    {
        uint16_t raw = params_.limit.iindpm_ma.get_raw();
        RETURN_IF_ERROR(write_u16(params_.limit.iindpm_ma.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_votg_regulation_register()
    {
        uint16_t raw = 0;
        RETURN_IF_ERROR(read_u16(params_.limit.votg_mv.reg_addr, raw));
        params_.limit.votg_mv.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_votg_regulation_register()
    {
        uint16_t raw = params_.limit.votg_mv.get_raw();
        RETURN_IF_ERROR(write_u16(params_.limit.votg_mv.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_iotg_regulation_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.limit.iotg_values.reg_addr, raw));
        params_.limit.iotg_values.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_iotg_regulation_register()
    {
        uint8_t raw = params_.limit.iotg_values.get_raw();
        RETURN_IF_ERROR(write_u8(params_.limit.iotg_values.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_precharge_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.pre_charge.reg_addr, raw));
        params_.control.pre_charge.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_precharge_control_register()
    {
        uint8_t raw = params_.control.pre_charge.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.pre_charge.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_termination_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.termination.reg_addr, raw));
        params_.control.termination.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_termination_control_register()
    {
        uint8_t raw = params_.control.termination.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.termination.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_recharge_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.re_charge.reg_addr, raw));
        params_.control.re_charge.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_recharge_control_register()
    {
        uint8_t raw = params_.control.re_charge.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.re_charge.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_timer_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.timer.reg_addr, raw));
        params_.control.timer.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_timer_control_register()
    {
        uint8_t raw = params_.control.timer.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.timer.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_0_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control0.reg_addr, raw));
        params_.control.charger.charger_control0.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_0_register()
    {
        uint8_t raw = params_.control.charger.charger_control0.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control0.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_1_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control1.reg_addr, raw));
        params_.control.charger.charger_control1.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_1_register()
    {
        uint8_t raw = params_.control.charger.charger_control1.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control1.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_2_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control2.reg_addr, raw));
        params_.control.charger.charger_control2.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_2_register()
    {
        uint8_t raw = params_.control.charger.charger_control2.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control2.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_3_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control3.reg_addr, raw));
        params_.control.charger.charger_control3.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_3_register()
    {
        uint8_t raw = params_.control.charger.charger_control3.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control3.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_4_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control4.reg_addr, raw));
        params_.control.charger.charger_control4.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_4_register()
    {
        uint8_t raw = params_.control.charger.charger_control4.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control4.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_control_5_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.charger.charger_control5.reg_addr, raw));
        params_.control.charger.charger_control5.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_control_5_register()
    {
        uint8_t raw = params_.control.charger.charger_control5.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.charger.charger_control5.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_mppt_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.mppt.reg_addr, raw));
        params_.control.mppt.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_mppt_control_register()
    {
        uint8_t raw = params_.control.mppt.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.mppt.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_temperature_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.temperature.reg_addr, raw));
        params_.control.temperature.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_temperature_control_register()
    {
        uint8_t raw = params_.control.temperature.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.temperature.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_ntc_control_0_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.ntc.ntc_control0.reg_addr, raw));
        params_.control.ntc.ntc_control0.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_ntc_control_0_register()
    {
        uint8_t raw = params_.control.ntc.ntc_control0.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.ntc.ntc_control0.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_ntc_control_1_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.ntc.ntc_control1.reg_addr, raw));
        params_.control.ntc.ntc_control1.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_ntc_control_1_register()
    {
        uint8_t raw = params_.control.ntc.ntc_control1.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.ntc.ntc_control1.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_mask_0_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.charger_mask.charger_mask0.reg_addr, raw));
        params_.mask.charger_mask.charger_mask0.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_mask_0_register()
    {
        uint8_t raw = params_.mask.charger_mask.charger_mask0.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.charger_mask.charger_mask0.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_mask_1_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.charger_mask.charger_mask1.reg_addr, raw));
        params_.mask.charger_mask.charger_mask1.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_mask_1_register()
    {
        uint8_t raw = params_.mask.charger_mask.charger_mask1.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.charger_mask.charger_mask1.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_mask_2_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.charger_mask.charger_mask2.reg_addr, raw));
        params_.mask.charger_mask.charger_mask2.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_mask_2_register()
    {
        uint8_t raw = params_.mask.charger_mask.charger_mask2.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.charger_mask.charger_mask2.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_charger_mask_3_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.charger_mask.charger_mask3.reg_addr, raw));
        params_.mask.charger_mask.charger_mask3.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_charger_mask_3_register()
    {
        uint8_t raw = params_.mask.charger_mask.charger_mask3.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.charger_mask.charger_mask3.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_fault_mask_0_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.fault_mask.fault_mask0.reg_addr, raw));
        params_.mask.fault_mask.fault_mask0.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_fault_mask_0_register()
    {
        uint8_t raw = params_.mask.fault_mask.fault_mask0.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.fault_mask.fault_mask0.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_fault_mask_1_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.mask.fault_mask.fault_mask1.reg_addr, raw));
        params_.mask.fault_mask.fault_mask1.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_fault_mask_1_register()
    {
        uint8_t raw = params_.mask.fault_mask.fault_mask1.get_raw();
        RETURN_IF_ERROR(write_u8(params_.mask.fault_mask.fault_mask1.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_adc_control_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.adc.acd.reg_addr, raw));
        params_.adc.acd.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_adc_control_register()
    {
        uint8_t raw = params_.adc.acd.get_raw();
        RETURN_IF_ERROR(write_u8(params_.adc.acd.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_adc_function_disable_0_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.adc.adc_function_disable.adc_function_disable0.reg_addr, raw));
        params_.adc.adc_function_disable.adc_function_disable0.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_adc_function_disable_0_register()
    {
        uint8_t raw = params_.adc.adc_function_disable.adc_function_disable0.get_raw();
        RETURN_IF_ERROR(write_u8(params_.adc.adc_function_disable.adc_function_disable0.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_adc_function_disable_1_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.adc.adc_function_disable.adc_function_disable1.reg_addr, raw));
        params_.adc.adc_function_disable.adc_function_disable1.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_adc_function_disable_1_register()
    {
        uint8_t raw = params_.adc.adc_function_disable.adc_function_disable1.get_raw();
        RETURN_IF_ERROR(write_u8(params_.adc.adc_function_disable.adc_function_disable1.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_dpdm_driver_register()
    {
        uint8_t raw = 0;
        RETURN_IF_ERROR(read_u8(params_.control.dpdm.reg_addr, raw));
        params_.control.dpdm.set_raw(raw);
        return ESP_OK;
    }

    esp_err_t Config::set_dpdm_driver_register()
    {
        uint8_t raw = params_.control.dpdm.get_raw();
        RETURN_IF_ERROR(write_u8(params_.control.dpdm.reg_addr, raw));
        return ESP_OK;
    }

    esp_err_t Config::get_limit_registers()
    {
        RETURN_IF_ERROR(get_minimal_system_voltage());
        RETURN_IF_ERROR(get_charge_voltage_limit_register());
        RETURN_IF_ERROR(get_charge_current_limit_register());
        RETURN_IF_ERROR(get_input_voltage_limit_register());
        RETURN_IF_ERROR(get_input_current_limit_register());
        RETURN_IF_ERROR(get_votg_regulation_register());
        RETURN_IF_ERROR(get_iotg_regulation_register());
        return ESP_OK;
    }

    esp_err_t Config::set_limit_registers()
    {
        RETURN_IF_ERROR(set_minimal_system_voltage());
        RETURN_IF_ERROR(set_charge_voltage_limit_register());
        RETURN_IF_ERROR(set_charge_current_limit_register());
        RETURN_IF_ERROR(set_input_voltage_limit_register());
        RETURN_IF_ERROR(set_input_current_limit_register());
        RETURN_IF_ERROR(set_votg_regulation_register());
        RETURN_IF_ERROR(set_iotg_regulation_register());
        return ESP_OK;
    }

    esp_err_t Config::get_control_registers()
    {
        RETURN_IF_ERROR(get_precharge_control_register());
        RETURN_IF_ERROR(get_termination_control_register());
        RETURN_IF_ERROR(get_recharge_control_register());
        RETURN_IF_ERROR(get_timer_control_register());
        RETURN_IF_ERROR(get_charger_control_0_register());
        RETURN_IF_ERROR(get_charger_control_1_register());
        RETURN_IF_ERROR(get_charger_control_2_register());
        RETURN_IF_ERROR(get_charger_control_3_register());
        RETURN_IF_ERROR(get_charger_control_4_register());
        RETURN_IF_ERROR(get_charger_control_5_register());
        RETURN_IF_ERROR(get_mppt_control_register());
        RETURN_IF_ERROR(get_temperature_control_register());
        RETURN_IF_ERROR(get_ntc_control_0_register());
        RETURN_IF_ERROR(get_ntc_control_1_register());
        RETURN_IF_ERROR(get_dpdm_driver_register());
        return ESP_OK;
    }

    esp_err_t Config::set_control_registers()
    {
        RETURN_IF_ERROR(set_precharge_control_register());
        RETURN_IF_ERROR(set_termination_control_register());
        RETURN_IF_ERROR(set_recharge_control_register());
        RETURN_IF_ERROR(set_timer_control_register());
        RETURN_IF_ERROR(set_charger_control_0_register());
        RETURN_IF_ERROR(set_charger_control_1_register());
        RETURN_IF_ERROR(set_charger_control_2_register());
        RETURN_IF_ERROR(set_charger_control_3_register());
        RETURN_IF_ERROR(set_charger_control_4_register());
        RETURN_IF_ERROR(set_charger_control_5_register());
        RETURN_IF_ERROR(set_mppt_control_register());
        RETURN_IF_ERROR(set_temperature_control_register());
        RETURN_IF_ERROR(set_ntc_control_0_register());
        RETURN_IF_ERROR(set_ntc_control_1_register());
        RETURN_IF_ERROR(set_dpdm_driver_register());
        return ESP_OK;
    }

    esp_err_t Config::get_mask_registers()
    {
        RETURN_IF_ERROR(get_charger_mask_0_register());
        RETURN_IF_ERROR(get_charger_mask_1_register());
        RETURN_IF_ERROR(get_charger_mask_2_register());
        RETURN_IF_ERROR(get_charger_mask_3_register());
        RETURN_IF_ERROR(get_fault_mask_0_register());
        RETURN_IF_ERROR(get_fault_mask_1_register());
        return ESP_OK;
    }

    esp_err_t Config::set_mask_registers()
    {
        RETURN_IF_ERROR(set_charger_mask_0_register());
        RETURN_IF_ERROR(set_charger_mask_1_register());
        RETURN_IF_ERROR(set_charger_mask_2_register());
        RETURN_IF_ERROR(set_charger_mask_3_register());
        RETURN_IF_ERROR(set_fault_mask_0_register());
        RETURN_IF_ERROR(set_fault_mask_1_register());
        return ESP_OK;
    }

    esp_err_t Config::get_adc_registers()
    {
        RETURN_IF_ERROR(get_adc_control_register());
        RETURN_IF_ERROR(get_adc_function_disable_0_register());
        RETURN_IF_ERROR(get_adc_function_disable_1_register());
        return ESP_OK;
    }

    esp_err_t Config::set_adc_registers()
    {
        RETURN_IF_ERROR(set_adc_control_register());
        RETURN_IF_ERROR(set_adc_function_disable_0_register());
        RETURN_IF_ERROR(set_adc_function_disable_1_register());
        return ESP_OK;
    }

    esp_err_t Config::get()
    {
        RETURN_IF_ERROR(get_limit_registers());
        RETURN_IF_ERROR(get_control_registers());
        RETURN_IF_ERROR(get_mask_registers());
        RETURN_IF_ERROR(get_adc_registers());
        return ESP_OK;
    }

    esp_err_t Config::set()
    {
        RETURN_IF_ERROR(set_limit_registers());
        RETURN_IF_ERROR(set_control_registers());
        RETURN_IF_ERROR(set_mask_registers());
        RETURN_IF_ERROR(set_adc_registers());
        return ESP_OK;
    }

}