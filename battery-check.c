/**
 * @file battery-check.c
 * @brief RP2040 Battery check library implementation
 * @author Turi Scandurra
 * @date 2023.11.28
 * @version 1.2.0
 */

#include "battery-check.h"
#include "hardware/adc.h"

uint16_t low_batt_threshold = LOW_BATT_THRESHOLD_DEFAULT;
Callbacks callbacks;

/**
 * @brief Initialize the battery voltage measurement
 * @param delay_ms Delay between measurements in milliseconds (0 to disable timer)
 * @param repeat_callback Callback function for periodic updates (NULL to disable)
 * @param low_callback Callback function for low battery detection (NULL to disable)
 */
void battery_check_init(int delay_ms, void* repeat_callback, void* low_callback) {
    /**
     * Initialize the ADC pin for battery level measurement
     */
    adc_gpio_init(PIN_BATT_LVL);
    callbacks.repeat = repeat_callback;
    callbacks.low = low_callback;

    /**
     * Start the repeating timer if delay is non-zero
     */
    if (delay_ms > 0) {
        add_repeating_timer_ms(delay_ms, battery_check_task, &callbacks, &battery_check_timer);
    }
}

/**
 * @brief Task function for battery voltage measurement
 * @param rt Repeating timer object
 * @return true to continue the timer, false to stop
 */
static bool battery_check_task(repeating_timer_t *rt) {
    /**
     * Get the current battery voltage
     */
    uint16_t battery_mv = battery_check();

    /**
     * Call the repeat callback function if available
     */
    if (callbacks.repeat) {
        callbacks.repeat(battery_mv);
    }

    /**
     * Call the low battery callback function if available and voltage is below threshold
     */
    if (callbacks.low && battery_mv < low_batt_threshold) {
        callbacks.low(battery_mv);
    }

    /**
     * Continue the timer
     */
    return true;
}

/**
 * @brief Set the low battery threshold
 * @param mv Low battery threshold in millivolts
 */
void battery_set_threshold(uint16_t mv) {
    low_batt_threshold = mv;
}

/**
 * @brief Stop the battery voltage measurement timer
 */
void battery_check_stop() {
    cancel_repeating_timer(&battery_check_timer);
}

/**
 * @brief Get the current battery voltage
 * @return Battery voltage in millivolts
 */
uint16_t battery_check() {
    /**
     * Select the VSYS sense input for ADC measurement
     */
    adc_select_input(3);

    /**
     * Calculate the battery voltage using coefficients from https://github.com/elehobica/pico_battery_op/
     */
    return adc_read() * 9875 / (1 << 12) - 20;
}

