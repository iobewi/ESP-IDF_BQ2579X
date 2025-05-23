#include "config/bq2579x-config_macro.hpp"
//#include "config/bq2579x-config_types.hpp"
#include "bq2579x.hpp"
#include "sdkconfig.h"

#define RETURN_IF_ERROR(x)         \
    do {                           \
        esp_err_t __err_rc = (x);  \
        if (__err_rc != ESP_OK) {  \
            return __err_rc;       \
        }                          \
    } while (0)

#define HANDLE_OUTPUT(format, obj)                            \
    do {                                                      \
        switch (format)                                       \
        {                                                     \
            case OutputFormat::Log:                           \
                obj.log();                                    \
                break;                                        \
            case OutputFormat::JSON:                          \
                printf("%s\n", obj.to_json().c_str());        \
                break;                                        \
            case OutputFormat::None:                          \
            default:                                          \
                break;                                        \
        }                                                     \
    } while (0)


namespace bq2579x
{

    inline esp_err_t return_if_not_ready(bool ready, const char* tag)
    {
        if (!ready)
        {
            ESP_LOGE(tag, "Tentative d’utilisation sans initialisation préalable");
            return ESP_ERR_INVALID_STATE;
        }
        return ESP_OK;
    }

    BQ2579XManager::BQ2579XManager(I2CDevices &i2c)
        : i2c_(i2c),
          cfg_(i2c_),
          alert_gpio_(gpio_num_t(CONFIG_BQ25798_ALERT_GPIO)),
          status_(i2c_),
          ctrl_(i2c_)
          {}

    // === API PUBLIQUE ===

    void BQ2579XManager::init()
    {
        xTaskCreatePinnedToCore(task_wrapper, "STUSB_Task", 4096, this, 5, &task_handle_, 0);
    }

    esp_err_t BQ2579XManager::init_device()
    {
        RETURN_IF_ERROR(is_ready());
        //ConfigParams from_kconfig = load_config_from_kconfig();
        //cfg_.datas() = from_kconfig ; 

        cfg_.datas() = load_config_from_kconfig();
        ESP_LOGI(TAG, "Old config");
        //cfg_.datas().log();
        ESP_LOGI(TAG, "New config");
        //from_kconfig.log();
        RETURN_IF_ERROR(get_status());
        RETURN_IF_ERROR(apply_config(cfg_));
        return ESP_OK;
    }

    esp_err_t BQ2579XManager::is_ready()
    {
        const int max_attempts = 10;
        const int delay_ms = 50;
        esp_err_t err = ESP_OK;
        for (int attempt = 0; attempt < max_attempts; ++attempt)
        {
            err = ctrl_.ready();
                if (err == ESP_OK)
                {
                    ESP_LOGI(TAG, "BQ2579X détecté sur le bus (tentative %d)", attempt + 1);
                    break;
                }
            ESP_LOGW(TAG, "Tentative %d/%d : BQ2579X non prêt (err=0x%x)", attempt + 1, max_attempts, err);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));
        }
        
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "BQ2579X non détecté après %d tentatives", max_attempts);
            ready_ = false;
            return ESP_ERR_TIMEOUT; // ou err si tu veux refléter la dernière erreur de ready()
        }
        ready_ = true;
        return ESP_OK;
    }

    esp_err_t BQ2579XManager::apply_config(Config &cfg)
    {   
        RETURN_IF_ERROR(return_if_not_ready(ready_, TAG));
        ESP_LOGI(TAG, "Set config");
        return cfg.set();   
    }

    esp_err_t BQ2579XManager::handle_alert()
    {
        RETURN_IF_ERROR(return_if_not_ready(ready_, TAG));
        RETURN_IF_ERROR(status_.get_flags());

        return ESP_OK;
    }

    /// Envoie un soft reset au BQ2579X
    esp_err_t BQ2579XManager::reset()
    {
        RETURN_IF_ERROR(return_if_not_ready(ready_, TAG));
        return ctrl_.send_reset();
    }


    /// Lit et retourne l’état courant de la connexion USB-C
    esp_err_t BQ2579XManager::get_status(OutputFormat format)
    {
        RETURN_IF_ERROR(return_if_not_ready(ready_, TAG));
        RETURN_IF_ERROR(status_.get_status());
        HANDLE_OUTPUT(format, status_);
        return ESP_OK;
    }

    esp_err_t BQ2579XManager::get_measurements(OutputFormat format)
    {
        auto status = cfg_.datas().adc.acd.get_values();
        if (status.adc_rate_oneshot == true ) {
            RETURN_IF_ERROR(ctrl_.en_adc());
            vTaskDelay(50);
        }
        RETURN_IF_ERROR(return_if_not_ready(ready_, TAG));
        RETURN_IF_ERROR(ctrl_.get());
        HANDLE_OUTPUT(format, ctrl_);
        return ESP_OK;
    }

    void BQ2579XManager::task_wrapper(void *arg)
    {
        static_cast<BQ2579XManager *>(arg)->task_main();
    }

    void IRAM_ATTR BQ2579XManager::gpio_isr_handler(void *arg)
    {
        auto *self = static_cast<BQ2579XManager *>(arg);
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(self->task_handle_, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    void BQ2579XManager::setup_interrupt(gpio_num_t gpio)
    {
        static bool isr_installed = false;
        gpio_config_t io_conf = {};
        io_conf.intr_type = GPIO_INTR_NEGEDGE;
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pin_bit_mask = (1ULL << gpio);
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
        gpio_config(&io_conf);

        if (!isr_installed)
        {
            esp_err_t err = gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3);
            if (err == ESP_OK || err == ESP_ERR_INVALID_STATE)
            {
                isr_installed = true;
            }
            else
            {
                ESP_LOGE(TAG, "Failed to install ISR service: %s", esp_err_to_name(err));
            }
        }

        gpio_isr_handler_add(gpio, gpio_isr_handler, this);
    }

    void BQ2579XManager::task_main()
    {
        setup_interrupt(alert_gpio_);
        init_device();
        
        while (true)
        {
            if (gpio_get_level(alert_gpio_) == 0 || ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
            {
                if (gpio_get_level(alert_gpio_) == 0)
                {
                    ESP_LOGE(TAG, "Alert");
                    handle_alert();
                }
                
            }
        }
    }
};