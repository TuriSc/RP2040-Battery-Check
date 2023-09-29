/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
 * v1.1.0 - 2023.09.29
*/

#include "battery-check.h"
#include "hardware/adc.h"

uint16_t low_batt_threshold = LOW_BATT_THRESHOLD_DEFAULT;

void battery_check_init(int delay_ms){
    adc_gpio_init(PIN_BATT_LVL);

    // Non-time-critical routine, run by timer
    add_repeating_timer_ms(delay_ms, battery_check_task, 0, &battery_check_timer);
}

static bool battery_check_task() {
    adc_select_input(3); // VSYS sense input

    // Coefficients from https://github.com/elehobica/pico_battery_op/
    uint16_t battery_mv = adc_read() * 9875 / (1<<12) - 20;
    battery_check_callback(battery_mv);
    static bool _low_callback_fired;
    if (!_low_callback_fired && battery_mv < low_batt_threshold){
        battery_low_callback(battery_mv);
        _low_callback_fired = true;
    }
}

void battery_set_threshold(uint16_t mv){
    low_batt_threshold = mv;
}

void battery_check_stop(){
    cancel_repeating_timer(&battery_check_timer);
}