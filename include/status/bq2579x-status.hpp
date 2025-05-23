#pragma once

#include "status/bq2579x-status_types.hpp"
#include "status/bq2579x-flags_types.hpp"

#include "bq2579x-interface.hpp"

namespace bq2579x
{
    static_assert(std::is_class<INTERFACE>::value, "INTERFACE is not a class");
    class STATUS : public INTERFACE
    {
    public:
        explicit STATUS(I2CDevices &dev) : INTERFACE(dev) {}

        ChargerStatus0Register charger_status0 = {};
        ChargerStatus1Register charger_status1 = {};
        ChargerStatus2Register charger_status2 = {};
        ChargerStatus3Register charger_status3 = {};
        ChargerStatus4Register charger_status4 = {};
        FaultStatus0Register   fault_status0 = {};
        FaultStatus1Register   fault_status1 = {};

        ChargerFlag0Register charger_flag0 = {};
        ChargerFlag1Register charger_flag1 = {};
        ChargerFlag2Register charger_flag2 = {};
        ChargerFlag3Register charger_flag3 = {};
        FaultFlag0Register   fault_flag0 = {};
        FaultFlag1Register   fault_flag1 = {};

        esp_err_t get_charger_status0();
        esp_err_t get_charger_status1();
        esp_err_t get_charger_status2();
        esp_err_t get_charger_status3();
        esp_err_t get_charger_status4();
        esp_err_t get_fault_status0();
        esp_err_t get_fault_status1();

        esp_err_t get_charger_flag0();
        esp_err_t get_charger_flag1();
        esp_err_t get_charger_flag2();
        esp_err_t get_charger_flag3();
        esp_err_t get_fault_flag0();
        esp_err_t get_fault_flag1();

        esp_err_t get_flags();
        esp_err_t get_status();

        void log() const;
        std::string to_json() const;

    private:
        inline static const char *TAG = "BQ2579X_STATUS";
    };

} // namespace bq2579x