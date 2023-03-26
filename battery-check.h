/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
 * v1.0.0 - 2023.03.26
*/

#ifndef RP2040_BATTERY_CHECK
#define RP2040_BATTERY_CHECK

#include <pico/stdlib.h>

#define LOW_BATT_THRESHOLD      3250    // 3.25V
#define PIN_BATT_LVL            29      // Cannot be changed

static repeating_timer_t battery_check_timer;
void battery_check_callback(uint16_t battery_mv);
static bool battery_check_task();
void battery_check_init(int delay_ms);

#endif