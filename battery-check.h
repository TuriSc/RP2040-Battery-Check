/**
 * @file battery-check.h
 * @brief RP2040 Battery check library
 * @author Turi Scandurra
 * @date 2023.11.28
 * @version 1.2.0
 */

#ifndef RP2040_BATTERY_CHECK
#define RP2040_BATTERY_CHECK

#include <pico/stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def LOW_BATT_THRESHOLD_DEFAULT
 * @brief Default low battery threshold in millivolts (3.25V)
 */
#define LOW_BATT_THRESHOLD_DEFAULT  3250

/**
 * @def PIN_BATT_LVL
 * @brief Pin used for battery level measurement (cannot be changed)
 */
#define PIN_BATT_LVL                29

/**
 * @typedef Callback
 * @brief Type definition for callback functions
 * @param battery_mv Battery voltage in millivolts
 */
typedef void (*Callback)(uint16_t battery_mv);

/**
 * @struct callbacks_t
 * @brief Structure to hold callback functions
 */
typedef struct callbacks_t {
    /**
     * @brief Callback function for periodic battery voltage updates
     */
    Callback repeat;
    /**
     * @brief Callback function for low battery voltage detection
     */
    Callback low;
} Callbacks;

/**
 * @var battery_check_timer
 * @brief Repeating timer for battery voltage checks
 */
static repeating_timer_t battery_check_timer;

/**
 * @brief Initialize the battery voltage measurement
 * @param delay_ms Delay between measurements in milliseconds (0 to disable timer)
 * @param repeat_callback Callback function for periodic updates (NULL to disable)
 * @param low_callback Callback function for low battery detection (NULL to disable)
 */
void battery_check_init(int delay_ms, void* repeat_callback, void* low_callback);

/**
 * @brief Task function for battery voltage measurement
 * @param rt Repeating timer object
 * @return true to continue the timer, false to stop
 */
static bool battery_check_task(repeating_timer_t *rt);

/**
 * @brief Callback function for battery voltage updates
 * @param battery_mv Battery voltage in millivolts
 */
void battery_check_callback(uint16_t battery_mv);

/**
 * @brief Callback function for low battery voltage detection
 * @param battery_mv Battery voltage in millivolts
 */
void battery_low_callback(uint16_t battery_mv);

/**
 * @brief Set the low battery threshold
 * @param mv Low battery threshold in millivolts
 */
void battery_set_threshold(uint16_t mv);

/**
 * @brief Stop the battery voltage measurement timer
 */
void battery_check_stop();

/**
 * @brief Get the current battery voltage
 * @return Battery voltage in millivolts
 */
uint16_t battery_check();

#ifdef __cplusplus
}
#endif

#endif

