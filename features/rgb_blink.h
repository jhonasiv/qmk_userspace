#ifndef RGB_BLINKING_ANIMATION
#define RGB_BLINKING_ANIMATION

#include <stdint.h>
#include "color.h"

/**
 * \file
 *
 * \defgroup rgb_blink RGB Blink animation for single keys.
 *
 */

/**
 * \brief Deferred execution callback responsible for blinking each individual key when they are
 * due.
 */
uint32_t blink_callback(uint32_t trigger_time, void *args);

/**
 * \brief Enables blinking for an individual key with its own RGB color and pulse interval
 */
void enable_blinking_for(uint8_t key_index, RGB color, uint32_t interval);

/**
 * \brief Disables blinking for an individual key
 */
void disable_blinking_for(uint8_t key_index);

bool blinking_enabled_on_led(uint8_t index);

void manage_blinking_keys(void);
#endif
