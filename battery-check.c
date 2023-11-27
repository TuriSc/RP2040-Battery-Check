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
Callbacks callbacks;

void battery_check_init(int delay_ms, void* repeat_callback, void* low_callback){
    adc_gpio_init(PIN_BATT_LVL);
    callbacks.repeat = repeat_callback;
    callbacks.low = low_callback;

    if (delay_ms > 0){
        // Non-time-critical routine, run by timer
        add_repeating_timer_ms(delay_ms, battery_check_task, &callbacks, &battery_check_timer);
    }
}

static bool battery_check_task(repeating_timer_t *rt, void *user_data) {
    uint16_t battery_mv = battery_check();

    if(callbacks.repeat){
        callbacks.repeat(battery_mv);
    }
    if(callbacks.low && battery_mv < low_batt_threshold){
        callbacks.low(battery_mv);
    }
    return true;
}

void battery_set_threshold(uint16_t mv){
    low_batt_threshold = mv;
}

void battery_check_stop(){
    cancel_repeating_timer(&battery_check_timer);
}


uint16_t battery_check(){
    adc_select_input(3); // VSYS sense input

    // Coefficients from https://github.com/elehobica/pico_battery_op/
    return adc_read() * 9875 / (1<<12) - 20;
}