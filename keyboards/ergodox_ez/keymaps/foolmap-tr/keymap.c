#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0
#define SYMB 1
#define MISC 2
#define TRUM 3

#define C_CDL UP(0, 1)
#define G_BRV UP(2, 3)
#define I_DOT UP(4, 5)
#define O_DIA UP(6, 7)
#define S_CDL UP(8, 9)
#define U_DIA UP(10, 11)

enum custom_keycodes {
  CLEAR = SAFE_RANGE
};

enum unicode_names {
    C_CDL_L,
    C_CDL_U,
    G_BRV_L,
    G_BRV_U,
    I_DOT_L,
    I_DOT_U,
    O_DIA_L,
    O_DIA_U,
    S_CDL_L,
    S_CDL_U,
    U_DIA_L,
    U_DIA_U,
};

const uint32_t PROGMEM unicode_map[] = {
    [C_CDL_L] = 0x00e7,
    [C_CDL_U] = 0x00c7,
    [G_BRV_L] = 0x011f,
    [G_BRV_U] = 0x011e,
    [I_DOT_L] = 0x0131,
    [I_DOT_U] = 0x0130,
    [O_DIA_L] = 0x00f6,
    [O_DIA_U] = 0x00d6,
    [S_CDL_L] = 0x015f,
    [S_CDL_U] = 0x015e,
    [U_DIA_L] = 0x00fc,
    [U_DIA_U] = 0x00dc,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: base
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |@MISC   |  1   |  2   |  3   |  4   |  5   | ESC  |           | BSPC |  6   |  7   |  8   |  9   |  0   |   @MISC|
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |MUTE    |  '   |  ,   |  .   |  P   |  Y   | TAB  |           | ENT  |  F   |  G   |  C   |  R   |  L   |    MPLY|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |@TRUM   |  A   |  O   |  E   |  U   |  I   |------|           |------|  D   |  H   |  T   |  N   |  S   |   @TRUM|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CLEAR   |  ;   |  Q   |  J   |  K   |  X   |^LSFT |           |^RSFT |  B   |  M   |  W   |  V   |  Z   |   CLEAR|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LGUI  | HOME | PGUP | PGDN | END  |                                       | LEFT | DOWN |  UP  |RIGHT |RGUI |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |@SYMB | LGUI |       | RGUI |@SYMB |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | SPC  | LCTL |SH_OS |       |SH_OS | RCTL | SPC  |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      | LALT |       | RALT |      |      |
 *                                 `--------------------'       `--------------------'
 */
[BASE] = LAYOUT_ergodox_pretty(
        OSL(MISC), KC_1,    KC_2,    KC_3,      KC_4,    KC_5,    KC_ESC,        KC_BSPC,       KC_6,     KC_7,    KC_8, KC_9,      KC_0, OSL(MISC),
        KC_MUTE,   KC_QUOT, KC_COMM, KC_DOT,    KC_P,    KC_Y,    KC_TAB,        KC_ENT,        KC_F,     KC_G,    KC_C, KC_R,      KC_L, KC_MPLY,
        OSL(TRUM), KC_A,    KC_O,    KC_E,      KC_U,    KC_I,    KC_D,          KC_H,          KC_T,     KC_N,    KC_S, OSL(TRUM),
        CLEAR,     KC_SCLN, KC_Q,    KC_J,      KC_K,    KC_X,    OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,     KC_M,    KC_W, KC_V,      KC_Z, CLEAR,
        KC_LGUI,   KC_HOME, KC_PGUP, KC_PGDN,   KC_END,  KC_LEFT, KC_DOWN,       KC_UP,         KC_RIGHT, KC_RGUI,
        OSL(SYMB), KC_LGUI, KC_RGUI, OSL(SYMB),
        SH_OS,     SH_OS,
        KC_SPC,    KC_LCTL, KC_LALT, KC_RALT,   KC_RCTL, KC_SPC
),

/* Keymap 1: symb
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |MPRV    |  !   |  @   |  #   |  $   |  %   |      |           |      |  ^   |  &   |  *   | F11  | F12  |    VOLU|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |MNXT    |  {   |  }   |  (   |  )   |  =   |------|           |------|  /   |  -   |  _   |  [   |  ]   |    VOLD|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ~   |  |   |  `   |      |           |      |  \   |  +   | DEL  | INS  |  \   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox_pretty(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        KC_MPRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_F11,  KC_F12,  KC_VOLU,
        KC_MNXT, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_EQL,  KC_SLSH, KC_MINS, KC_UNDS, KC_LBRC, KC_RBRC, KC_VOLD,
        _______, _______, _______, KC_TILD, KC_PIPE, KC_GRV,  _______, _______, KC_BSLS, KC_PLUS, KC_DEL,  KC_INS,  KC_BSLS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______,
        _______, _______, _______, _______, _______, _______
),

/* Keymap 2: misc
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MS_U |      | WH_U |      |           |      |      | ACL2 | ACL1 | ACL0 |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | MS_L | MS_D | MS_R | WH_D |------|           |------|      | BTN1 | BTN2 | BTN3 |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      | BOOT |      |           |      | BOOT | WH_L | WH_R |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MISC] = LAYOUT_ergodox_pretty(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_MS_U, _______, KC_WH_U, _______, _______, _______, KC_ACL2, KC_ACL1, KC_ACL0, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_BTN1, KC_BTN2, KC_BTN3, _______, _______,
        _______, _______, _______, _______, _______, QK_BOOT, _______, _______, QK_BOOT, KC_WH_L, KC_WH_R, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______,
        _______, _______, _______, _______, _______, _______
),

/* Keymap 3: trum
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |G_BRV |C_CDL |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |O_DIA |      |U_DIA |I_DOT |------|           |------|      |      |      |      |S_CDL |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[TRUM] = LAYOUT_ergodox_pretty(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, G_BRV,   C_CDL,   _______, _______, _______,
        _______, _______, O_DIA,   _______, U_DIA,   I_DOT,   _______, _______, _______, _______, S_CDL,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______,
        _______, _______, _______, _______, _______, _______
),

};

void clear(void) {
  clear_oneshot_mods();
  clear_oneshot_locked_mods();
  clear_keyboard();
  reset_oneshot_layer();
  layer_clear();
  layer_on(BASE);
  rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CLEAR:
        clear();
        return false;
    }
  }
  return true;
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        break;
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }

  return state;
};

void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    rgb_matrix_sethsv_noeeprom(HSV_GREEN);
  }
  if (mods & MOD_MASK_CTRL) {
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
  }
  if (mods & MOD_MASK_ALT) {
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
  }
  if (mods & MOD_MASK_GUI) {
    rgb_matrix_sethsv_noeeprom(HSV_CORAL);
  }
  if (!mods) {
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
  }
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    rgb_matrix_sethsv_noeeprom(HSV_SPRINGGREEN);
  }
  if (mods & MOD_MASK_CTRL) {
    rgb_matrix_sethsv_noeeprom(HSV_CYAN);
  }
  if (mods & MOD_MASK_ALT) {
    rgb_matrix_sethsv_noeeprom(HSV_MAGENTA);
  }
  if (mods & MOD_MASK_GUI) {
    rgb_matrix_sethsv_noeeprom(HSV_PINK);
  }
  if (!mods) {
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
  }
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}
