/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
*/

#include <stdio.h>
#include <pico/stdlib.h>
#include "battery-check.h"
#include "hardware/adc.h"

void battery_check_callback(uint16_t battery_mv){
    // Called periodically according to the timer set
    // on initialization
    printf("VSYS voltage: %dmv\n", battery_mv);
}

void battery_low_callback(uint16_t battery_mv){
    // Called once
    printf("Low battery detected: %dmv\n", battery_mv);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    battery_check_stop(); // Stop the timer
}

int main() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Initialize the ADC before continuing
    adc_init();

    /*  Initialize the periodic measurement of VSYS voltage.
        Arguments:
            (uint16_t) ms - delay between polls in milliseconds - or 0 to disable automatic checks
            (void) repeating_callback(uint16_t battery_mv) - or NULL
            (void) low_battery_callback(uint16_t battery_mv) - or NULL
    */
    battery_check_init(5000, battery_check_callback, battery_low_callback);

    while (true) {
        tight_loop_contents(); // Nothing to do here
    }
}