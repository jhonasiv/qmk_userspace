#include <stdint.h>
#include "action.h"
#include "action_layer.h"
#include "features/rgb_control.h"
#include "keycodes.h"
#include "keymap_us.h"

#include QMK_KEYBOARD_H
#include "keymap_us_international_linux.h"
#include "features/leader_compose.h"

enum layers { BASE, MOD, SYM, NAV, MEDIA, FN, GAMING, GAMING_ALT };

#define OSM_LSHIFT OSM(MOD_LSFT)
#define OSM_RSHIFT OSM(MOD_RSFT)
#define OSM_ALT    OSM(MOD_LALT)
#define OSM_LCTRL  OSM(MOD_LCTL)
#define OSM_RCTRL  OSM(MOD_RCTL)

#define VOL_DOWN   KC_AUDIO_VOL_DOWN
#define VOL_UP     KC_AUDIO_VOL_UP
#define VOL_MUTE   KC_AUDIO_MUTE
#define MEDIA_STOP KC_MEDIA_STOP
#define MEDIA_PREV KC_MEDIA_PREV_TRACK
#define MEDIA_NEXT KC_MEDIA_NEXT_TRACK
#define MEDIA_PLAY KC_MEDIA_PLAY_PAUSE

#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE  SAFE_RANGE

#define ____ KC_TRNS

enum custom_keycodes {
    RGB_CTRL_TOG = ML_SAFE_RANGE,
    FREEZE_REPEAT_REGISTER,
    FREEZE_REPEAT_ENABLE,
    CUSTOM_REPEAT,
    ALT_CUSTOM_REPEAT,
    ALT_TAB,
    QUICK_LAYER_OFF
};

#define QLO QUICK_LAYER_OFF

#define FREEZE_REP     FREEZE_REPEAT_REGISTER
#define FREEZE_REP_TOG FREEZE_REPEAT_ENABLE

const key_override_t shift_backspace_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t inverted_quote         = ko_make_basic(MOD_MASK_SHIFT, US_DQUO, US_QUOT);
const key_override_t crase                  = ko_make_basic(MOD_MASK_SHIFT, US_ACUT, US_DGRV);
const key_override_t minus                  = ko_make_basic(MOD_MASK_SHIFT, KC_MINUS, KC_MINUS);

const key_override_t **key_overrides =
    (const key_override_t *[]){&shift_backspace_delete, &inverted_quote, &crase, &minus, NULL};

enum combos {
    ESC_COMBO,
    ENTER_COMBO,
    SYM_ENTER_COMBO,
    NAV_ENTER_COMBO,

    // Layers
    //    SYM
    SYM_COMBO,
    RSYM_COMBO,
    //    NAV
    NAV_COMBO,
    //    MEDIA
    MEDIA_COMBO,
    MEDIA_LOCK_COMBO,
    MEDIA_OUT_COMBO,
    //    FN
    FN_COMBO,
    FN_LOCK_COMBO,
    FN_OUT_COMBO,

    // LANG
    GRAVE_COMBO,
    CEDILHA_COMBO,
    ACUTE_COMBO,
    CIRC_COMBO,
    TILDE_COMBO,
    UNDERLINE_COMBO,

    // CUSTOM KEYS;
    USE_FREEZE_REPEAT,

    // GAMING KEYS
    GMG_ENTER,
    GMG_6,
    GMG_7,
    GMG_8,
    GMG_9,
    GMG_0,
    GMG_F6,
    GMG_F7,
    GMG_F8,
    GMG_F9,
    GMG_F10,
    GMG_F11,
    GMG_F12,
    GMG_TAB,
    GMG_I,
    GMG_P,
    GMG_M,
};

const uint16_t esc_combo[] PROGMEM       = {KC_R, KC_S, COMBO_END};
const uint16_t enter_combo[] PROGMEM     = {KC_I, KC_E, COMBO_END};
const uint16_t sym_enter_combo[] PROGMEM = {KC_EQL, KC_ASTERISK, COMBO_END};
const uint16_t nav_enter_combo[] PROGMEM = {KC_UP, KC_DOWN, COMBO_END};

// Layers
//    SYM
const uint16_t sym_combo[] PROGMEM  = {KC_W, KC_P, COMBO_END};
const uint16_t rsym_combo[] PROGMEM = {KC_L, KC_Y, COMBO_END};
//    NAV
const uint16_t nav_combo[] PROGMEM = {KC_W, KC_F, COMBO_END};
//    MEDIA
const uint16_t media_combo[] PROGMEM      = {KC_1, KC_2, COMBO_END};
const uint16_t media_lock_combo[] PROGMEM = {KC_1, KC_2, KC_3, COMBO_END};
const uint16_t media_out_combo[] PROGMEM  = {VOL_DOWN, VOL_UP, VOL_MUTE, COMBO_END};
//    FN
const uint16_t fn_combo[] PROGMEM      = {KC_3, KC_4, COMBO_END};
const uint16_t fn_lock_combo[] PROGMEM = {KC_3, KC_4, KC_5, COMBO_END};
const uint16_t fn_out_combo[] PROGMEM  = {KC_F4, KC_F5, KC_F6, COMBO_END};

