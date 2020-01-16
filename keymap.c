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
#define RUS     1

#define FN     2
#define NAV     3


enum custom_keycodes {
  SMILEK = SAFE_RANGE,
  QMKURL,
  LANG,
  MY_OTHER_MACRO,
  RUS_LAT,
// };
// enum shifted_keycodes {
  AKM_1_9,
//   AKM_1_10,
//   AKM_1_11,
//   AKM_1_12,
//   AKM_1_13,
  AKM_1_14,

  AKM_2_22,
  AKM_2_23,

  AKM_3_11,

  AKM_4_11,

  M_CYR_ER,
};


// const int len_enum = end - start + 1;
// uint16_t alt_keymap[2][len_enum] = {
uint16_t alt_keymap[2][10] = {
        {
            KC_LEFT_PAREN,
            // KC_UNDERSCORE,
            // KC_MINUS,
            // KC_EQUAL,
            // KC_DOUBLE_QUOTE,
            KC_LEFT_ANGLE_BRACKET,

            KC_LBRACKET,
            KC_LEFT_CURLY_BRACE,

            KC_COLON,

            KC_SLASH,

            // CYR
            KC_M,
        },
        {
            KC_RIGHT_PAREN,
            // KC_UNDERSCORE,
            // KC_MINUS,
            // KC_EQUAL,
            // KC_BSLASH,
            KC_RIGHT_ANGLE_BRACKET,

            KC_RBRACKET,
            KC_RIGHT_CURLY_BRACE,

            KC_SCOLON,

            KC_PIPE,

            // CYR
            KC_RBRACKET,
        }
};


uint16_t key_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
    case RUS_LAT:
        if (record->event.pressed)
            {
                key_timer = timer_read();
                register_mods(MOD_LSFT);
            }
        else
            {
                unregister_mods(MOD_LSFT);
                if (timer_elapsed(key_timer) < 500)
                    {
                    layer_invert(RUS);
                    tap_code16(C(G(KC_NO)));
                    }
                else
                    {
                    }
            }
        return false;
        break;

    uint8_t mod_state = get_mods();
    case AKM_1_9 ... M_CYR_ER:
      if (record->event.pressed)
      {
        mod_state = get_mods() & MOD_MASK_SHIFT;
        clear_mods();
        if(mod_state)
        {
          tap_code16(alt_keymap[1][keycode - AKM_1_9]);
        }
        else
        {
          tap_code16(alt_keymap[0][keycode - AKM_1_9]);
        }
        set_mods(mod_state);
      }
      return false;

    case SMILEK:
        if (record->event.pressed) {
        // when keycode SMILEK is pressed
        SEND_STRING("¯\\_(ツ)_/¯");
        } else {
        // when keycode SMILEK is released
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
                layer_invert(RUS);
                tap_code(KC_CAPSLOCK);
        }
        break;

  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAT] = LAYOUT(
        KC_GRAVE ,          KC_EXCLAIM,  KC_AT,  KC_HASH, KC_DOLLAR, KC_PERCENT, KC_CIRCUMFLEX, KC_QUESTION, KC_ASTERISK, AKM_1_9, KC_UNDERSCORE, KC_MINUS, KC_EQUAL,  KC_DOUBLE_QUOTE, AKM_1_14,
        KC_TAB   ,          KC_Q,        KC_W,   KC_E,    KC_R,      KC_T,       KC_Y,          KC_U,        KC_I,        KC_O,    KC_P,          AKM_2_22, AKM_2_23,  KC_BSPC,
        KC_GESC  ,          KC_A,        KC_S,   KC_D,    KC_F,      KC_G,       KC_H,          KC_J,        KC_K,        KC_L,    AKM_3_11,      KC_QUOT,  KC_ENT,
        SFT_T(KC_CAPS),XXXXXXX,  KC_Z,   KC_X,   KC_C,    KC_V,      KC_B,       KC_N,          KC_M,        KC_COMM,     KC_DOT,  AKM_4_11,      KC_UP,    RUS_LAT,
        KC_LCTL  ,KC_LGUI,  KC_LALT,             MO(FN),             KC_ENT,                    KC_SPC,      MO(FN),      KC_APP,  KC_LEFT,       KC_DOWN,  KC_RIGHT),

    [RUS] = LAYOUT(
        _______,          _______,      UC(0x0040), KC_AT, _______,  _______,     _______,    S(KC_7),     _______,     _______,  _______,      _______,  _______,     _______,   _______,
        _______,          KC_Q,         KC_W,    KC_E,    KC_R,     KC_T,        KC_Y,          KC_U,        KC_I,        KC_O,     KC_P,         KC_LBRC,  S(KC_SLASH), _______,
        _______,          KC_A,         KC_S,    KC_D,    KC_F,     KC_G,        KC_H,          KC_J,        KC_K,        KC_L,     KC_SCLN,      KC_QUOT,  _______,
        _______,XXXXXXX,  KC_Z,         KC_X,    KC_C,    KC_V,     KC_B,        KC_N,          M_CYR_ER,    KC_COMM,     KC_DOT,   KC_SLSH,      _______,  _______,
        _______,_______,  _______,               _______,           _______,                    _______,     _______,     _______,  _______,      _______,  _______),

    [FN] = LAYOUT(
        RESET  ,          KC_F1,        KC_F2,   KC_F3,   KC_F4,    KC_F5,       KC_F6,         KC_F7,       KC_F8,       KC_F9,    KC_F10,       KC_F11,         KC_F12,      KC_INS,    KC_PAUS,
        _______,          KC_HOME,      KC_UP,   KC_END,   _______,  _______,     _______,       KC_KP_MINUS, KC_7,        KC_8,     KC_9,         KC_KP_ASTERISK, KC_KP_SLASH, _______,
        KC_CAPSLOCK,      KC_LEFT,      KC_DOWN, KC_RIGHT, KC_DEL,   KC_HOME,     KC_END,        KC_BSPC,     KC_4,        KC_5,     KC_6,         KC_KP_EQUAL,    KC_PDOT,
        LALT(KC_LSHIFT),XXXXXXX,  KC_DOWN,      KC_PGUP, _______, _______,  _______,    _______,       KC_KP_PLUS,  KC_1,        KC_2,     KC_3,         _______,        _______,
        _______,_______,  _______,               _______,           TO(LAT),                    KC_0,        _______,     _______,  _______,      _______,        _______),

    [NAV] = LAYOUT(
        SMILE  ,          _______,     _______,   UNICODE_MODE_LNX,   UNICODE_MODE_WIN,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_P0,   RESET,
        _______,          _______,     KC_VOLU,   _______,    RUB_SIGN,   _______,   _______,   KC_PGUP,   _______,   KC_UP,   _______,   _______,   _______,   _______,   _______,
        KC_MPRV,          KC_VOLD,     KC_MNXT,   KC_DEL,     KC_HOME,   KC_END,   KC_BSPC,   KC_LEFT,   KC_DOWN,   KC_RGHT,   _______,   _______,
        _______,XXXXXXX,  SMILEK,      QMKURL,    MY_OTHER_MACRO,   KC_PGDN,   _______,   _______,   KC_PGDN,   _______,   _______,   _______,   _______,   _______,
        _______,_______,  _______,     _______,    _______,   _______,   _______,   _______,   _______,   _______,   _______),

};
