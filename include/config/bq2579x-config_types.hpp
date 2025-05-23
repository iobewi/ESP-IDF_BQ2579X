#pragma once

#include "config/bq2579x-config_adc_types.hpp"
#include "config/bq2579x-config_control_types.hpp"
#include "config/bq2579x-config_limit_types.hpp"
#include "config/bq2579x-config_mask_types.hpp"

namespace bq2579x
{
    struct ConfigParams
    {
        ConfigLimit limit = {};
        ConfigControl control = {};
        ConfigMask mask = {};
        ConfigADC adc = {};

        void log() const
        {
            limit.log();
            control.log();
            mask.log();
            adc.log();
        }

        std::string to_json() const
        {
            return std::string("{") +
                   "\"limit\": " + limit.to_json() + "," +
                   "\"control\": " + control.to_json() + "," +
                   "\"mask\": " + mask.to_json() + "," +
                   "\"adc\": " + adc.to_json() +
                   "}";
        }
    };
}