// LANG
const uint16_t grave_combo[] PROGMEM     = {KC_SEMICOLON, KC_BACKSLASH, COMBO_END};
const uint16_t acute_combo[] PROGMEM     = {KC_Y, KC_SEMICOLON, COMBO_END};
const uint16_t cedilha_combo[] PROGMEM   = {KC_O, US_DQUO, COMBO_END};
const uint16_t circ_combo[] PROGMEM      = {KC_6, KC_J, COMBO_END};
const uint16_t tilde_combo[] PROGMEM     = {KC_5, KC_B, COMBO_END};
const uint16_t underline_combo[] PROGMEM = {KC_N, KC_E, COMBO_END};

// Custom Keys
const uint16_t use_freeze_repeat_combo[] = {KC_T, KC_G, COMBO_END};

// Gaming combos
const uint16_t gaming_enter[] = {KC_Q, KC_E, COMBO_END};
const uint16_t gaming_6[]     = {KC_ESC, KC_1, COMBO_END};
const uint16_t gaming_7[]     = {KC_1, KC_2, COMBO_END};
const uint16_t gaming_8[]     = {KC_2, KC_3, COMBO_END};
const uint16_t gaming_9[]     = {KC_3, KC_4, COMBO_END};
const uint16_t gaming_0[]     = {KC_4, KC_5, COMBO_END};
const uint16_t gaming_tab[]   = {KC_R, KC_T, COMBO_END};
const uint16_t gaming_p[]     = {KC_E, KC_R, COMBO_END};
const uint16_t gaming_i[]     = {KC_E, KC_T, COMBO_END};
const uint16_t gaming_m[]     = {KC_F, KC_G, COMBO_END};
const uint16_t gaming_f6[]    = {KC_ESC, KC_F1, COMBO_END};
const uint16_t gaming_f7[]    = {KC_F1, KC_F2, COMBO_END};
const uint16_t gaming_f8[]    = {KC_F2, KC_F3, COMBO_END};
const uint16_t gaming_f9[]    = {KC_F3, KC_F4, COMBO_END};
const uint16_t gaming_f10[]   = {KC_F4, KC_F5, COMBO_END};
const uint16_t gaming_f11[]   = {KC_F1, KC_F2, KC_F3, COMBO_END};
const uint16_t gaming_f12[]   = {KC_F2, KC_F3, KC_F4, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [ESC_COMBO]          = COMBO(esc_combo, KC_ESC),
    [ENTER_COMBO]        = COMBO(enter_combo, KC_ENTER),
    [SYM_ENTER_COMBO]    = COMBO(sym_enter_combo, KC_ENTER),
    [NAV_ENTER_COMBO]    = COMBO(nav_enter_combo, KC_ENTER),

    // Layers
    //    SYM
    [SYM_COMBO]          = COMBO(sym_combo, OSL(SYM)),
    [RSYM_COMBO]         = COMBO(rsym_combo, OSL(SYM)),
    //    NAV
    [NAV_COMBO]          = COMBO(nav_combo, MO(NAV)),
    //    MEDIA
    [MEDIA_COMBO]        = COMBO(media_combo, OSL(MEDIA)),
    [MEDIA_LOCK_COMBO]   = COMBO(media_lock_combo, TG(MEDIA)),
    [MEDIA_OUT_COMBO]    = COMBO(media_out_combo, TG(MEDIA)),
    //    FN
    [FN_COMBO]           = COMBO(fn_combo, OSL(FN)),
    [FN_LOCK_COMBO]      = COMBO(fn_lock_combo, TG(FN)),
    [FN_OUT_COMBO]       = COMBO(fn_out_combo, TG(FN)),

    // Lang
    [GRAVE_COMBO]        = COMBO(grave_combo, US_GRV),
    [CEDILHA_COMBO]      = COMBO(cedilha_combo, US_CCED),
    [ACUTE_COMBO]        = COMBO(acute_combo, US_ACUT),
    [CIRC_COMBO]         = COMBO(circ_combo, US_DCIR),
    [TILDE_COMBO]        = COMBO(tilde_combo, US_DTIL),
    [UNDERLINE_COMBO]    = COMBO(underline_combo, KC_UNDERSCORE),

    // Custom
    [USE_FREEZE_REPEAT]  = COMBO(use_freeze_repeat_combo, FREEZE_REP_TOG),

    // Gaming
    [GMG_ENTER] = COMBO(gaming_enter, KC_ENTER),
    [GMG_6]   = COMBO(gaming_6, KC_6),
    [GMG_7]   = COMBO(gaming_7, KC_7),
    [GMG_8]   = COMBO(gaming_8, KC_8),
    [GMG_9]   = COMBO(gaming_9, KC_9),
    [GMG_0]   = COMBO(gaming_0, KC_0),
    [GMG_F6]  = COMBO(gaming_f6, KC_F6),
    [GMG_F7]  = COMBO(gaming_f7, KC_F7),
    [GMG_F8]  = COMBO(gaming_f8, KC_F8),
    [GMG_F9]  = COMBO(gaming_f9, KC_F9),
    [GMG_F10] = COMBO(gaming_f10, KC_F10),
    [GMG_F11] = COMBO(gaming_f11, KC_F11),
    [GMG_F12] = COMBO(gaming_f12, KC_F12),
    [GMG_TAB] = COMBO(gaming_tab, KC_TAB),
    [GMG_I]   = COMBO(gaming_i, KC_I),
    [GMG_P]   = COMBO(gaming_p, KC_P),
    [GMG_M]   = COMBO(gaming_m, KC_M),
};
// clang-format on

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [BASE] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        --------------------------------------------------------------------------- */
/*   ||     DBG     |     1     |     2     |     3     |     4     |     5   ||       ||        6    |     7    |     8    |     9     |     0     |              | */
/*   || */ DB_TOGG  ,  KC_1     ,  KC_2     ,  KC_3     ,  KC_4     ,  KC_5    ,              KC_6    ,  KC_7    ,  KC_8    ,  KC_9     ,  KC_0     ,     ____ ,/* |\ */
/*    --------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*   ||             |     Q     |     W     |     F     |     P     |     B   ||       ||       J    |     L     |     U    |     Y    |     ;      |     \        | */
/*   || */   ____   ,  KC_Q     ,  KC_W     ,  KC_F     ,  KC_P     ,  KC_B    ,             KC_J    ,  KC_L     ,  KC_U    ,  KC_Y    ,  US_SCLN   , US_BSLS  ,/* |\ */
/*   ---------------------------------------------------------------------------        --------------------------------------------------------------------------- */
/*   ||             |     A     |     R     |     S     |     T     |     G   ||       ||       M    |     N     |     E    |     I    |     O      |     "        | */
/*   ||*/FREEZE_REP ,  KC_A     ,  KC_R     ,  KC_S     ,  KC_T     ,  KC_G    ,             KC_M    ,  KC_N     ,  KC_E    ,  KC_I    ,    KC_O    , US_DQUO ,/* |\ */
/*   ---------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*   ||     GUI     |     Z     |     X     |     C     |     D     |     V   ||       ||       K    |     H     |     ,    |     .    |     /      |              | */
/*   ||*/KC_LEFT_GUI,  KC_Z     ,  KC_X     ,  KC_C     ,  KC_D     ,  KC_V    ,             KC_K    ,  KC_H     ,KC_COMMA  ,  KC_DOT  ,  KC_SLSH   ,    ____  ,/* |\  */
/*   ---------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*                                                ||    SPC    | REPEAT KEY   ||       || ALT REPEAT     |  OSL MOD    || */
/*                                                ||*/ KC_SPACE, CUSTOM_REPEAT ,        ALT_CUSTOM_REPEAT,  OSL(MOD)// ||
/*                                                 -----------------------------       ||-------------------------- */
    ),
    [MOD] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        ---------------------------------------------------------------------------------- */
