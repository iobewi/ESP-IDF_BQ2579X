#include "config/bq2579x-config_macro.hpp"

namespace bq2579x
{
        ConfigParams load_config_from_kconfig()
        {
                ConfigParams params;

                // === Default Charging Parameters ===
                params.limit.vreg_mv.set_value(CONFIG_BQ25798_VREG_MV);
                params.limit.ichg_ma.set_value(CONFIG_BQ25798_ICHG_MA);
                // === Input Source Parameters ===
                params.limit.vindpm_mv.set_value(CONFIG_BQ25798_VINDPM_MV);
                params.limit.iindpm_ma.set_value(CONFIG_BQ25798_IINDPM_MA);
                params.limit.vsysmin_mv.set_value(CONFIG_BQ25798_VSYS_MIN_MV);

                // === OTG / Backup Mode Configuration ===
                params.limit.votg_mv.set_value(5000);
                bq2579x::IOTGRegulationRegister::Values iotg_regulation = {};
                iotg_regulation.otg_current_ma = 3000;
                iotg_regulation.precharge_timer_short = 0;
                params.limit.iotg_values.set_values(iotg_regulation);

                bq2579x::PrechargeControlRegister::Values precharge_control = {};
                precharge_control.precharge_current_ma = 120;
                precharge_control.threshold = bq2579x::PrechargeControlRegister::VBATLowThreshold::THRESH_714;
                params.control.pre_charge.set_values(precharge_control);

                bq2579x::TerminationControlRegister::Values termination_control = {};
                termination_control.iterm_ma = 200;
                params.control.termination.set_values(termination_control);

                bq2579x::RechargeControlRegister::Values recharge_control = {};
                recharge_control.cell_count = bq2579x::RechargeControlRegister::CellCount::Two;
                recharge_control.trechg = bq2579x::RechargeControlRegister::DeglitchTime::T_1024ms;
                recharge_control.vrechg_offset_mv = 150;
                params.control.re_charge.set_values(recharge_control);

                bq2579x::TimerControlRegister::Values timer_control = {};
                timer_control.topoff_timer = bq2579x::TimerControlRegister::TopOffTimer::Disabled;
                timer_control.en_chg_timer = 1;
                timer_control.en_prechg_timer = 1;
                timer_control.en_trichg_timer = 1;
                timer_control.chg_timer = bq2579x::TimerControlRegister::ChargeTimer::Hr12;
                timer_control.tmr2x_en = 1;
                params.control.timer.set_values(timer_control);

                bq2579x::ChargerControl0Register::Values charger_control0 = {};
                charger_control0.en_auto_ibatdis = 1;
                charger_control0.en_backup = 0;
                charger_control0.en_chg = 1;
                charger_control0.en_hiz = 0;
                charger_control0.en_ico = 0;
                charger_control0.en_term = 1;
                charger_control0.force_ibatdis = 0;
                charger_control0.force_ico = 0;
                params.control.charger.charger_control0.set_values(charger_control0);

                bq2579x::ChargerControl1Register::Values charger_control1 = {};
                charger_control1.vbus_backup = bq2579x::ChargerControl1Register::VBUSBackupRatio::Ratio80;
                charger_control1.vac_ovp = bq2579x::ChargerControl1Register::VACOVPThreshold::V26;
                charger_control1.wd_rst = false;
                charger_control1.watchdog = bq2579x::ChargerControl1Register::WatchdogTimeout::Sec40;
                params.control.charger.charger_control1.set_values(charger_control1);

                bq2579x::ChargerControl2Register::Values charger_control2 = {};
                charger_control2.force_indet = false;
                charger_control2.auto_indet_en = true;
                charger_control2.en_12v = false;
                charger_control2.en_9v = false;
                charger_control2.hvdcp_en = false;
                charger_control2.sdrv_ctrl = bq2579x::ChargerControl2Register::SFETControl::Idle;
                charger_control2.sdrv_dly = false;
                params.control.charger.charger_control2.set_values(charger_control2);

                bq2579x::ChargerControl3Register::Values charger_control3 = {};
                charger_control3.dis_acdrv = false;
                charger_control3.en_otg = false;
                charger_control3.pfm_otg_dis = false;
                charger_control3.pfm_fwd_dis = false;
                charger_control3.wkup_dly = false;
                charger_control3.dis_ldo = false;
                charger_control3.dis_otg_ooa = false;
                charger_control3.dis_fwd_ooa = false;
                params.control.charger.charger_control3.set_values(charger_control3);

                bq2579x::ChargerControl4Register::Values charger_control4 = {};
                charger_control4.en_acdrv2 = false;
                charger_control4.en_acdrv1 = false;
                charger_control4.pwm_freq_750khz = true;
                charger_control4.dis_stat = false;
                charger_control4.dis_vsys_short = false;
                charger_control4.dis_votg_uvp = false;
                charger_control4.force_vindpm_det = false;
                charger_control4.en_ibus_ocp = true;
                params.control.charger.charger_control4.set_values(charger_control4);

                bq2579x::ChargerControl5Register::Values charger_control5 = {};
                charger_control5.sfet_present = false;
                charger_control5.en_ibat = false;
                charger_control5.ibat_reg = bq2579x::ChargerControl5Register::IBATRegulation::A6;
                charger_control5.en_iindpm = true;
                charger_control5.en_extilim = true;
                charger_control5.en_batoc = false;
                params.control.charger.charger_control5.set_values(charger_control5);

                bq2579x::TemperatureControlRegister::Values temperature_control = {};
                temperature_control.treg = bq2579x::TemperatureControlRegister::ThermalRegulation::Deg120;
                temperature_control.tshut = bq2579x::TemperatureControlRegister::ThermalShutdown::Deg150;
                temperature_control.vbus_pd_en = false;
                temperature_control.vac1_pd_en = false;
                temperature_control.vac2_pd_en = false;
                temperature_control.bkup_acfet1_on = false;
                params.control.temperature.set_values(temperature_control);

                bq2579x::NTCControl0Register::Values ntc_control0 = {};
                ntc_control0.jeita_vset = bq2579x::NTCControl0Register::JEITAVoltage::VREGm400mV;
                ntc_control0.jeita_iseth = bq2579x::NTCControl0Register::JEITACurrent::Unchanged;
                ntc_control0.jeita_isetc = bq2579x::NTCControl0Register::JEITACurrent::Pct20;
                params.control.ntc.ntc_control0.set_values(ntc_control0);

                bq2579x::NTCControl1Register::Values ntc_control1 = {};
                ntc_control1.ts_cool = bq2579x::NTCControl1Register::TSCOOL::PCT_68_4;
                ntc_control1.ts_warm = bq2579x::NTCControl1Register::TSWARM::PCT_44_8;
                ntc_control1.bhot = bq2579x::NTCControl1Register::BHOT::Deg60;
                ntc_control1.bcold = bq2579x::NTCControl1Register::BCOLD::DegMinus10;
                ntc_control1.ts_ignore = false;
                params.control.ntc.ntc_control1.set_values(ntc_control1);

                bq2579x::ADCControlRegister::Values adc_control = {};
#if CONFIG_BQ25798_ADC_ENABLE
                adc_control.adc_enable = false;
#else
                adc_control.adc_enable = false;

#endif
                adc_control.sample_resolution = bq2579x::ADCControlRegister::ADCSampleResolution::RES_14_BIT;
                adc_control.average_enable = false;
                adc_control.average_init = false;
                adc_control.adc_rate_oneshot = true;
                params.adc.acd.set_values(adc_control);

                bq2579x::ADCFunctionDisable0Register::Values adc_function_disable0 = {};
#if CONFIG_BQ25798_ADC_VBAT
                adc_function_disable0.vbat_adc_disable = false;
#else
                adc_function_disable0.vbat_adc_disable = true;
#endif
#if CONFIG_BQ25798_ADC_IBAT
                adc_function_disable0.ibat_adc_disable = false;
#else
                adc_function_disable0.ibat_adc_disable = true;
#endif
#if CONFIG_BQ25798_ADC_VSYS
                adc_function_disable0.vsys_adc_disable = false;
#else
                adc_function_disable0.vsys_adc_disable = true;
#endif
#if CONFIG_BQ25798_ADC_VBUS
                adc_function_disable0.vbus_adc_disable = false;
#else
                adc_function_disable0.vbus_adc_disable = true;
#endif
#if CONFIG_BQ25798_ADC_IBUS
                adc_function_disable0.ibus_adc_disable = false;
#else
                adc_function_disable0.ibus_adc_disable = true;
#endif
#if CONFIG_BQ25798_ADC_TEMP
                adc_function_disable0.ts_adc_disable = false;
#else
                adc_function_disable0.ts_adc_disable = true;
#endif
                adc_function_disable0.tdie_adc_disable = false;
                params.adc.adc_function_disable.adc_function_disable0.set_values(adc_function_disable0);

                bq2579x::ADCFunctionDisable1Register::Values adc_function_disable1 = {};
                adc_function_disable1.dp_adc_disable = false;
                adc_function_disable1.dm_adc_disable = false;
                adc_function_disable1.vac2_adc_disable = false;
                adc_function_disable1.vac1_adc_disable = false;
                params.adc.adc_function_disable.adc_function_disable1.set_values(adc_function_disable1);

                bq2579x::MPPTControlRegister::Values mppt_control = {};
                mppt_control.voc_pct = bq2579x::MPPTControlRegister::VOCPct::PCT_0_8750;
                mppt_control.voc_dly = bq2579x::MPPTControlRegister::VOCDelay::Delay_300ms;
                mppt_control.voc_rate = bq2579x::MPPTControlRegister::VOCRate::Interval_2min;
                mppt_control.en_mppt = false;
                params.control.mppt.set_values(mppt_control);

                bq2579x::DPDMDriverRegister::Values dpdm_control = {};
                dpdm_control.dplus = bq2579x::DPDMDriverRegister::OutputLevel::HIZ;
                dpdm_control.dminus = bq2579x::DPDMDriverRegister::OutputLevel::HIZ;
                params.control.dpdm.set_values(dpdm_control);

                // === ADC Monitoring ===

                // === Application des registres ===

                return params;
        }
}
