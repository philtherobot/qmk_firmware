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

enum layers{
  BASE,
  EXTEND,
  SYMBOLS1,
  FN,
};


enum unicode_names {
    agrav,    Agrav,
    acirc,    Acirc,
    adiae,    Adiae,

    egrav,    Egrav,
    eacut,    Eacut,
    ecirc,    Ecirc,
    ediae,    Ediae,

    icirc,    Icirc,
    idiae,    Idiae,

    ocirc,    Ocirc,

    ugrav,    Ugrav,
    ucirc,    Ucirc,
    udiae,    Udiae,

    ccedi,    Ccedi,

    LAngQuot,
    RAngQuot
};

const uint32_t unicode_map[] PROGMEM = {
    [agrav]     = 0x00E0, // à
    [Agrav]     = 0x00C0, // À

    [acirc]     = 0x00E2, // â
    [Acirc]     = 0x00C2, // Â

    [adiae]     = 0x00E4, // ä
    [Adiae]     = 0x00C4, // Ä

    [egrav]     = 0x00E8, // è
    [Egrav]     = 0x00C8, // È

    [eacut]     = 0x00E9, // é
    [Eacut]     = 0x00C9, // É

    [ecirc]     = 0x00EA, // ê
    [Ecirc]     = 0x00CA, // Ê

    [ediae]     = 0x00EB, // ë
    [Ediae]     = 0x00CB, // Ë

    [icirc]     = 0x00EE, // î
    [Icirc]     = 0x00CE, // Î

    [idiae]     = 0x00EF, // ï
    [Idiae]     = 0x00CF, // Ï

    [ocirc]     = 0x00F4, // ô
    [Ocirc]     = 0x00D4, // Ô

    [ugrav]     = 0x00F9, // ù
    [Ugrav]     = 0x00D9, // Ù

    [ucirc]     = 0x00FB, // û
    [Ucirc]     = 0x00DB, // Û

    [udiae]     = 0x00FC, // ü
    [Udiae]     = 0x00DC, // Ü

    [ccedi]     = 0x00E7, // ç
    [Ccedi]     = 0x00C7, // Ç

    [LAngQuot]  = 0x00AB, // «
    [RAngQuot]  = 0x00BB, // »
};

enum custom_keycodes {
    CUSTOM_KC_EMAIL = SAFE_RANGE,
    CUSTOM_KC_EXTEND
};

bool locked_into_extend = false;
bool extend_is_pressed = false;

