#include "process_combo.h"

enum layers { BASE, SYM, NAV, MEDIA, FN, BR };

#define OSM_LSHIFT OSM(MOD_LSFT)
#define OSM_RSHIFT OSM(MOD_RSFT)
#define OSM_LCTRL OSM(MOD_LCTL)
#define OSM_RCTRL OSM(MOD_RCTL)

enum combos {
    WESC_Q_COMBO,
    DS_SAVE_COMBO,
    SDF_SHIFT_COMBO,
    JKL_SHIFT_COMBO,
    DFG_CTRL_COMBO,
    HJK_CTRL_COMBO
};

const uint16_t wesc_q_combo[] PROGMEM = {KC_W, KC_ESC, COMBO_END};
const uint16_t ds_save_combo[] PROGMEM = {KC_D, KC_S, COMBO_END};
const uint16_t sdf_shift_combo[] PROGMEM = {KC_S, KC_D, KC_F, COMBO_END};
const uint16_t dfg_ctrl_combo[] PROGMEM = {KC_D, KC_F, KC_G, COMBO_END};
const uint16_t jkl_shift_combo[] PROGMEM = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t hjk_ctrl_combo[] PROGMEM = {KC_D, KC_F, KC_G, COMBO_END};

combo_t key_combos[] = {
    [WESC_Q_COMBO] = COMBO(wesc_q_combo, KC_Q),
    [DS_SAVE_COMBO] = COMBO(ds_save_combo, LSFT_T(KC_S)),
    [SDF_SHIFT_COMBO] = COMBO(sdf_shift_combo, OSM_LSHIFT),
    [JKL_SHIFT_COMBO] = COMBO(jkl_shift_combo, OSM_RSHIFT),
    [DFG_CTRL_COMBO] = COMBO(dfg_ctrl_combo, OSM_LCTRL),
    [HJK_CTRL_COMBO] = COMBO(hjk_ctrl_combo, OSM_RCTRL),
};
