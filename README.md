# RP2040 Battery Check and low battery indicator

A small library to measure the voltage level on the VSYS pin of a Raspberry Pi Pico.
Useful for battery-powered projects.

The included example turns the onboard LED on when the voltage provided is below 3.25V.

### Available functions
```c
// Initialize the measurement. Make sure to initialize the ADC before calling this.
void battery_check_init(int delay_ms)

// Called periodically according to the timer set on initialization.
void battery_check_callback(uint16_t battery_mv)

// Called once, as soon as the detected voltage falls below the threshold.
void battery_low_callback(uint16_t battery_mv)

// Set the low threshold. Default is 3250mv.
void battery_set_threshold(uint16_t mv)

// Stop the measurement by canceling the repeating timer
void battery_check_stop()
```

An example application is provided.

### Version history
- 2023.09.29 - v1.1.0 - Added more public functions
- 2023.03.26 - v1.0.0 - First release