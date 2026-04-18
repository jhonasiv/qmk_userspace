#include "rgb_effects.h"
#include "rgb_matrix.h"
#include "action_util.h"

/**
 * Modifier indicator effect: when a modifier is active (held or one-shot),
 * ALL LEDs are set to a color specific to that modifier.
 *
 * When multiple modifiers are active, combined-modifier colors are checked
 * first, then individual modifiers fall back to the highest-priority single mod.
 *
 * Customize colors by editing the arrays below.
 */

/* Active modifier color (r, g, b) -- set each frame by tick */
static bool    mod_active = false;
static uint8_t mod_r = 0, mod_g = 0, mod_b = 0;

/* Individual modifier colors -- customize these */
/*                                          R    G    B   */
static const uint8_t color_ctrl[3]      = { 50,  50, 200};  /* Blue    */
static const uint8_t color_shift[3]     = {200,  50,  50};  /* Red     */
static const uint8_t color_alt[3]       = { 50, 200,  50};  /* Green   */
static const uint8_t color_gui[3]       = {200, 150,   0};  /* Amber   */

/* Combined modifier colors */
static const uint8_t color_ctrl_shift[3] = {150,  50, 200}; /* Purple  */
static const uint8_t color_ctrl_alt[3]   = { 50, 150, 150}; /* Teal    */
static const uint8_t color_alt_shift[3]  = {200, 100,  50}; /* Orange  */

static void modifier_tick(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    mod_active = false;

    if (mods == 0) return;

    bool has_ctrl  = mods & MOD_MASK_CTRL;
    bool has_shift = mods & MOD_MASK_SHIFT;
    bool has_alt   = mods & MOD_MASK_ALT;
    bool has_gui   = mods & MOD_MASK_GUI;

    const uint8_t *color = NULL;

    /* Check combined modifiers first */
    if (has_ctrl && has_shift) {
        color = color_ctrl_shift;
    } else if (has_ctrl && has_alt) {
        color = color_ctrl_alt;
    } else if (has_alt && has_shift) {
        color = color_alt_shift;
    }
    /* Single modifiers */
    else if (has_ctrl) {
        color = color_ctrl;
    } else if (has_shift) {
        color = color_shift;
    } else if (has_alt) {
        color = color_alt;
    } else if (has_gui) {
        color = color_gui;
    }

    if (color) {
        mod_active = true;
        mod_r = color[0];
        mod_g = color[1];
        mod_b = color[2];
    }
}

static bool modifier_set_led(uint8_t led_index, uint8_t *r, uint8_t *g, uint8_t *b) {
    if (!mod_active) return false;
    *r = mod_r;
    *g = mod_g;
    *b = mod_b;
    return true;
}

rgb_effect_t rgb_effect_modifier = {
    .tick        = modifier_tick,
    .set_led     = modifier_set_led,
    .on_keyevent = NULL,
    .priority    = 20,
};