/*   ||             |           |           |           |           |         ||       ||             |          |                |           |           |              | */
/*   || */   ____   ,  ____     ,  ____     ,  ____     ,  ____     ,  ____    ,              ____    ,  ____    ,  ____          ,  ____     ,  ____     ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------       ||--------------------------------------------------------------------------------- */
/*   ||             |           |           |           |           |         ||       ||   GAMING    |           | RGB TOG       |          |            |              | */
/*   || */   ____   ,  ____     ,  ____     ,  ____     ,   ____    ,  ____    ,          DF(GAMING)  ,  ____     , RGB_CTRL_TOG  ,   ____   ,    ____    ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------        ---------------------------------------------------------------------------------- */
/*   ||             |  OSM_ALT  | OSM_LCTRL |OSM_LSHIFT |    TAB    |         ||       ||             |  BSPACE   |               |          |            |              | */
/*   ||*/    ____   ,  OSM_ALT  , OSM_LCTRL ,OSM_LSHIFT ,  KC_TAB   ,  ____    ,             ____     ,  KC_BSPC  ,   ____        ,   ____   ,    ____    ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------       ||--------------------------------------------------------------------------------- */
/*   ||             |           |           | Caps Word |           |         ||       ||             |           |               |          |            |              | */
/*   || */   ____   ,  ____     ,  ____     ,  CW_TOGG  ,  ____     ,  ____    ,             ____     ,  ____     ,   ____        ,   ____   ,    ____    ,    ____  ,/* |\  */
/*   ---------------------------------------------------------------------------       ||--------------------------------------------------------------------------------- */
/*                                                ||           |              ||       ||             |               || */
/*                                                ||*/ ____    ,      ____     ,               ____   ,    ____    // ||
/*                                                 -----------------------------       ||-------------------------- */
    ),
    [SYM] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        --------------------------------------------------------------------------- */
