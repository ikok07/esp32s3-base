#include <esp_log.h>

#include "app_state.h"
#include "led_strip.h"
#include "driver/gptimer.h"

#include "power.h"
#include "timer.h"
#include "led.h"

bool IRAM_ATTR tim_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx);

void app_main(void) {

    // Configure power
    ESP_ERROR_CHECK(POWER_Config());

    *gAppState.htim = (TIMER_HandleTypeDef){
        .htim = (gptimer_handle_t){},
        .Cfg = (TIMER_ConfigTypeDef){
            .Clk = GPTIMER_CLK_SRC_APB,
            .Direction = GPTIMER_COUNT_UP,
            .Resolution_Hz = 1000000,
            .InterruptPrio = 1,
            .Alarm = {
                .TriggerCount = 1000000,
                .AutoReloadOnAlarm = 1,
                .AlarmTriggerCb = tim_callback
            }
        }
    };

    if (TIMER_Init(gAppState.htim) != TIMER_ERROR_OK) {
        while (1);
    };

    if (TIMER_Start(gAppState.htim) != TIMER_ERROR_OK) {
        while (1);
    }

    if (LED_Config() != ESP_OK) {
        while (1);
    }

    LED_StartTask();
}

bool IRAM_ATTR tim_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
    vTaskGenericNotifyGiveFromISR(gAppState.Tasks->LedTask.OsTask, 0, NULL);
    return pdFALSE;
}