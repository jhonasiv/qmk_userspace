// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include <stdint.h>
#include "action.h"

/**
 * \file
 *
 * \defgroup leader_compose Leader Compose Key. Adapts the leader key with an early ending
 * funtionality
 * \{
 */

/**
 * \brief User callback, invoked when the leader_compose sequence begins.
 */
void leader_compose_start_user(void);

/**
 * \brief User callback, invoked when the leader_compose sequence ends.
 */
void leader_compose_end_user(void);

/**
 * Begin the leader_compose sequence, resetting the buffer and timer.
 */
void leader_compose_start(void);

/**
 * End the leader_compose sequence.
 */
void leader_compose_end(void);

void leader_compose_task(void);

/**
 * Whether the leader_compose sequence is active.
 */
bool leader_compose_sequence_active(void);

/**
 * Add the given keycode to the sequence buffer.
 *
 * If `LEADER_NO_TIMEOUT` is defined, the timer is reset if the buffer is empty.
 *
 * \param keycode The keycode to add.
 *
 * \return `true` if the keycode was added, `false` if the buffer is full.
 */
bool leader_compose_sequence_add(uint16_t keycode);

/**
 * Whether the leader_compose sequence has reached the timeout.
 *
 * If `LEADER_NO_TIMEOUT` is defined, the buffer must also contain at least one key.
 */
bool leader_compose_sequence_timed_out(void);

/**
 * Reset the leader_compose sequence timer.
 */
void leader_compose_reset_timer(void);

/**
 * Check the sequence buffer for the given keycode.
 *
 * \param kc The keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_compose_sequence_one_key(uint16_t kc);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_compose_sequence_two_keys(uint16_t kc1, uint16_t kc2);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_compose_sequence_three_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 * \param kc4 The fourth keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_compose_sequence_four_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4);

/**
 * Check the sequence buffer for the given keycodes.
 *
 * \param kc1 The first keycode to check.
 * \param kc2 The second keycode to check.
 * \param kc3 The third keycode to check.
 * \param kc4 The fourth keycode to check.
 * \param kc5 The fifth keycode to check.
 *
 * \return `true` if the sequence buffer matches.
 */
bool leader_compose_sequence_five_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4,
                                       uint16_t kc5);

bool process_leader_compose(uint16_t keycode, keyrecord_t *record);

void leader_compose_on_key_release(uint16_t keycode);
int  leader_compose_match_held_sequence(uint16_t key0, uint16_t key1, uint16_t key2, uint16_t key3,
                                        uint16_t key4);
bool leader_compose_release_sequence_one_key(uint16_t key0);
bool leader_compose_release_sequence_two_keys(uint16_t key0, uint16_t key1);
bool leader_compose_release_sequence_three_keys(uint16_t key0, uint16_t key1, uint16_t key2);
bool leader_compose_release_sequence_four_keys(uint16_t key0, uint16_t key1, uint16_t key2,
                                               uint16_t key3);
bool leader_compose_release_sequence_five_keys(uint16_t key0, uint16_t key1, uint16_t key2,
                                               uint16_t key3, uint16_t key4);

void leader_compose_register_sequence_held(uint16_t key0, uint16_t key1, uint16_t key2,
                                           uint16_t key3, uint16_t key4);
/** \} */