/*   ||             |           |           |           |           |         ||       ||             |          |          |           |           |              | */
/*   || */   ____   ,  ____     ,  ____     ,  ____     ,  ____     ,  ____    ,              ____    ,  ____    ,  ____    ,  ____     ,  ____     ,    ____  ,/* |\ */
/*    --------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*   ||             |           |     {     |     }     |    0      |    $    ||       ||     %      |    &      |    @     |    #     |     `      |              | */
/*   || */   ____   ,  ____     ,  KC_LCBR  ,  KC_RCBR  ,  KC_0     ,  KC_DLR  ,             KC_PERC ,  KC_AMPR  ,  KC_AT   ,  KC_HASH ,    US_GRV  ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------        --------------------------------------------------------------------------- */
/*   ||             |           |     (     |     )     |     [     |    ]    ||       ||     +      |    -      |    =     |    *     |      /     |              | */
/*   ||*/    ____   ,  ____     ,  KC_LPRN  ,  KC_RPRN  ,  KC_LBRC  ,  KC_RBRC ,             KC_PLUS ,  KC_MINUS , KC_EQUAL ,  KC_ASTR ,  KC_SLASH  ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*   ||             |           |           |           |           |         ||       ||            |           |    <     |    >     |            |              | */
/*   || */   ____   ,  ____     ,  ____     ,  ____     ,  ____     ,  ____    ,             ____    ,  ____     ,   KC_LT  ,   KC_GT  ,    ____    ,    ____  ,/* |\  */
/*   ---------------------------------------------------------------------------       ||-------------------------------------------------------------------------- */
/*                                                ||           |              ||       ||                |   LAYER OFF   || */
/*                                                ||*/ ____    ,      ____     ,               ____      ,    QLO     // ||
/*                                                 -----------------------------       ||-------------------------- */
    ),
    [NAV] = LAYOUT_voyager(
/*   -------------------------------------------------------------------------------------        ------------------------------------------------------------------------------------ */
/*   ||             |              |              |            |              |         ||       ||         |              |              |            |              |              | */
/*   || */   ____   ,  ____        ,  ____        ,  ____      ,     ____     ,  ____    ,           ____   ,  ____        ,  ____        ,  ____      ,     ____     ,  ____    ,/* |\ */
/*    ------------------------------------------------------------------------------------       ||----------------------------------------------------------------------------------- */
/*   ||             |  C-Left      |   C-Down     |   C-Up     |   C-Right    |         ||       ||         |  C-Left      |   C-Down     |   C-Up     |   C-Right    |              | */
/*   || */   ____   , LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP),LCTL(KC_RIGHT),  ____    ,           ____   , LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP),LCTL(KC_RIGHT),  ____    ,/* |\  */
/*   -------------------------------------------------------------------------------------       ||----------------------------------------------------------------------------------- */
/*   ||             |   Left       |   Down       |    Up      |   Right      |         ||       ||         |   Left       |   Down       |    Up      |   Right      |              | */
/*   ||*/    ____   ,  KC_LEFT     , KC_DOWN      ,   KC_UP    ,  KC_RIGHT    ,  ____    ,           ____   ,  KC_LEFT     , KC_DOWN      ,   KC_UP    ,  KC_RIGHT    ,  ____    ,/* |\ */
/*   -------------------------------------------------------------------------------------       ||-----------------------------------------------------------------------------------*/
/*   ||             |  Home        |   PgDown     |   PgUp     |   End        |         ||       ||         |  Home        |   PgDown     |   PgUp     |   End        |              | */
/*   || */   ____   ,  KC_HOME     ,  KC_PGDN     ,  KC_PGUP   ,  KC_END      ,  ____    ,           ____   ,  KC_HOME     ,  KC_PGDN     ,  KC_PGUP   ,  KC_END      ,  ____    ,/* |\ */
/*   -------------------------------------------------------------------------------------        ------------------------------------------------------------------------------------*/
/*                                                       ||   LSHIFT        |           ||       ||                |   LAYER OFF   || */
/*                                                       ||*/ KC_LEFT_SHIFT ,   ____     ,               ____      ,   QLO      // ||
/*                                                        --------------------------------       ||-------------------------- */
    ),
    [MEDIA] = LAYOUT_voyager(
/*   -------------------------------------------------------------------------------------       ------------------------------------------------------------------------------------ */
/*   ||           |         |              |            |              |                ||       ||         |              |              |            |              |              | */
/*   || */ ____   ,  ____   ,    ____      ,  ____      ,     ____     ,     ____        ,           ____   ,  ____        ,  ____        ,  ____      ,     ____     ,  ____    ,/* |\ */
/*    ------------------------------------------------------------------------------------       ||----------------------------------------------------------------------------------- */
/*   ||           |         |  MEDIA STOP  | MEDIA PREV |  MEDIA NEXT  |      PLAY      ||       ||         |              |              |            |              |              | */
/*   || */ ____   ,  ____   ,  MEDIA_STOP  , MEDIA_PREV ,  MEDIA_NEXT  ,    MEDIA_PLAY   ,           ____   ,     ____     ,     ____     ,     ____   ,    ____      ,  ____    ,/* |\ */
/*   -------------------------------------------------------------------------------------      ------------------------------------------------------------------------------------*/
/*   ||           |         |    VOL DOWN  |    VOL UP  |   MUTE       |                ||       ||         |              |              |            |              |              | */
/*   ||*/  ____   ,  ____   ,    VOL_DOWN  ,    VOL_UP  ,  VOL_MUTE    ,      ____       ,           ____   ,     ____     ,     ____     ,    ____    ,      ____    ,  ____    ,/* |\ */
/*   -------------------------------------------------------------------------------------       ||-----------------------------------------------------------------------------------*/
/*   ||           |         |              |            |              |                ||       ||         |              |              |            |              |              | */
/*   || */ ____   ,  ____   ,    ____      ,  ____      ,     ____     ,      ____       ,           ____   ,     ____     ,     ____     ,    ____    ,      ____    ,  ____    ,/* |\ */
/*   -------------------------------------------------------------------------------------       ||-----------------------------------------------------------------------------------*/
/*                                                          ||           |              ||       ||                |   LAYER OFF   || */
/*                                                          ||*/ ____    ,      ____     ,               ____      ,   QLO      // ||
/*                                                           -----------------------------       ||--------------------------------- */
    ),
    [FN] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        --------------------------------------------------------------------------------- */
