/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
 * v1.0.0 - 2023.03.26
*/

#include "battery-check.h"
#include "hardware/adc.h"

static bool battery_check_task() {
   adc_select_input(3); // VSYS sense input

   // Coefficients from https://github.com/elehobica/pico_battery_op/
   uint16_t battery_mv = adc_read() * 9875 / (1<<12) - 20;
   battery_check_callback(battery_mv);
}

void battery_check_init(int delay_ms){
    adc_gpio_init(PIN_BATT_LVL);

    // Non-time-critical routine, run by timer
    add_repeating_timer_ms(delay_ms, battery_check_task, 0, &battery_check_timer);
}