#include "rgb_effects.h"
#include "rgb_matrix.h"
#include "timer.h"

/**
 * Keypress fade effect: when a normal key is pressed, its LED lights up white
 * and linearly fades to off over FADE_DURATION_MS.
 *
 * Modifier keys (OSM, layer switches, etc.) are excluded from triggering fades.
 */

#define FADE_DURATION_MS 2000

static uint32_t fade_start[RGB_MATRIX_LED_COUNT] = {0};
static bool     fade_active[RGB_MATRIX_LED_COUNT] = {false};

/* Declared in keymap.c */
extern const uint8_t PROGMEM keypos_to_led_map[MATRIX_ROWS][MATRIX_COLS];

static void fade_tick(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (fade_active[i] && timer_elapsed32(fade_start[i]) >= FADE_DURATION_MS) {
            fade_active[i] = false;
        }
    }
}

static bool fade_set_led(uint8_t led_index, uint8_t *r, uint8_t *g, uint8_t *b) {
    if (!fade_active[led_index]) {
        return false;
    }
    uint32_t elapsed = timer_elapsed32(fade_start[led_index]);
    if (elapsed >= FADE_DURATION_MS) {
        return false;
    }
    /* Linear fade: brightness goes from 255 to 0 */
    uint8_t brightness = 255 - (uint8_t)((uint32_t)255 * elapsed / FADE_DURATION_MS);
    *r = brightness;
    *g = brightness;
    *b = brightness;
    return true;
}

static bool is_normal_keypress(uint16_t keycode) {
    /* Exclude modifiers, layer switches, custom keycodes, and transparent keys */
    if (IS_QK_ONE_SHOT_MOD(keycode)) return false;
    if (IS_QK_LAYER_TAP(keycode))    return false;
    if (IS_QK_MOD_TAP(keycode))      return false;
    if (IS_QK_MOMENTARY(keycode))    return false;
    if (IS_QK_ONE_SHOT_LAYER(keycode)) return false;
    if (IS_QK_TOGGLE_LAYER(keycode)) return false;
    if (IS_QK_LAYER_MOD(keycode))    return false;
    if (keycode == KC_TRNS)          return false;
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        /* Regular key with mod bits applied (e.g. LCTL(KC_LEFT)) -- still a "key" action */
        return true;
    }
    if (keycode >= KC_LEFT_CTRL && keycode <= KC_RIGHT_GUI) return false;
    return true;
}

static void fade_on_keyevent(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return;
    if (!is_normal_keypress(keycode)) return;

    uint8_t led = pgm_read_byte(&keypos_to_led_map[record->event.key.row][record->event.key.col]);
    if (led >= RGB_MATRIX_LED_COUNT) return;

    fade_start[led]  = timer_read32();
    fade_active[led] = true;
}

rgb_effect_t rgb_effect_fade = {
    .tick        = fade_tick,
    .set_led     = fade_set_led,
    .on_keyevent = fade_on_keyevent,
    .priority    = 10,
};
