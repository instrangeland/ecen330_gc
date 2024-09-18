#include <stdio.h>
#include "pin.h"
#include "driver/gptimer.h"
#include "hw.h"
#include "lcd.h"
#include "watch.h"
#include "esp_timer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define HW_BTN_A      32
#define HW_BTN_B      33
#define HW_BTN_MENU   13
#define HW_BTN_OPTION  0
#define HW_BTN_SELECT 27
#define HW_BTN_START  39

volatile int64_t isr_max=0;
volatile int32_t isr_count=0; 

uint64_t volatile timer_ticks = 0;
bool volatile running = false;
static const char *TAG = "lab03";


static bool tick(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    uint64_t tick_start, tick_stop;
    tick_start = esp_timer_get_time();
    if (!pin_get_level(HW_BTN_A)){
        running = true;
    } else if (!pin_get_level(HW_BTN_B)) {
        running = false;
    } else if (!pin_get_level(HW_BTN_START)) {
        running = false;
        timer_ticks = 0;
    }
    if (running)
        timer_ticks++;
    tick_stop = esp_timer_get_time();
    isr_count++;
    if ((tick_stop - tick_start) > isr_max) {
        isr_max = (tick_stop - tick_start);
    }
    return false;
}

// Main application
void app_main(void)
{
    int64_t start_io, stop_io, start_setup_timer, stop_setup_timer, start_output, stop_output;
    start_io = esp_timer_get_time();
    pin_reset(HW_BTN_A);
    pin_reset(HW_BTN_B);
    pin_reset(HW_BTN_START);
    pin_input(HW_BTN_A, true);
    pin_input(HW_BTN_B, true);
    pin_input(HW_BTN_START, true);
    stop_io = esp_timer_get_time();
    printf("Configure I/O Pins: %lld microseconds\n", (stop_io - start_io));
	ESP_LOGI(TAG, "Starting");
    start_setup_timer = esp_timer_get_time();
    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1 * 1000 * 1000, // 1MHz, 1 tick = 1us
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0, // counter will reload with 0 on alarm event
        .alarm_count = 10000, // period = 10ms @resolution 1MHz
        .flags.auto_reload_on_alarm = true, // enable auto-reload
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    gptimer_event_callbacks_t cbs = {
        .on_alarm = tick, // register user callback
    };

    
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));
    ESP_ERROR_CHECK(gptimer_enable(gptimer));
    ESP_ERROR_CHECK(gptimer_start(gptimer));
    stop_setup_timer = esp_timer_get_time();
    printf("Setup Timer Pins: %lld microseconds\n", (stop_setup_timer - start_setup_timer));
    start_output = esp_timer_get_time();
    ESP_LOGI(TAG, "Stopwatch update");
    stop_output = esp_timer_get_time();
    printf("Log update: %lld microseconds\n", (stop_output - start_output));
    lcd_init();
    watch_init();
    while (true) {
        if (isr_count >= 500) {
            printf("Max ISR time: %lld microseconds for the last 5 seconds\n", (isr_max));
            isr_count = 0;
            isr_max = 0;
        }
        watch_update(timer_ticks);
    }

}
