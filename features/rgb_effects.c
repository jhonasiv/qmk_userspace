#include "rgb_effects.h"
#include "rgb_matrix.h"

/* Register all effects here, in any order. Priority field determines evaluation order. */
static rgb_effect_t *effects[] = {
    &rgb_effect_layer,
    &rgb_effect_modifier,
    &rgb_effect_fade,
};

#define EFFECT_COUNT (sizeof(effects) / sizeof(effects[0]))

static bool initialized = false;

void rgb_effects_init(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    initialized = true;
}

void rgb_effects_process(void) {
    if (!initialized) {
        rgb_effects_init();
    }

    /* Tick all effects (update timers, read state) */
    for (uint8_t e = 0; e < EFFECT_COUNT; e++) {
        if (effects[e]->tick) {
            effects[e]->tick();
        }
    }

    /* Sort effects by priority descending (simple insertion sort, tiny array) */
    rgb_effect_t *sorted[EFFECT_COUNT];
    for (uint8_t i = 0; i < EFFECT_COUNT; i++) {
        sorted[i] = effects[i];
    }
    for (uint8_t i = 1; i < EFFECT_COUNT; i++) {
        rgb_effect_t *tmp = sorted[i];
        int8_t j = i - 1;
        while (j >= 0 && sorted[j]->priority < tmp->priority) {
            sorted[j + 1] = sorted[j];
            j--;
        }
        sorted[j + 1] = tmp;
    }

    /* For each LED, find the highest-priority effect that claims it */
    for (uint8_t led = 0; led < RGB_MATRIX_LED_COUNT; led++) {
        uint8_t r = 0, g = 0, b = 0;
        bool claimed = false;
        for (uint8_t e = 0; e < EFFECT_COUNT; e++) {
            if (sorted[e]->set_led && sorted[e]->set_led(led, &r, &g, &b)) {
                claimed = true;
                break;
            }
        }
        (void)claimed;
        rgb_matrix_set_color(led, r, g, b);
    }
}

void rgb_effects_record(uint16_t keycode, keyrecord_t *record) {
    if (!initialized) {
        rgb_effects_init();
    }
    for (uint8_t e = 0; e < EFFECT_COUNT; e++) {
        if (effects[e]->on_keyevent) {
            effects[e]->on_keyevent(keycode, record);
        }
    }
}