/*   ||             |           |    F10    |   F11     |    F12    |         ||       ||             |                |          |           |           |              | */
/*   || */   ____   ,  ____     ,  KC_F10   ,  KC_F11   ,  KC_F12   ,  ____    ,              ____    ,  ____          ,  ____    ,  ____     ,  ____     ,    ____  ,/* |\ */
/*    --------------------------------------------------------------------------       ||-------------------------------------------------------------------------------- */
/*   ||             |           |    F1     |    F2     |    F3     |         ||       ||             |                |          |           |           |              | */
/*   || */   ____   ,  ____     ,   KC_F1   ,   KC_F2   ,  KC_F3    ,  ____    ,              ____    ,  ____          ,  ____    ,  ____     ,  ____     ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------       ||-------------------------------------------------------------------------------- */
/*   ||             |           |    F4     |    F5     |    F6     |         ||       ||             |      PRINT     |          |           |           |              | */
/*   ||*/    ____   ,  ____     ,  KC_F4    ,   KC_F5   ,   KC_F6   ,  ____    ,              ____    , KC_PRINT_SCREEN,  ____    ,  ____     ,  ____     ,    ____  ,/* |\ */
/*   ---------------------------------------------------------------------------       ||--------------------------------------------------------------------------------- */
/*   ||             |           |    F7     |    F8     |   F9      |         ||       ||            |                 |          |          |            |              | */
/*   || */   ____   ,  ____     ,  KC_F7     ,  KC_F8   ,  KC_F9    ,  ____    ,             ____    ,  ____           ,   ____   ,   ____   ,    ____    ,    ____  ,/* |\  */
/*   ---------------------------------------------------------------------------       ||--------------------------------------------------------------------------------- */
/*                                                ||           |              ||       ||                |   LAYER OFF   || */
/*                                                ||*/ ____    ,      ____     ,               ____      ,    QLO     // ||
/*                                                 -----------------------------       ||-------------------------- */
    ),
    [GAMING] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        ------------------------------------------------------------------------------ */
