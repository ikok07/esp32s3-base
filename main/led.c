//
// Created by Kok on 2/12/26.
//

#include "led.h"

#include "led_strip.h"
#include "esp_task.h"

#include "app_state.h"
#include "tasks_common.h"

static led_strip_handle_t hled;
static volatile uint8_t gColorIndex = 0;

static void led_task(void *arg);

esp_err_t LED_Config() {
    led_strip_config_t LED_Config = {
        .strip_gpio_num = LED_PIN,
        .max_leds = 1
    };
    led_strip_rmt_config_t RMT_Config = {
        .resolution_hz = 10 * 1000 * 1000 // 10 MHz
    };

    return led_strip_new_rmt_device(&LED_Config, &RMT_Config, &hled);
}

void LED_StartTask() {
    gAppState.Tasks->LedTask = (SCHEDULER_TaskTypeDef){
        .Args = NULL,
        .CoreID = LED_TASK_CORE_ID,
        .Name = "LED Task",
        .Priority = LED_TASK_PRIORITY,
        .StackDepth = LED_TASK_STACK_DEPTH,
        .Function = led_task
    };
    SCHEDULER_Create(&gAppState.Tasks->LedTask);
}

void led_task(void *arg) {
    while (1) {
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) {
            uint32_t value = 50;
            ESP_ERROR_CHECK(led_strip_set_pixel(
                hled,
                0,
                gColorIndex == 0 ? value : 0,
                gColorIndex == 1 ? value : 0,
                gColorIndex == 2 ? value : 0
            ));
            ESP_ERROR_CHECK(led_strip_refresh(hled));

            gColorIndex++;
            if (gColorIndex > 2) gColorIndex = 0;
        }
    }
}