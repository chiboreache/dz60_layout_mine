#include QMK_KEYBOARD_H
#include "./keycodes/signs.h"

/* Standard arrangement / LAYOUT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │
 * ├────┼───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
 * │40  │41  │43  │44      │46  │48        │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
/ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
/ k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
/ k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
/ k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, \
/ k40, k41,      k43, k44,      k46,      k48,      k4a, k4b, k4c, k4d, k4e  \
*/
#define LAT     0
#define LAT_UP  1

#define RUS     2
#define RUS_UP  3

#define NUM     4
#define NAV     5



enum unicode_names {
    MY_AMPR,
    MY_7
};

// first 128 entries in the map can be used with the XP feature
const uint32_t PROGMEM unicode_map[] = {
    [MY_AMPR]  = 0x0026,  // &
    [MY_7] = 0x0037,  // 7
};

// creating a handy shortname to use in keymap; not strictly necessary
#define AMPR_7 XP(MY_AMPR, MY_7)




enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL,
  LANG,
  SHIFT,
  MY__7,
  MY_OTHER_MACRO
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  const uint8_t mod_state = get_mods();
  switch (keycode) {
    case MY__7:
        if (record->event.pressed) {
            if(get_mods() & MOD_MASK_SHIFT)
            {
                clear_mods();
                tap_code(KC_7);
                set_mods(mod_state);
            } else {
                tap_code(KC_G);
            }
        }
        break;

    case QMKBEST:
        if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
        } else {
        // when keycode QMKBEST is released
        }
        break;

    case QMKURL:
        if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/\n");
        } else {
        // when keycode QMKURL is released
        }
        break;

    case MY_OTHER_MACRO:
        if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ac")); // selects all and copies
        }
        break;

    case LANG:
        if (record->event.pressed) {
                tap_code(KC_CAPSLOCK);
                layer_invert(LAT_UP);
        }
        break;

    // case SHIFT:
    //   if (record->event.pressed) {
    //             tap_code16(LM(LAT_UP, MOD_LSFT));
    //   } else {
    //             layer_invert(LAT);
    //   }
    //   break;


  }
  return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAT] = LAYOUT(
        TT(NUM),     S(KC_1),  S(KC_2),  S(KC_3),  S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9),  S(KC_0),  KC_UNDS,  KC_COLN,  KC_DQUO,  KC_BSLS,
        KC_TAB,           KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  S(KC_LBRC),  KC_BSPC,
        KC_GESC,            KC_A,       KC_S,    KC_D,    KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSHIFT,XXXXXXX,  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  AMPR_7,  TT(LAT_UP),
        KC_LCTL,        KC_LGUI,          KC_LALT,    MO(NAV),    KC_ENT,                 KC_SPC,                 MO(NUM),    KC_GRV,   TG(NUM),    KC_RGHT,  KC_WH_D),

    [LAT_UP] = LAYOUT(
        TO(LAT),     KC_1,  KC_2,  KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,  KC_0,  KC_UNDS,  KC_COLN,  KC_DQUO,  KC_BSLS,
        _______,           KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_LBRC,  _______,
        _______,            KC_A,       KC_S,    KC_D,    KC_F,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  _______,
        KC_LSHIFT,XXXXXXX,  KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  _______,  _______,
        _______,        _______,          _______,    _______,    _______,                 _______,                 _______,    _______,   _______,    _______,  _______),

    [NUM] = LAYOUT(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,    KC_F9,   KC_F10,  KC_F11,     KC_F12,     KC_INS,    KC_PAUS,
        TO(LAT),    RGB_TOG,    RGB_MOD,    RGB_RMOD,   RGB_HUI,    RGB_HUD,    RGB_SPI,    KC_PMNS,    KC_7,     KC_8,    KC_9,    KC_PSLS,    KC_PAST,    KC_PSCR,
        _______,    RGB_SAI,    RGB_SAD,    _______,    KC_DEL,     RGB_VAI,    RGB_VAD,    KC_BSPC,    KC_4,     KC_5,    KC_6,    _______,    KC_PEQL,
        _______,    XXXXXXX,    RGB_M_P,    RGB_M_R,    RGB_M_X,    RGB_M_G,    RGB_M_SW,   RGB_SPD,    KC_PPLS,  KC_1,    KC_2,    KC_3,       KC_LEFT,    KC_RGHT,
        _______,    _______,    _______,    _______,    _______,    _______,    KC_0,       KC_PDOT,    _______,  _______, _______),

    [NAV] = LAYOUT(
        SMILE,     UC(0xBD20),  RUB_SIGN,   UNICODE_MODE_LNX,   UNICODE_MODE_WIN,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_P0,   RESET,
        _______,   _______,     KC_VOLU,   _______,    KC_PGUP,   _______,   _______,   KC_PGUP,   _______,   KC_UP,   _______,   _______,   _______,   _______,   _______,
        KC_MPRV,   KC_VOLD,     KC_MNXT,   KC_DEL,     KC_HOME,   KC_END,   KC_BSPC,   KC_LEFT,   KC_DOWN,   KC_RGHT,   _______,   _______,
        _______,   XXXXXXX,     QMKBEST,   QMKURL,    MY_OTHER_MACRO,   KC_PGDN,   _______,   _______,   KC_PGDN,   _______,   _______,   _______,   LANG,   _______,
        _______,   _______,     _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______),

};



// KEYMAP(
//  LT(1, TG(1)), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_LABK, KC_UNDS, KC_PIPE, KC_BSLS, KC_DEL,
//  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LCBR, KC_BSPC,
//  KC_GESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_COLN, KC_QUOT, KC_ENT,
//  SFT_T(KC_CAPS), _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(3),
//  KC_LCTL, KC_LGUI, KC_LALT, MO(2), KC_ENT, KC_SPC, KC_RALT, KC_F19, KC_APP, MO(1), KC_PSCR),

// KEYMAP(
//  _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
//  TO(0), _______, KC_VOLU, _______, KC_PGUP, KC_PGDN, _______, KC_MINS, KC_7, KC_8, KC_9, KC_PSLS, KC_PAST, _______,
//  _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, _______, _______, KC_4, KC_5, KC_6, _______, KC_EQL,
//  _______, _______, _______, _______, _______, KC_HOME, KC_END, _______, KC_PPLS, KC_1, KC_2, KC_3, _______, _______,
//  _______, _______, _______, _______, _______, _______, KC_0, KC_PDOT, _______, _______, _______),

// KEYMAP(
//  _______, KC_P0, KC_P0, KC_INS, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0, KC_P0,
//  _______, _______, KC_UP, _______, KC_PGUP, _______, _______, KC_PGUP, _______, KC_UP, _______, _______, _______, _______,
//  _______, M(1), KC_DOWN, M(0), KC_DEL, KC_HOME, KC_END, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
//  _______, _______, _______, _______, _______, KC_PGDN, _______, _______, KC_PGDN, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

// KEYMAP(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),



// void eeconfig_init_user(void) {
//     set_unicode_input_mode(UC_LNX);
// }