/*   ||      ESC    |     1     |     2     |     3     |     4     |     5   ||       ||        6    |     7     |     8     |     9     |     0     |  BACKSPACE   | */
/*   || */ KC_ESC   ,  KC_1     ,  KC_2     ,  KC_3     ,  KC_4     ,  KC_5    ,              KC_6    ,  KC_7     ,  KC_8     ,  KC_9     ,  KC_0     ,  KC_BSPC ,/* |\*/
/*    --------------------------------------------------------------------------        ------------------------------------------------------------------------------ */
/*   ||      CTRL   |    Q      |    W      |    E      |    R      |   T     ||       ||      Y      |    U      |    I      |    O      |    P      |   TAB        | */
/*   || */ KC_LCTL  ,   KC_Q    ,  KC_W     ,   KC_E    ,   KC_R    ,  KC_T    ,             KC_Y     ,   KC_U    ,  KC_I     ,   KC_O    ,   KC_P    ,  KC_TAB  ,/* |\*/
/*   ---------------------------------------------------------------------------       ------------------------------------------------------------------------------- */
/*   ||     SHIFT   |    A      |    S      |    D      |    F      |   G     ||       ||     H       |    J      |    K      |    L      |    ;      |              | */
/*   ||*/ KC_LSFT   ,  KC_A     ,  KC_S     ,   KC_D    ,   KC_F    ,  KC_G    ,            KC_H      ,  KC_J     ,  KC_K     ,   KC_L    , KC_SCLN   ,  ____    ,/* |\*/
/*   ---------------------------------------------------------------------------       ------------------------------------------------------------------------------- */
/*   ||  LEFT ALT   |   Z       |    X      |    C      |    V      |   B     ||       ||     N       |   M       |    ,      |    .      |    /      |   SWAP HANDS | */
/*   || */ KC_LALT  ,  KC_Z     ,   KC_X    ,   KC_C    ,   KC_V    ,  KC_B    ,            KC_N      ,  KC_M     , KC_COMM   ,   KC_DOT  , KC_SLSH   ,    SH_TT ,/* |\*/
/*   ---------------------------------------------------------------------------       ||----------------------------------------------------------------------------- */
/*                                                ||   SPACE   |  GAMING ALT  ||       ||                |   LAYER OFF   || */
/*                                                ||*/ KC_SPC  , TG(GAMING_ALT),               ____      ,   DF(BASE)
/*                                                 -----------------------------       ||-------------------------- */
    ),
    [GAMING_ALT] = LAYOUT_voyager(
/*   ---------------------------------------------------------------------------        ------------------------------------------------------------------------------ */
/*   ||             |    F1     |    F2     |    F3     |    F4     |     F5   ||       ||             |           |           |           |           |              | */
/*   || */ ____     ,  KC_F1    ,  KC_F2    ,  KC_F3    ,  KC_F4    ,  KC_F5   ,              ____    ,  ____     ,  ____     ,  ____     ,  ____     ,  ____ ,   /* |\*/
/*    --------------------------------------------------------------------------        ------------------------------------------------------------------------------ */
/*   ||             |           |   UP      |           |           |         ||       ||             |           |           |           |           |              | */
/*   || */ ____     ,   ____    ,  KC_UP    ,   ____    ,   ____    ,  ____    ,             ____     ,   ____    ,  ____     ,   ____    ,   ____    ,  ____  ,/*   |\*/
/*   ---------------------------------------------------------------------------       ------------------------------------------------------------------------------- */
/*   ||             |  LEFT     |   DOWN    |   RIGHT   |           |         ||       ||             |           |           |           |           |              | */
/*   ||*/ ____      ,  KC_LEFT  ,  KC_DOWN  , KC_RIGHT  ,   ____    ,  ____    ,            ____      ,  ____     ,  ____     ,   ____    ,    ____   ,  ____    ,/* |\*/
/*   ---------------------------------------------------------------------------       ------------------------------------------------------------------------------- */
/*   ||             |           |           |           |           |         ||       ||             |           |           |           |           |             | */
/*   || */ ____     ,  ____     ,   ____    ,   ____    ,   ____    ,  ____    ,            ____      ,  ____     ,    ____   ,   ____    ,    ____   ,    ____ ,/* |\*/
/*   ---------------------------------------------------------------------------       ||----------------------------------------------------------------------------- */
/*                                                ||           |              ||       ||                |   LAYER OFF   || */
/*                                                ||*/ ____    ,TG(GAMING_ALT) ,               ____      ,   QLO
/*                                                 -----------------------------       ||-------------------------- */
    ),

    // clang-format on
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_NONE);
}

