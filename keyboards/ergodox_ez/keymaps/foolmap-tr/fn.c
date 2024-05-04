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
