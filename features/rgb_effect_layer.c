#include "rgb_effects.h"
#include "rgb_matrix.h"
#include "action_layer.h"

/**
 * Layer indicator effect: when a non-BASE layer is active,
 * the top row LEDs (indices 0-5 left, 26-31 right) light up
 * in a color specific to that layer.
 *
 * Customize colors by editing the layer_colors array below.
 */

/* Layer count -- must match the layers enum in keymap.c */
#define LAYER_COUNT 9

/* Top row LED indices on the Voyager */
static const uint8_t top_row_leds[] = {0, 1, 2, 3, 4, 5, 26, 27, 28, 29, 30, 31};
#define TOP_ROW_COUNT (sizeof(top_row_leds) / sizeof(top_row_leds[0]))

/*                                    R    G    B   */
static const uint8_t layer_colors[LAYER_COUNT][3] = {
    [0] = {  0,   0,   0},  /* BASE    -- no indicator (off) */
    [1] = {100, 100, 255},  /* MOD     -- Light Blue         */
    [2] = {255, 200,   0},  /* SYM     -- Yellow             */
    [3] = {  0, 255, 100},  /* NAV     -- Green              */
    [4] = {255,   0, 150},  /* MEDIA   -- Pink               */
    [5] = {255,  80,   0},  /* FN      -- Orange             */
    [6] = {  0, 200, 200},  /* TAB     -- Cyan               */
    [7] = {255,   0,   0},  /* GAMING  -- Red                */
    [8] = {150,   0,   0},  /* EXT     -- Dark Red           */
};

static uint8_t active_layer = 0;

static void layer_tick(void) {
    active_layer = get_highest_layer(layer_state);
}

static bool layer_set_led(uint8_t led_index, uint8_t *r, uint8_t *g, uint8_t *b) {
    if (active_layer == 0 || active_layer >= LAYER_COUNT) return false;

    /* Only claim top row LEDs */
    for (uint8_t i = 0; i < TOP_ROW_COUNT; i++) {
        if (top_row_leds[i] == led_index) {
            *r = layer_colors[active_layer][0];
            *g = layer_colors[active_layer][1];
            *b = layer_colors[active_layer][2];
            return true;
        }
    }
    return false;
}

rgb_effect_t rgb_effect_layer = {
    .tick        = layer_tick,
    .set_led     = layer_set_led,
    .on_keyevent = NULL,
    .priority    = 30,
};
