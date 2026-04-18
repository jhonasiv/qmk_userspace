#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "action.h"

/**
 * \file
 * \defgroup rgb_effects Extensible RGB Effect System
 *
 * A priority-based system for composing multiple RGB lighting behaviors.
 * Each effect has a priority (higher wins) and can claim individual LEDs.
 * Effects are evaluated per-LED from highest to lowest priority; the first
 * effect that claims a LED wins.
 *
 * To add a new effect:
 *   1. Create a new .c file with tick/set_led/on_keyevent functions
 *   2. Define a rgb_effect_t and register it in rgb_effects.c
 *   3. Add the .c file to rules.mk SRC
 */

typedef struct {
    /**
     * Called once per frame before LED iteration.
     * Use for updating timers, reading state, etc.
     */
    void (*tick)(void);

    /**
     * Called for each LED index. Write r/g/b and return true to claim the LED.
     * Return false to let lower-priority effects handle it.
     */
    bool (*set_led)(uint8_t led_index, uint8_t *r, uint8_t *g, uint8_t *b);

    /**
     * Called on every key press/release. Use for triggering transient effects.
     * May be NULL if the effect doesn't need keyevent info.
     */
    void (*on_keyevent)(uint16_t keycode, keyrecord_t *record);

    /** Higher priority effects are evaluated first. */
    uint8_t priority;
} rgb_effect_t;

/* Lifecycle */
void rgb_effects_init(void);
void rgb_effects_process(void);
void rgb_effects_record(uint16_t keycode, keyrecord_t *record);

/* Effect declarations -- implemented in their own .c files */
extern rgb_effect_t rgb_effect_layer;
extern rgb_effect_t rgb_effect_modifier;
extern rgb_effect_t rgb_effect_fade;
