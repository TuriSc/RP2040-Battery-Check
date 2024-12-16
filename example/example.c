/**
 * @file example.c
 * @brief Example application for RP2040 Battery Check library
 * @author Turi Scandurra
 * @date 2023.11.28
 * @version 1.2.0
 */

#include <stdio.h>
#include <pico/stdlib.h>
#include "battery-check.h"
#include "hardware/adc.h"

/**
 * @brief Callback function for battery voltage updates
 * @param battery_mv Battery voltage in millivolts
 */
void battery_check_callback(uint16_t battery_mv) {
    printf("VSYS voltage: %dmv\n", battery_mv);
}

/**
 * @brief Callback function for low battery voltage detection
 * @param battery_mv Battery voltage in millivolts
 */
void battery_low_callback(uint16_t battery_mv) {
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

    /*  For manual control over measurements, call battery_check_init with a delay of 0
        and the callbacks set to NULL. Then call battery_check at the appropriate time:

        battery_check_init(0, NULL, NULL);
        uint16_t battery_mv = battery_check();

        Note: immediately after power-on the reading can be significantly lower.
        Perform other initialization first and/or add a sleep_ms(10) if required to stabilize it.
    */

    while (true) {
        tight_loop_contents(); // Nothing to do here
    }
}
