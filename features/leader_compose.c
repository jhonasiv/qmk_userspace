// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "leader_compose.h"
#include "debug.h"
#include "keycodes.h"
#include "timer.h"
#include "util.h"
#include "quantum_keycodes.h"
#include <string.h>

#ifndef LEADER_TIMEOUT
#    define LEADER_TIMEOUT 300
#endif

#ifndef LEADER_SEQUENCE_SIZE
#    define LEADER_SEQUENCE_SIZE 5
#endif

// Leader key stuff
bool     leading                                               = false;
uint16_t leader_compose_time                                   = 0;
uint16_t leader_compose_sequence[LEADER_SEQUENCE_SIZE]         = {0, 0, 0, 0, 0};
uint8_t  leader_compose_sequence_size                          = 0;
bool     leader_compose_down                                   = false;
uint16_t leader_compose_sequence_held[2][LEADER_SEQUENCE_SIZE] = {0};

__attribute__((weak)) void leader_compose_start_user(void) {}

__attribute__((weak)) void leader_compose_end_user(void) {}

__attribute__((weak)) bool leader_compose_final_sequences(void) {
    return false;
}

__attribute__((weak)) void leader_compose_on_key_release_user(uint16_t keycode) {}
__attribute__((weak)) void leader_compose_on_timeout_sequences(void) {}

void leader_compose_start(void) {
    if (leading) {
        return;
    }
    leader_compose_start_user();
    leading                      = true;
    leader_compose_time          = timer_read();
    leader_compose_sequence_size = 0;
    memset(leader_compose_sequence, 0, sizeof(leader_compose_sequence));
}

bool leader_compose_sequence_done(void) {
    return leader_compose_sequence_active() &&
           (leader_compose_sequence_timed_out() || leader_compose_final_sequences());
}

void leader_compose_end(void) {
    leading = false;
    if (leader_compose_sequence_timed_out()) {
        leader_compose_on_timeout_sequences();
    }
    leader_compose_end_user();
}

void leader_compose_task(void) {
    if (leader_compose_sequence_done()) {
        leader_compose_end();
    }
}

bool leader_compose_sequence_active(void) {
    return leading;
}

bool leader_compose_sequence_add(uint16_t keycode) {
    if (leader_compose_sequence_size >= ARRAY_SIZE(leader_compose_sequence)) {
        return false;
    }

#if defined(LEADER_NO_TIMEOUT)
    if (leader_compose_sequence_size == 0) {
        leader_compose_reset_timer();
    }
#endif

    leader_compose_sequence[leader_compose_sequence_size] = keycode;
    leader_compose_sequence_size++;

    return true;
}

bool leader_compose_sequence_timed_out(void) {
#if defined(LEADER_NO_TIMEOUT)
    return leader_compose_sequence_size > 0 && timer_elapsed(leader_compose_time) > LEADER_TIMEOUT;
#else
    return timer_elapsed(leader_compose_time) > LEADER_TIMEOUT;
#endif
}

void leader_compose_reset_timer(void) {
    leader_compose_time = timer_read();
}

bool leader_compose_sequence_is(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4,
                                uint16_t kc5, uint16_t sequence[5]) {
    return sequence[0] == kc1 && sequence[1] == kc2 && sequence[2] == kc3 && sequence[3] == kc4 &&
           sequence[4] == kc5;
}

bool leader_compose_sequence_one_key(uint16_t kc) {
    return leader_compose_sequence_is(kc, 0, 0, 0, 0, leader_compose_sequence);
}

bool leader_compose_sequence_two_keys(uint16_t kc1, uint16_t kc2) {
    return leader_compose_sequence_is(kc1, kc2, 0, 0, 0, leader_compose_sequence);
}

bool leader_compose_sequence_three_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3) {
    return leader_compose_sequence_is(kc1, kc2, kc3, 0, 0, leader_compose_sequence);
}

bool leader_compose_sequence_four_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4) {
    return leader_compose_sequence_is(kc1, kc2, kc3, kc4, 0, leader_compose_sequence);
}

bool leader_compose_sequence_five_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4,
                                       uint16_t kc5) {
    return leader_compose_sequence_is(kc1, kc2, kc3, kc4, kc5, leader_compose_sequence);
}

bool process_leader_compose(uint16_t keycode, keyrecord_t *record) {
    dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->event.time, record->tap.interrupted, record->tap.count);
    if (record->event.pressed) {
        if (keycode == QK_LEAD) {
            leader_compose_down = true;
            leader_compose_start();
            return true;
        }

#ifdef LEADER_COMPOSE_CONTINUOUS_TRIGGER
        if (leader_compose_down && !leader_compose_sequence_active()) {
            leader_compose_start();
        }
#endif
        if (leader_compose_sequence_active() && !leader_compose_sequence_timed_out()) {
#ifndef LEADER_KEY_STRICT_KEY_PROCESSING
            if (IS_QK_MOD_TAP(keycode)) {
                keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            } else if (IS_QK_LAYER_TAP(keycode)) {
                keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            }
#endif

            if (!leader_compose_sequence_add(keycode)) {
                leader_compose_end();

                return true;
            }

#ifdef LEADER_PER_KEY_TIMING
            leader_compose_reset_timer();
#endif

            return false;
        }
    } else if (keycode == QK_LEADER) {
        leader_compose_down = false;
#ifdef LEADER_COMPOSE_CONTINUOUS_TRIGGER
    } else {
        leader_compose_on_key_release(keycode);
#endif
    }

    return true;
}

