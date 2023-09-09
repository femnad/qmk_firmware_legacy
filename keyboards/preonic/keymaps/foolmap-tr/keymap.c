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
#include "muse.h"

enum preonic_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE
};

#define C_CDL_L UC(0x00e7) // ç
#define G_BRV_L UC(0x011f) // ğ
#define I_DLS_L UC(0x0131) // ı
#define O_DIA_L UC(0x00f6) // ö
#define S_CDL_L UC(0x015F) // ş
#define U_DIA_L UC(0x00fc) // ü

#define C_CDL_U UC(0x00c7) // Ç
#define G_BRV_U UC(0x011e) // Ğ
#define I_DAB_U UC(0x0130) // İ
#define O_DIA_U UC(0x00d6) // Ö
#define S_CDL_U UC(0x015E) // Ş
#define U_DIA_U UC(0x00dc) // Ü

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TILD, KC_GRV,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_ESC,  KC_BSPC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_TAB,  KC_ENT,  KC_D,    KC_H,    KC_T,    KC_N,    KC_S,
  KC_SCLN, KC_Q, KC_J, KC_K, KC_X, OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
  OSL(3), OSL(2), OSM(MOD_LALT), OSM(MOD_LCTL), OSL(1), KC_SPC, KC_SPC, OSL(1), OSM(MOD_RCTL), OSM(MOD_RALT), OSL(2), OSL(3)
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_BTN3, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN2, RESET,   RESET, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_EQL,  _______, _______, KC_SLSH, KC_MINS, KC_UNDS, KC_LBRC, KC_RBRC,
  KC_HOME, KC_PGUP, KC_TILD, KC_PIPE, KC_GRV,  _______, _______, KC_BSLS, KC_PLUS, KC_DEL,  KC_INS,  _______,
  _______, _______, _______, _______, OSL(3),  _______, _______, OSL(3), _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TILD, KC_GRV,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_ESC,  KC_BSPC, KC_F,    G_BRV_L, C_CDL_L, KC_R,    KC_L,
  KC_A,    O_DIA_L, KC_E,    U_DIA_L, I_DLS_L, KC_TAB,  KC_ENT,  KC_D,    KC_H,    KC_T,    KC_N, S_CDL_L,
  KC_SCLN, KC_Q, KC_J, KC_K, KC_X, OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
  _______, _______, _______, _______, _______,   _______,   _______,   _______,   _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TILD, KC_GRV,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_ESC,  KC_BSPC, KC_F,    G_BRV_U, C_CDL_U, KC_R,    KC_L,
  KC_A,    O_DIA_U,    KC_E, U_DIA_U, I_DAB_U, KC_TAB,  KC_ENT,  KC_D,    KC_H,    KC_T,    KC_N,    S_CDL_U,
  KC_SCLN, KC_Q, KC_J, KC_K, KC_X, OSM(MOD_LSFT), OSM(MOD_RSFT), KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,
  _______, _______, _______, _______, _______,   _______,   _______,   _______,   _______, _______, _______, _______
 )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
