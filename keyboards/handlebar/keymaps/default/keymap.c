// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = 
    {   {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    }          ,
        {KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    }          ,
        {KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    }         ,
        {KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,    }        ,
        {KC_CAPS, KC_LCTL, KC_LSFT, KC_SPC,  KC_LALT, }       ,

 { KC_0,    KC_9,    KC_8,    KC_7,    KC_6, },
 { KC_SCLN, KC_Y,    KC_U,    KC_L,    KC_J, },
 { KC_O,    KC_I,    KC_E,    KC_N,    KC_M, },
 { KC_COMM, KC_DOT,  KC_H,    KC_K,    KC_SLSH, },
 { KC_BSLS, KC_X,    KC_RSFT, KC_ENT,  KC_X },
}    
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;

  // start with indicator off
  rgblight_sethsv_at(0,0,0, 0);
  rgblight_sethsv_at(0,0,0, 1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_CAPS:
                 static int v = 40;
                 rgblight_sethsv_at(0,128,v, 0);
                 v = v == 0 ? 40 : 0;
                 break;
        }
    }

    return true;
}