int leader_compose_match_held_sequence(uint16_t key0, uint16_t key1, uint16_t key2, uint16_t key3,
                                       uint16_t key4) {
    if (leader_compose_sequence_held[0] == KC_NO) {
        return -1;
    }
    for (int i = 0; i < 2; i++) {
        dprintf("\nINDEX %d: Seq 0x%04X 0x%04X 0x%04X 0x%04X 0x%04X", i, key0, key1, key2, key3,
                key4);
        dprintf("\nSTORED INDEX %d: Seq 0x%04X 0x%04X 0x%04X 0x%04X 0x%04X\n", i,
                leader_compose_sequence_held[i][0], leader_compose_sequence_held[i][1],
                leader_compose_sequence_held[i][2], leader_compose_sequence_held[i][3],
                leader_compose_sequence_held[i][4]);
        if (leader_compose_sequence_is(key0, key1, key2, key3, key4,
                                       leader_compose_sequence_held[i])) {
            return i;
        }
    }
    return -1;
}

void release_held_sequence(int index) {
    if (index == 0 && leader_compose_sequence_held[1][0] != KC_NO) {
        memcpy(&leader_compose_sequence_held[0], &leader_compose_sequence_held[1],
               sizeof(leader_compose_sequence_held[0]));
        memset(&leader_compose_sequence_held[1], 0, sizeof(leader_compose_sequence_held[1]));
        return;
    }
    memset(&leader_compose_sequence_held[index], 0, sizeof(leader_compose_sequence_held[index]));
}

void leader_compose_on_key_release(uint16_t keycode) {
    dprintf("Keycode 0x%04X was released, calling compose end\n", keycode);
    leader_compose_on_key_release_user(keycode);
}

bool leader_compose_release_sequence_one_key(uint16_t key0) {
    int held_index = leader_compose_match_held_sequence(key0, 0, 0, 0, 0);
    if (held_index == -1) {
        return false;
    }

    release_held_sequence(held_index);
    return true;
}

bool leader_compose_release_sequence_two_keys(uint16_t key0, uint16_t key1) {
    int held_index = leader_compose_match_held_sequence(key0, key1, 0, 0, 0);
    if (held_index == -1) {
        return false;
    }

    release_held_sequence(held_index);
    return true;
}

bool leader_compose_release_sequence_three_keys(uint16_t key0, uint16_t key1, uint16_t key2) {
    int held_index = leader_compose_match_held_sequence(key0, key1, key2, 0, 0);
    if (held_index == -1) {
        return false;
    }

    release_held_sequence(held_index);
    return true;
}
bool leader_compose_release_sequence_four_keys(uint16_t key0, uint16_t key1, uint16_t key2,
                                               uint16_t key3) {
    int held_index = leader_compose_match_held_sequence(key0, key1, key2, key3, 0);
    if (held_index == -1) {
        return false;
    }

    release_held_sequence(held_index);
    return true;
}
bool leader_compose_release_sequence_five_keys(uint16_t key0, uint16_t key1, uint16_t key2,
                                               uint16_t key3, uint16_t key4) {
    int held_index = leader_compose_match_held_sequence(key0, key1, key2, key3, key4);
    if (held_index == -1) {
        return false;
    }

    release_held_sequence(held_index);
    return true;
}

void leader_compose_register_sequence_held(uint16_t key0, uint16_t key1, uint16_t key2,
                                           uint16_t key3, uint16_t key4) {
    size_t id;
    if (leader_compose_sequence_held[0][0] == KC_NO) {
        id = 0;
    } else {
        id = 1;
    }
    memcpy(&leader_compose_sequence_held[id][0], &key0, sizeof(leader_compose_sequence_held[0][0]));
    memcpy(&leader_compose_sequence_held[id][1], &key1, sizeof(leader_compose_sequence_held[0][1]));
    memcpy(&leader_compose_sequence_held[id][2], &key2, sizeof(leader_compose_sequence_held[0][2]));
    memcpy(&leader_compose_sequence_held[id][3], &key3, sizeof(leader_compose_sequence_held[0][3]));
    memcpy(&leader_compose_sequence_held[id][4], &key4, sizeof(leader_compose_sequence_held[0][4]));
    dprintf("\nREGISTERING INDEX %d: Seq 0x%04X 0x%04X 0x%04X 0x%04X 0x%04X\n", id,
            leader_compose_sequence_held[id][0], leader_compose_sequence_held[id][1],
            leader_compose_sequence_held[id][2], leader_compose_sequence_held[id][3],
            leader_compose_sequence_held[id][4]);
}
