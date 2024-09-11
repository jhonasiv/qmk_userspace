#ifndef RGB_CONTROL_ANIMATION
#define RGB_CONTROL_ANIMATION

#include <stdint.h>
#include "color.h"

/**
 * \file
 *
 * \defgroup rgb_blink RGB Blink animation for single keys.
 *
 */
 void init_rgb_state(void);

/**
 * \brief Enables blinking for an individual key with its own RGB color and pulse interval
 */
void enable_blinking_for(uint8_t key_index, RGB color, uint32_t interval, uint32_t n_times);

/**
 * \brief Disables blinking for an individual key
 */
void disable_blinking_for(uint8_t key_index);

bool blinking_enabled_on_led(uint8_t index);

void manage_blinking_keys(void);
#endif
