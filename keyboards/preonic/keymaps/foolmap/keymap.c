/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum preonic_layers {
  _BASE,
  _LOWER,
  _RAISE,
};

enum preonic_keycodes {
  CLEAR = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TILD, KC_GRV,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_ESC,  KC_BSPC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_TAB,  KC_ENT,  KC_D,    KC_H,    KC_T,    KC_N,    KC_S,
  KC_SCLN, KC_Q, KC_J, KC_K, KC_X, OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
  OSL(2), OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSL(1), KC_SPC, KC_SPC, OSL(1), OSM(MOD_RCTL), OSM(MOD_RALT), OSM(MOD_RGUI), OSL(2)
),

[_LOWER] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_VOLD, KC_VOLU, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_MUTE, KC_MPLY, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_EQL,  KC_MPRV, KC_MNXT, KC_SLSH, KC_MINS, KC_UNDS, KC_LBRC, KC_RBRC,
  CLEAR,   _______, KC_TILD, KC_PIPE, KC_GRV,  _______, _______, KC_BSLS, KC_PLUS, KC_DEL,  KC_INS,  CLEAR,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______, _______, KC_F11,  KC_F12,
  _______, _______, KC_PGUP, _______, _______, _______, _______, _______, _______, KC_UP, _______, _______,
  _______, KC_HOME, KC_PGDN, KC_END,  KC_INS,  _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RESET, _______, _______, _______, _______, _______, _______, _______, _______, RESET, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CLEAR:
        clear_oneshot_mods();
        clear_oneshot_locked_mods();
        clear_keyboard();
        reset_oneshot_layer();
        layer_clear();
        layer_on(_BASE);
        return false;
    }
 }
  return true;
}