// clang-format off
const uint8_t PROGMEM keypos_to_led_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_voyager(
/*   --------------------------------------------------         ------------------------------------------------------------*/
/*   || */    0   ,   1  ,   2  ,   3  ,   4  ,   5   ,            24    , 25  ,  26    ,  27     ,  28     ,    29  ,/* |\ */
/*    -----------------------------------------------||         ||----------------------------------------------------------*/
/*   || */    6   ,   7  ,   8  ,   9  ,  10  ,  11   ,            30    , 31  ,  32    ,  33     ,  34     ,    35  ,/* |\ */
/*   ------------------------------------------------||         ||----------------------------------------------------------*/
/*   ||*/    12   ,  13  ,  14  ,  15  ,  16  ,  17   ,            36    , 37  ,  38    ,  39     ,  40     ,    41  ,/* |\ */
/*   ------------------------------------------------||         ||----------------------------------------------------------*/
/*   || */   18   ,  19  ,  20  ,  21  ,  22  ,  23   ,            42    , 43  ,   44   ,   45   ,    46    ,    47  ,/* |\ */
/*   ------------------------------------------------||         ||----------------------------------------------------------*/
/*                                 ||*/   48  ,  49   ,            50    ,  51    // ||
/*                                  -------------------         ---------------------*/
    );

#define QK_ONE_SHOT_MOD_COUNT 8
#define QK_LAYERS_SUPPORTING_LEDS 6