void toggle_extend_layer(void) { 
    locked_into_extend = !locked_into_extend;

    if(locked_into_extend)
        layer_on(EXTEND);
    else
        layer_off(EXTEND);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CUSTOM_KC_EMAIL:
                 SEND_STRING("philtherobot@gmail.com");
                 return false;
            case CUSTOM_KC_EXTEND:
                extend_is_pressed = true;
                bool const isRightShift = get_mods() & MOD_BIT(KC_RIGHT_SHIFT);
                if(isRightShift) {
                    toggle_extend_layer();
                }
                else {
                    layer_on(EXTEND);
                }
                return false;

            case KC_RIGHT_SHIFT:
                if(extend_is_pressed) {
                    toggle_extend_layer();
                    return false;
                }
                return true;
        }
    }
    else {  // key is released

        switch (keycode) {
            case CUSTOM_KC_EXTEND:
                extend_is_pressed = false;
                if(!locked_into_extend) layer_off(EXTEND);
                return false;
        }
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = 
    { VISUAL_TO_MATRIX( 
                                  KC_2,    KC_3,    KC_4,    KC_5,        KC_6,           KC_7,    KC_8,     KC_9,
      KC_1,              KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,        KC_J,           KC_L,    KC_U,     KC_Y,    KC_SCLN, KC_0,
      CUSTOM_KC_EXTEND,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,        KC_M,           KC_N,    KC_E,     KC_I,    KC_O,    KC_BSLS,
                         KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,        KC_SLSH,        KC_K,    KC_H,     KC_COMM, KC_DOT,
                                  KC_LCTL, KC_LSFT, KC_SPC,  KC_LALT,     OSL(SYMBOLS1),  KC_ENT,  KC_RSFT,  MO(FN)
    )
    },


    [EXTEND] = 
    { VISUAL_TO_MATRIX( 
      //-----------//-----------//-----------//-----------//-----------//-----------     //-----------//-----------//-----------//-----------//-----------//-----------
                                _______,     _______,     _______,     _______,          _______,     _______,     _______,     _______,
      _______,     _______,     KC_ESC,      KC_INS,      KC_CAPS,     KC_MS_UP,         KC_PGUP,     KC_HOME,     KC_UP,       KC_END,      KC_DEL,      _______,
      _______,     _______,     KC_LALT,     KC_LSFT,     KC_LCTL,     KC_MS_DOWN,       KC_PGDN,     KC_LEFT,     KC_DOWN,     KC_RIGHT,    KC_BSPC,     _______,
                   _______,     LCTL(KC_X),  LCTL(KC_C),  LCTL(KC_D),  LCTL(KC_V),       KC_MS_BTN1,  KC_MS_BTN3,  KC_MS_BTN2,  KC_MS_LEFT,  KC_MS_RIGHT,
                                _______,     LCTL(KC_Z),  _______,     _______,          KC_TAB,      _______,     _______,     _______
    )
    },


    [SYMBOLS1] = 
    { VISUAL_TO_MATRIX( 
      //-----------//-------------//-------------//-----------------//-----------//-----------     //----------------//-----------------//------------------//-----------------//-----------------//-----------
                                  _______,       _______,           _______,     _______,          _______,           _______,           _______,           KC_MINS,
      KC_GRV,      UM(LAngQuot),  UM(RAngQuot),  S(KC_LBRC),        S(KC_RBRC),  _______,          _______,           UP(agrav, Agrav),  UP(ocirc, Ocirc),  UP(acirc, Acirc),  UP(icirc, Icirc),  KC_QUOT,
      _______,     KC_LBRC,       KC_RBRC,       S(KC_9),           S(KC_0),     _______,          UP(idiae, Idiae),  UP(eacut, Eacut),  UP(egrav, Egrav),  UP(ecirc, Ecirc),  UP(ediae, Ediae),  _______,
                   _______,       _______,       UP(ccedi, Ccedi),  KC_EQL,      S(KC_EQL),        _______,           _______,           UP(ucirc, Ucirc),  UP(ugrav, Ugrav),  UP(udiae, Udiae),
                                  _______,       _______,           _______,     _______,          _______,           _______,           _______,           _______
    )
    },

    [FN] = 
    { VISUAL_TO_MATRIX( 
      //-----------//--------//----------------//-----------//-----------//-----------     //-----------//-----------//-----------//-----------//-----------//-----------
                             KC_F2,            KC_F3,       KC_F4,       KC_F5,            KC_F6,       KC_F7,       KC_F8,       KC_F9,
      KC_F1,       _______,  _______,          KC_VOLD,     KC_MUTE,     KC_VOLU,          KC_F11,      KC_F12,      _______,     KC_PSCR,     KC_PAUSE,    KC_F10,
      _______,     _______,  _______,          KC_MPRV,     KC_MPLY,     KC_MNXT,          _______,     _______,     _______,     _______,     _______,     _______,
                   _______,  CUSTOM_KC_EMAIL,  _______,     _______,     _______,          _______,     _______,     _______,     _______,     _______,
                                               _______,     _______,     KC_LGUI,     _______,          _______,     _______,     KC_RALT,     _______
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

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (record->event.pressed) {
//         switch (keycode) {
//             case KC_CAPS:
//                  static int v = 40;
//                  rgblight_sethsv_at(0,128,v, 0);
//                  v = v == 0 ? 40 : 0;
//                  break;
//         }
//     }

//     return true;
// }
