/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
 * 2023.11.28 - v1.2.0
*/

#ifndef RP2040_BATTERY_CHECK
#define RP2040_BATTERY_CHECK

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOW_BATT_THRESHOLD_DEFAULT  3250    // 3.25V
#define PIN_BATT_LVL                29      // Cannot be changed

typedef void (*Callback)(uint16_t mv);

typedef struct callbacks_t {
    Callback repeat;
    Callback low;
} Callbacks;

static repeating_timer_t battery_check_timer;
void battery_check_init(int delay_ms, void* repeat_callback, void* low_callback);
static bool battery_check_task();
void battery_check_callback(uint16_t battery_mv);
void battery_low_callback(uint16_t battery_mv);
void battery_set_threshold(uint16_t mv);
void battery_check_stop();

uint16_t battery_check();

#ifdef __cplusplus
}
#endif

#endif