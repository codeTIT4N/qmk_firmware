#include QMK_KEYBOARD_H

#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute

#ifdef OLED_ENABLE
#include "demon.c"
#endif

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LCTL, KC_LGUI, KC_SPC, KC_ENT, MO(_LOWER), MO(_RAISE), KC_RALT
),

[_LOWER] = LAYOUT(
  KC_ESC,   KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_F5,               KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_BSPC,
  KC_GRV,    KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                                  KC_6,   KC_7,   KC_8,   KC_9,  KC_0,  KC_BSLS,
  KC_TAB,   XXXXXXX, KC_S,   XXXXXXX, XXXXXXX,  XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_SCLN, KC_QUOT,
  KC_LSFT, XXXXXXX, XXXXXXX, KC_C, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_MINS, KC_EQL, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                        KC_LALT, KC_LCTL, KC_LGUI, KC_SPC, KC_ENT, XXXXXXX, MO(_RAISE), KC_RALT
),

[_RAISE] = LAYOUT(
        KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TILD,  KC_EXLM,    KC_AT,    KC_HASH,    KC_DLR,    KC_PERC,                     KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_PIPE,
        KC_TAB,  XXXXXXX,    KC_S,   XXXXXXX,   KC_MS_BTN1,   KC_MS_BTN2,                       KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,   KC_COLN, KC_DQT,
        KC_LSFT,   XXXXXXX,   XXXXXXX,   KC_C,  XXXXXXX,  XXXXXXX,   KC_LCBR, KC_RCBR,  KC_UNDS,    KC_PLUS,    KC_LT, KC_GT,  KC_QUES,  KC_RSFT,
        KC_LALT, KC_LCTL, KC_LGUI, KC_SPC, KC_ENT, MO(_LOWER), XXXXXXX, KC_RALT
    ),
[_ADJUST] = LAYOUT(
        KC_MUTE,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F11, KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_anim();
    //// If you want to change the display of OLED, you need to change here
    //oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    ////oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    ////oled_write_ln(read_host_led_state(), false);
    ////oled_write_ln(read_timelog(), false);
    //oled_write_ln(read_layer_state(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
