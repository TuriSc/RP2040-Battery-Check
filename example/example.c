/*
 * RP2040 Battery check
 * Measures the voltage level on the VSYS pin of a Raspberry Pi Pico.
 * Useful as a low-battery indicator.
 * By Turi Scandurra – https://turiscandurra.com/circuits
 * v1.0.0 - 2023.03.26
*/

#include <stdio.h>
#include <pico/stdlib.h>
#include "battery-check.h"
#include "hardware/adc.h"

void battery_check_callback(uint16_t battery_mv){
    printf("VSYS voltage: %dmv\n", battery_mv);

    if (battery_mv < LOW_BATT_THRESHOLD){
        // Low battery detected!
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
    } else {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
    }
}

int main() {
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Initialize the ADC before continuing
    adc_init();

    // Initialize the periodic measurement of VSYS voltage.
    // The parameter is the delay between polls in milliseconds.
    battery_check_init(5000);

    while (true) {
        tight_loop_contents(); // Do nothing
    }
}