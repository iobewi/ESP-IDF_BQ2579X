#pragma once

#include <cstdint>
#include <string>

#include "config/bq2579x-config_types.hpp"
#include "bq2579x-interface.hpp"

namespace bq2579x
{
    class Config : public INTERFACE
    {
    public:
        Config(I2CDevices &dev,
               const ConfigParams &params = {});

        // REG00h - Minimal System Voltage (VSYSMIN)
        esp_err_t get_minimal_system_voltage();
        esp_err_t set_minimal_system_voltage();

        // REG01h - Charge Voltage Limit (VREG)
        esp_err_t get_charge_voltage_limit_register();
        esp_err_t set_charge_voltage_limit_register();

        // REG03h - Charge Current Limit (ICHG)
        esp_err_t get_charge_current_limit_register();
        esp_err_t set_charge_current_limit_register();

        // REG05h - Input Voltage Limit (VINDPM)
        esp_err_t get_input_voltage_limit_register();
        esp_err_t set_input_voltage_limit_register();

        // REG06h - Input Current Limit (IINDPM)
        esp_err_t get_input_current_limit_register();
        esp_err_t set_input_current_limit_register();

        // REG0Bh - VOTG Regulation
        esp_err_t get_votg_regulation_register();
        esp_err_t set_votg_regulation_register();

        // REG0Dh - IOTG Regulation
        esp_err_t get_iotg_regulation_register();
        esp_err_t set_iotg_regulation_register();

        // REG08h - Precharge Control
        esp_err_t get_precharge_control_register();
        esp_err_t set_precharge_control_register();

        // REG09h - Termination Control
        esp_err_t get_termination_control_register();
        esp_err_t set_termination_control_register();

        // REG0Ah - Re-charge Control
        esp_err_t get_recharge_control_register();
        esp_err_t set_recharge_control_register();

        // REG0Eh - Timer Control
        esp_err_t get_timer_control_register();
        esp_err_t set_timer_control_register();

        // REG0Fh - Charger Control 0
        esp_err_t get_charger_control_0_register();
        esp_err_t set_charger_control_0_register();

        // REG10h - Charger Control 1
        esp_err_t get_charger_control_1_register();
        esp_err_t set_charger_control_1_register();

        // REG11h - Charger Control 2
        esp_err_t get_charger_control_2_register();
        esp_err_t set_charger_control_2_register();

        // REG12h - Charger Control 3
        esp_err_t get_charger_control_3_register();
        esp_err_t set_charger_control_3_register();

        // REG13h - Charger Control 4
        esp_err_t get_charger_control_4_register();
        esp_err_t set_charger_control_4_register();

        // REG14h - Charger Control 5
        esp_err_t get_charger_control_5_register();
        esp_err_t set_charger_control_5_register();

        // REG15h - MPPT Control
        esp_err_t get_mppt_control_register();
        esp_err_t set_mppt_control_register();

        // REG16h - Temperature Control
        esp_err_t get_temperature_control_register();
        esp_err_t set_temperature_control_register();

        // REG17h - NTC Control 0
        esp_err_t get_ntc_control_0_register();
        esp_err_t set_ntc_control_0_register();

        // REG18h - NTC Control 1
        esp_err_t get_ntc_control_1_register();
        esp_err_t set_ntc_control_1_register();

        // REG28h - Charger Mask 0
        esp_err_t get_charger_mask_0_register();
        esp_err_t set_charger_mask_0_register();

        // REG29h - Charger Mask 1
        esp_err_t get_charger_mask_1_register();
        esp_err_t set_charger_mask_1_register();

        // REG2Ah - Charger Mask 2
        esp_err_t get_charger_mask_2_register();
        esp_err_t set_charger_mask_2_register();

        // REG2Bh - Charger Mask 3
        esp_err_t get_charger_mask_3_register();
        esp_err_t set_charger_mask_3_register();

        // REG2Ch - Fault Mask 0
        esp_err_t get_fault_mask_0_register();
        esp_err_t set_fault_mask_0_register();

        // REG2Dh - Fault Mask 1
        esp_err_t get_fault_mask_1_register();
        esp_err_t set_fault_mask_1_register();

        // REG2Eh - ADC Control
        esp_err_t get_adc_control_register();
        esp_err_t set_adc_control_register();

        // REG2Fh - ADC Function Disable 0
        esp_err_t get_adc_function_disable_0_register();
        esp_err_t set_adc_function_disable_0_register();

        // REG30h - ADC Function Disable 1
        esp_err_t get_adc_function_disable_1_register();
        esp_err_t set_adc_function_disable_1_register();

        // REG47h - DPDM Driver
        esp_err_t get_dpdm_driver_register();
        esp_err_t set_dpdm_driver_register();


        esp_err_t get_limit_registers();
        esp_err_t set_limit_registers();

        esp_err_t get_control_registers();
        esp_err_t set_control_registers();

        esp_err_t get_mask_registers();
        esp_err_t set_mask_registers();

        esp_err_t get_adc_registers();
        esp_err_t set_adc_registers();

        esp_err_t get();
        esp_err_t set();

        ConfigParams &datas() { return params_; };
        const ConfigParams &datas() const { return params_; };

    private:
        ConfigParams params_;
        inline static const char *TAG = "BQ2579X_CONFIG";
    };

} // namespace bq2579x
