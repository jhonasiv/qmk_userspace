#include "rgb_blink.h"
#include <stdint.h>
#include "color.h"
#include "debug.h"
#include "deferred_exec.h"
#include "info_config.h"
#include "rgb_matrix.h"
#include "timer.h"

RGB            color_map[RGB_MATRIX_LED_COUNT]             = {0};
uint32_t       blink_interval[RGB_MATRIX_LED_COUNT]        = {0};
uint32_t       blink_timer_deadlines[RGB_MATRIX_LED_COUNT] = {UINT32_MAX};
deferred_token blink_callback_token                        = INVALID_DEFERRED_TOKEN;
deferred_token initialization_callback_token               = INVALID_DEFERRED_TOKEN;

uint32_t synch_with_closest_blink(uint16_t interval, uint32_t time) {
    uint32_t closest_deadline = UINT32_MAX;
    for (size_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint32_t deadline = blink_timer_deadlines[i];
        if (blink_interval[i] == interval) {
            return deadline;
        }

        if (deadline < closest_deadline) {
            closest_deadline = deadline;
        }
    }
    if (closest_deadline == UINT32_MAX) {
        return time;
    }
    return closest_deadline;
}

void enable_blinking_for(uint8_t key_index, RGB color, uint32_t interval) {
    blink_timer_deadlines[key_index] = synch_with_closest_blink(interval, timer_read32());
    color_map[key_index]             = color;
    blink_interval[key_index]        = interval;
}

void disable_blinking_for(uint8_t key_index) {
    RGB off                   = {0, 0, 0};
    color_map[key_index]      = off;
    blink_interval[key_index] = UINT32_MAX;
}

bool blinking_enabled_on_led(uint8_t index) {
    RGB  color      = color_map[index];
    bool rgb_is_off = color.r == 0 && color.g == 0 && color.b == 0;
    return blink_timer_deadlines[index] != UINT16_MAX && !rgb_is_off;
}

void manage_blinking_keys(void) {
    uint32_t trigger_time = timer_read32();
    for (size_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint32_t deadline = blink_timer_deadlines[i];
        RGB      rgb      = color_map[i];
        uint16_t interval = blink_interval[i];
        if (trigger_time > deadline) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

            uint64_t next_deadline = trigger_time + interval;
            if (next_deadline > UINT32_MAX) {
                blink_timer_deadlines[i] = UINT32_MAX;
            }
            blink_timer_deadlines[i] = next_deadline;
        } else if (trigger_time > deadline - interval / 2) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else if (trigger_time > deadline - interval) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
