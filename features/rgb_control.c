#include "rgb_control.h"
#include "color.h"
#include "debug.h"
#include "info_config.h"
#include "rgb_matrix.h"

RGB      color_map[RGB_MATRIX_LED_COUNT]             = {};
uint32_t blink_interval[RGB_MATRIX_LED_COUNT]        = {};
uint32_t blink_timer_deadlines[RGB_MATRIX_LED_COUNT] = {};
uint32_t blink_counters[RGB_MATRIX_LED_COUNT]        = {};
uint32_t blink_ntimes_limit[RGB_MATRIX_LED_COUNT]    = {};

bool rgb_control_init = false;

void init_rgb_state(void) {
    if (rgb_control_init) {
        return;
    }
    disable_all();
    rgb_control_init = true;
}

void disable_all()
{
    RGB off = {0, 0, 0};
    for (size_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        color_map[i]             = off;
        blink_counters[i]        = 0;
        blink_interval[i]        = UINT32_MAX;
        blink_timer_deadlines[i] = UINT32_MAX;
        blink_ntimes_limit[i]    = UINT32_MAX;
        rgb_matrix_set_color(i, 0, 0, 0);
    }
}

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

void enable_blinking_for(uint8_t key_index, RGB color, uint32_t interval, uint32_t n_times) {
    blink_timer_deadlines[key_index] = synch_with_closest_blink(interval, timer_read32());
    color_map[key_index]             = color;
    blink_interval[key_index]        = interval;
    blink_ntimes_limit[key_index]    = n_times;
    blink_counters[key_index]        = 0;
}

void disable_blinking_for(uint8_t key_index) {
    RGB off                   = {0, 0, 0};
    color_map[key_index]      = off;
    blink_interval[key_index] = UINT32_MAX;
    blink_counters[key_index] = 0;
}

bool blinking_enabled_on_led(uint8_t index) {
    RGB  color      = color_map[index];
    bool rgb_is_off = color.r == 0 && color.g == 0 && color.b == 0;
    return blink_timer_deadlines[index] != UINT32_MAX && !rgb_is_off;
}

void manage_blink_deadline(size_t led_index, uint32_t trigger_time) {
    uint32_t count       = blink_counters[led_index];
    uint32_t count_limit = blink_ntimes_limit[led_index];

    if (count_limit != UINT32_MAX && count > count_limit) {
        dprintf("index: %u, count: %lu, limit: %lu, deadline: %lu, interval: %lu\n", led_index,
                count, count_limit, blink_timer_deadlines[led_index], blink_interval[led_index]);
        disable_blinking_for(led_index);
    }

    uint32_t interval      = blink_interval[led_index];
    if (interval == UINT32_MAX) {
        blink_timer_deadlines[led_index] = UINT32_MAX;
        return;
    }
    uint64_t next_deadline = trigger_time + interval;
    blink_timer_deadlines[led_index] = next_deadline;
}

void manage_blinking_keys(void) {
    uint32_t trigger_time = timer_read32();
    for (size_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        uint32_t deadline = blink_timer_deadlines[i];
        RGB      rgb      = color_map[i];
        uint16_t interval = blink_interval[i];
        if (trigger_time > deadline) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

            blink_counters[i] += 1;
            manage_blink_deadline(i, trigger_time);
        } else if (trigger_time > deadline - interval / 2 || !blinking_enabled_on_led(i)) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else if (trigger_time > deadline - interval) {
            // Should be on as it didnt reach the first half of the interval yet
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
