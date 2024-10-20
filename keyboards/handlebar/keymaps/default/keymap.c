// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define VISUAL_TO_MATRIX( \
                          num_left_1, num_left_2, num_left_3, num_left_4,   num_right_1, num_right_2, num_right_3, num_right_4, \
  top_left_1, top_left_2, top_left_3, top_left_4, top_left_5, top_left_6,   top_right_1, top_right_2, top_right_3, top_right_4, top_right_5, top_right_6, \
  hom_left_1, hom_left_2, hom_left_3, hom_left_4, hom_left_5, hom_left_6,   hom_right_1, hom_right_2, hom_right_3, hom_right_4, hom_right_5, hom_right_6, \
              bot_left_1, bot_left_2, bot_left_3, bot_left_4, bot_left_5,   bot_right_1, bot_right_2, bot_right_3, bot_right_4, bot_right_5, \
                          thu_left_1, thu_left_2, thu_left_3, thu_left_4,   thu_right_1, thu_right_2, thu_right_3, thu_right_4 \
   ) \
   { top_left_1, num_left_1, num_left_2, num_left_3, num_left_4 }, \
   { top_left_2, top_left_3, top_left_4, top_left_5, top_left_6 }, \
   { hom_left_2, hom_left_3, hom_left_4, hom_left_5, hom_left_6 }, \
   { bot_left_1, bot_left_2, bot_left_3, bot_left_4, bot_left_5 }, \
   { hom_left_1, thu_left_1, thu_left_2, thu_left_3, thu_left_4 }, \
\
   { top_right_6, num_right_4, num_right_3, num_right_2, num_right_1 }, \
   { top_right_5, top_right_4, top_right_3, top_right_2, top_right_1 }, \
   { hom_right_5, hom_right_4, hom_right_3, hom_right_2, hom_right_1 }, \
   { bot_right_5, bot_right_4, bot_right_3, bot_right_2, bot_right_1 }, \
   { hom_right_6, thu_right_4, thu_right_3, thu_right_2, thu_right_1 }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = 
    { VISUAL_TO_MATRIX( 
                        KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,
      KC_1,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_0,
      KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_BSLS,
               KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,        KC_SLSH, KC_K,    KC_H,    KC_COMM, KC_DOT,
                        KC_LCTL, KC_LSFT, KC_SPC,  KC_LALT,     KC_X,    KC_ENT,  KC_RSFT, KC_X
    )
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