const uint8_t PROGMEM osm_keys_led[QK_LAYERS_SUPPORTING_LEDS][QK_ONE_SHOT_MOD_COUNT] = {
    [BASE] = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
    [MOD]  = {       14,        15,        13, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
    [SYM]  = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
    [NAV]  = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
    [MEDIA]= {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
    [FN]   = {UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX, UINT8_MAX},
};
// clang-format on

bool rgb_matrix_indicators_user(void) {
    manage_blinking_keys();
    return true;
}

keyrecord_t frozen_key_repeat = {0};
uint16_t    frozen_mod_repeat = 0;
bool        freeze_key_repeat = false;
bool        is_alt_tab_active = false;

void matrix_scan_user(void) {
#ifdef LEADER_COMPOSE_ENABLE
    leader_compose_task();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n",
    //         keycode, record->event.key.col, record->event.key.row, record->event.pressed,
    //         record->event.time, record->tap.interrupted, record->tap.count);
    // keyrecord_t registered_record = {0};
    switch (keycode) {
        case RGB_CTRL_TOG:
            disable_all();
            return false;
        case QUICK_LAYER_OFF:
            if (record->event.pressed) {
                layer_off(get_highest_layer(layer_state));
            }
            return false;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX: {
            if (record->event.pressed) {
                action_t      action = action_for_keycode(keycode);
                uint8_t       shift  = action.layer_bitop.part * 4;
                layer_state_t bits   = ((layer_state_t)action.layer_bitop.bits) << shift;
                layer_state_t mask =
                    (action.layer_bitop.xbit) ? ~(((layer_state_t)0xf) << shift) : 0;
                switch (action.layer_bitop.op) {
                    case OP_BIT_AND:
                        layer_and(bits | mask);
                        break;
                    case OP_BIT_OR:
                        layer_or(bits | mask);
                        break;
                    case OP_BIT_XOR:
                        layer_xor(bits | mask);
                        break;
                    case OP_BIT_SET:
                        layer_state_set(bits | mask);
                        break;
                }
            }
            return false;
        }
    }

#ifdef LEADER_COMPOSE_ENABLE
    return process_leader_compose(keycode, record);
#endif
    return true;
}

uint8_t previous_active_oneshot_mods = 0;
void    process_blinking_for_one_shot_mods(uint16_t keycode, keyrecord_t *record) {
    uint8_t led_index = keypos_to_led_map[record->event.key.row][record->event.key.col];
    switch (keycode) {
        case OSM_ALT:
        case OSM_LSHIFT:
        case OSM_LCTRL:
            if (record->event.pressed) {
                RGB rgb = {RGB_YELLOW};
                enable_blinking_for(led_index, rgb, 500, UINT32_MAX);
                break;
            }
        default: {
            uint8_t active_oneshot_mods = get_oneshot_mods();
            if (previous_active_oneshot_mods == 0 && active_oneshot_mods == 0) {
                break;
            }
            for (size_t i = 0; i < QK_ONE_SHOT_MOD_COUNT; i++) {
                for (size_t j = 0; j < QK_LAYERS_SUPPORTING_LEDS; j++) {
                    uint8_t osm_led     = osm_keys_led[j][i];
                    uint8_t checked_mod = 1 << i;
                    if (osm_led == UINT8_MAX) {
                        continue;
                    }
                    dprintf("prev active: %u, active: %u, mod: %u, led: %u\n",
                               previous_active_oneshot_mods, active_oneshot_mods, checked_mod,
                               osm_led);
                    if ((active_oneshot_mods & checked_mod) == 0 &&
                        (previous_active_oneshot_mods & checked_mod) != 0) {
                        RGB color = {0, 10, 100};
                        enable_blinking_for(led_index, color, 2500, 3);
                        enable_blinking_for(osm_led, color, 2500, 3);
                    }
                }
            }
            previous_active_oneshot_mods = active_oneshot_mods;
            break;
        }
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_CONTROL_ENABLE
    init_rgb_state();
    process_blinking_for_one_shot_mods(keycode, record);
#endif

    if (IS_QK_ONE_SHOT_MOD(keycode) && is_oneshot_layer_active() && record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode,
                          keyrecord_t *record) {
    if (layer_state_cmp(layer_state | default_layer_state, GAMING) ||
        layer_state_cmp(layer_state | default_layer_state, GAMING_ALT)) {
        return combo_index >= GMG_ENTER;
    }
    return combo_index < GMG_ENTER;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    switch (keycode) {
        case FREEZE_REPEAT_REGISTER:
        case CUSTOM_REPEAT:
        case ALT_CUSTOM_REPEAT:
            return false;
    }
    return true;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & (MOD_BIT_LSHIFT | MOD_BIT_RSHIFT));
    bool alted   = (mods & MOD_BIT_LALT);
    bool ctrled  = (mods & (MOD_BIT_LCTRL | MOD_BIT_RCTRL));
    switch (keycode) {
        case KC_TAB:
            if (shifted && alted) {
                return LALT(KC_TAB);
            } else if (ctrled && shifted) {
                return C(KC_TAB);
            } else if (shifted) {
                return KC_TAB;
            } else if (alted) {
                return LSA(KC_TAB);
            } else if (ctrled) {
                return C(S(KC_TAB));
            } else {
                return S(KC_TAB);
            }
    }
    return KC_TRNS;
}

uint8_t locked_mods = 0;

void leader_compose_on_key_release_user(uint16_t keycode) {
    dprintln("leader compose on key release user");
    if (keycode == KC_N && leader_compose_release_sequence_one_key(KC_N)) {
        unregister_code(KC_BACKSPACE);
    } else if (keycode == KC_R && leader_compose_release_sequence_two_keys(KC_SPACE, KC_R)) {
        dprintln("R released");
        unregister_mods(MOD_BIT_LCTRL);
    }
}
void leader_compose_on_timeout_sequences(void) {
    if (leader_compose_sequence_two_keys(KC_SPACE, KC_R)) {
        register_mods(MOD_BIT_LCTRL);
        locked_mods |= MOD_BIT_LCTRL;
        set_last_mods(MOD_BIT_LCTRL);
        leader_compose_register_sequence_held(KC_SPACE, KC_R, 0, 0, 0);
    } else if (leader_compose_sequence_two_keys(KC_SPACE, KC_A)) {
        register_mods(MOD_BIT_LALT);
        locked_mods |= MOD_BIT_LALT;
        set_last_mods(MOD_BIT_LALT);
    } else {
        clear_oneshot_locked_mods();
        unregister_mods(locked_mods);
        locked_mods = 0;
    }
}

bool leader_compose_final_sequences(void) {
    // SHIFT
    if (leader_compose_sequence_one_key(KC_S)) {
        set_oneshot_mods(MOD_BIT_LSHIFT);
        set_last_mods(MOD_BIT_LSHIFT);
    } else if (leader_compose_sequence_two_keys(KC_SPACE, KC_S)) {
        caps_word_toggle();
    }
    // CTRL
    else if (leader_compose_sequence_one_key(KC_R)) {
        set_oneshot_mods(MOD_BIT_LCTRL);
        set_last_mods(MOD_BIT_LCTRL);
    } // ALT
    else if (leader_compose_sequence_one_key(KC_A)) {
        set_oneshot_mods(MOD_BIT_LALT);
        set_last_mods(MOD_BIT_LALT);
    }
    // Ctrl + Shift (avoiding accidental press on ctrl s or capital r)
    else if (leader_compose_sequence_three_keys(KC_SPACE, KC_R, KC_S)) {
        set_oneshot_mods(MOD_MASK_CS);
        set_last_mods(MOD_MASK_CS);
    }
    // Ctrl + Alt (avoiding accidental press on ctrl a)
    else if (leader_compose_sequence_three_keys(KC_SPACE, KC_R, KC_A)) {
        set_oneshot_mods(MOD_MASK_CA);
        set_last_mods(MOD_MASK_CA);
    } else if (leader_compose_sequence_one_key(KC_T)) {
        SEND_STRING(SS_TAP(X_TAB));
        set_last_keycode(KC_TAB);
    } else if (leader_compose_sequence_one_key(KC_N)) {
        register_code(KC_BACKSPACE);
        set_last_keycode(KC_BACKSPACE);
        leader_compose_register_sequence_held(KC_N, 0, 0, 0, 0);
    } else {
        return false;
    }
    return true;
}
