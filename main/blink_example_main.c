#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "driver/ledc.h"

#define CHANNEL          ADC_CHANNEL_0
#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_11

enum State
    {
    OFF,
    FULL,
    THREE_QUARTER,
    HALF,
    QUARTER
    };

void ledControl(int channel, enum State currentState){  
                switch (currentState)
            {
                case OFF:
                    ESP_ERROR_CHECK( ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, 0) );
                    ESP_ERROR_CHECK( ledc_update_duty(LEDC_LOW_SPEED_MODE, channel) );
                    break;
                case FULL:
                    ESP_ERROR_CHECK( ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, 4095) );
                    ESP_ERROR_CHECK( ledc_update_duty(LEDC_LOW_SPEED_MODE, channel) );
                    break;
                case THREE_QUARTER:
                    ESP_ERROR_CHECK( ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, 3000) );
                    ESP_ERROR_CHECK( ledc_update_duty(LEDC_LOW_SPEED_MODE, channel) );
                    break;
                case HALF:
                    ESP_ERROR_CHECK( ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, 2000) );
                    ESP_ERROR_CHECK( ledc_update_duty(LEDC_LOW_SPEED_MODE, channel) );
                    break;
                case QUARTER:
                    ESP_ERROR_CHECK( ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, 1000) );
                    ESP_ERROR_CHECK( ledc_update_duty(LEDC_LOW_SPEED_MODE, channel) );
                    break;                 
            }         
}
void endState(int last, int second, int first){
        ledControl(last, OFF);
        ledControl(second, QUARTER);
        ledControl(first, HALF);
        vTaskDelay(pdMS_TO_TICKS(100));
        ledControl(second, OFF);
        ledControl(first, QUARTER);
        vTaskDelay(pdMS_TO_TICKS(100));
        ledControl(first, OFF);
        vTaskDelay(pdMS_TO_TICKS(100));
}
void app_main(void)
{
    //-------------ADC1 Init---------------//
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = EXAMPLE_ADC_ATTEN,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, CHANNEL, &config));

    // config timer for PWM
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_12_BIT,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    ledc_channel_config_t pwm_config = {
        .gpio_num = GPIO_NUM_4,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config1 = {
        .gpio_num = GPIO_NUM_18,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config2 = {
        .gpio_num = GPIO_NUM_19,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config3 = {
        .gpio_num = GPIO_NUM_21,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_3,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config4 = {
        .gpio_num = GPIO_NUM_22,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_4,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config5 = {
        .gpio_num = GPIO_NUM_27,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_5,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config6 = {
        .gpio_num = GPIO_NUM_26,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_6,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ledc_channel_config_t pwm_config7 = {
        .gpio_num = GPIO_NUM_25,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_7,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config1));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config2));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config3));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config4));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config5));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config6));
    ESP_ERROR_CHECK(ledc_channel_config(&pwm_config7));

    while (1) {
        int out = 0;
        int hodnoty[] = {3,4,5,6,7};
        int hodnotyBack[] = {0,1,2,3,4};
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, CHANNEL, &out));

        for(int i = 0; i < 3; i++){
            ledControl(i, FULL);
        }
        
        for(int i = 0; i < 5; i++){
            ledControl(hodnoty[i], FULL);
            ledControl(hodnotyBack[i],THREE_QUARTER);
            if(i >= 1){
                ledControl(hodnotyBack[i-1],HALF);
            }
            if(i >= 2){
                ledControl(hodnotyBack[i-2],QUARTER);
            }
            if(i >= 3){
                ledControl(hodnotyBack[i-3],OFF);
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        endState(2,3,4);
        
        for(int i = 4; i > -1; i--){
            ledControl(hodnotyBack[i], FULL);
            ledControl(hodnoty[i], THREE_QUARTER);
            if(i <= 3){
                ledControl(hodnoty[i+1],HALF);
            }
            if(i <= 2){
                ledControl(hodnoty[i+2],QUARTER);
            }
            if(i <= 1){
                ledControl(hodnoty[i+3],OFF);
            }
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        endState(5,4,3);
     }
    }