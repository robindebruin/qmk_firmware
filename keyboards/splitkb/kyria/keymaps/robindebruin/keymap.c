/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
// #include "print.h"

#include QMK_KEYBOARD_H

typedef union {
    uint32_t raw;
    struct {
        bool osIsWindows;
    };
} user_config_t;

user_config_t user_config;

enum layers {
    _QWERTY = 0,
    _SYM,
    _NAV,
    _MOUSE,
    _FUNCTION,
};

enum custom_keycodes {
    // Undo, Cut, Copy, Paste, NxtWord, PrvWord
    SELWORD
};

// Aliases for readability
#define QWERTY DF(_QWERTY)  ''

#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define MOUSE MO(_MOUSE)
// #define KC_CPYW LGUI(LSFT(LCTL(KC_3)))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  i  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |shft/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |MOUSE |  |CapsLk|  ] } |   N  |   M  | ,  < | . >  | /  ? | esc/RAltShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LCtrl/| alt  | cmd  |QKLEAD| Nmbrs|  | Nav  |Option| Space| CMD  |  ~grave   |
 *                        |   ⌥  |      |      |      | layer|  | Layer|      |   ⌥  |      |  `   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB ,         KC_Q,  KC_W ,  LT(MOUSE,KC_E)  ,       KC_R ,        KC_T ,                                         KC_Y,        KC_U ,           KC_I ,            KC_O ,     KC_P ,        KC_BSPC,
     KC_LSFT, LCTL_T(KC_A),  LALT_T(KC_S)   ,  CMD_T(KC_D)  ,    LT(NAV,KC_F),    KC_G ,                             KC_H, KC_J,   RCMD_T(KC_K) ,    RALT_T(KC_L) ,   RCTL_T(KC_SCLN),      RSFT_T(KC_QUOTE),
     QK_GRAVE_ESCAPE,   KC_Z,  KC_X   ,  KC_C  ,           KC_V ,            KC_B , KC_LBRC, OSL(FKEYS),     KC_CAPS, TG(MOUSE),      KC_N,        KC_M ,         KC_COMM,          KC_DOT ,   KC_SLSH, KC_ESC,
                      KC_LCTL,  KC_LALT ,  KC_LGUI	, KC_ENTER,    _______,     _______ , LT(FKEYS, KC_SPC) ,  KC_LEAD, MO(SYM) , _______  
    ),

/* 
 * Symbols
 *
 * !@#$%  ^&*+
 * =<({[  ]})_-
 * zxc§b n±|/\ )|||±±±±±±±±±±±§§§±>vv>cc```````````~```````````~```cc````
 * 
 */
    [_SYM] = LAYOUT(
     _______ , KC_EXLM,   KC_AT, KC_HASH,  KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, _______,
     _______ , KC_EQL , KC_LABK, KC_LPRN,  KC_LCBR, KC_LBRC,                                     KC_RBRC, KC_RCBR, KC_RPRN, KC_RABK, KC_UNDS, _______,
     _______ , _______, _______,  KC_TILDE, KC_GRV , _______, _______, _______, _______, _______, _______, KC_TILD, KC_PIPE, KC_SLSH, KC_BSLS, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   shift|  ctrl| Alt  | cmnd |      |      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, _______,
      _______, _______, _______, _______, _______, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
     * MOUSE
     */ 
    // deze laag onhoog zodat die de media knoppen erft?
    // en dan mouse layer van G naar T of B, en dan acl012 ook naar de linkerhand
    [_MOUSE] = LAYOUT(
        _______, KC_ACL0, KC_BTN2, _______, KC_BTN1, _______,                                     _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

/*
 * Function Layer: Function keys
 */
    [_FUNCTION] = LAYOUT(
      _______ ,   KC_1 ,    KC_2 ,   KC_3 ,     KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , _______ ,
      _______,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5 ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10, _______,
      _______,  _______,  _______,  _______,  KC_F11 ,_______, _______, _______, _______, _______, _______, KC_F12, _______, _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),  


// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {       
        case SELWORD:  // Selects the current word under the cursor.
        if (record->event.pressed) {
            // SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            // Mac users, change LCTL to LALT:
            SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
        }
        return false; 
    }
    return true;
};


// leader keys 
// start with leader key followed by any sequence defined below
// ss = send string feature_send_string
// X prefix is nodig ipv KC
LEADER_EXTERNS();

layer_state_t current_layer_state;
void leader_start(void) {  
      current_layer_state = get_highest_layer(layer_state | default_layer_state);
      layer_clear();
}

void leader_end(void) {
  // Add your code to run when a leader key sequence ends here
  // layer_on(current_layer_state);
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;

    // __TERMINAL__ //
    // YY: cmd curly bracket left 
    // SEQ_TWO_KEYS(KC_Y, KC_Y) {    
    //   // register_code(KC_LGUI);
    //   // register_code(KC_LBRC);
    //   // unregister_code(KC_LBRC);
    //   // unregister_code(KC_LGUI);      
    // }
    // // PP: cmd curly bracket right 
    // SEQ_TWO_KEYS(KC_P, KC_P) {    
    //   // SEND_STRING(SS_LGUI(SS_TAP(X_RCBR))) 
    //      SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_RCBR)))); 
    // }

    // MAC
    // Y: ctrl left arrow  
    // PREV FULL SCREEN
    SEQ_ONE_KEY(KC_Y) {        
      SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
    } 
    // P: ctrl right arrow  
    // NEXT FULL SCREEN
    SEQ_ONE_KEY(KC_P) {    
    // ctrl right arrow
      SEND_STRING(SS_LCTL(SS_TAP(X_RGHT)));
    } 

    // __CHROME__ //
    // U: option cmd left arrow 
    // left tab 
    SEQ_ONE_KEY(KC_U) {    
    // option cmd left arrow
      SEND_STRING(SS_LALT(SS_LGUI(SS_TAP(X_LEFT))));
    } 
    // O: option cmd right arrow 
    // right tab
    SEQ_ONE_KEY(KC_O) {    
      SEND_STRING(SS_LALT(SS_LGUI(SS_TAP(X_RGHT))));
    }
    // UU: cmd left arrow  
    // back history
    SEQ_TWO_KEYS(KC_U, KC_U) {          
      SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
    }
    // OO: cmd right arrow
    // fwd history
    SEQ_TWO_KEYS(KC_O, KC_O) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
    }
    
    // W: word select
    SEQ_ONE_KEY(KC_W) {        
      SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) );
    }
    // WC: word copy
      SEQ_TWO_KEYS(KC_W, KC_C) {    
      SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("c"));
    }
    // WP: word paste
    SEQ_TWO_KEYS(KC_W, KC_P) {        
      SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("v"));
    } 

    // WC: word bold
      SEQ_TWO_KEYS(KC_W, KC_B) {    
      SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("b"));
    }
      // WD: word paste
    SEQ_TWO_KEYS(KC_W, KC_D) {        
      SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
      register_code(KC_BSPC);
      unregister_code(KC_BSPC); 
    }
 
    // LS: select line
    SEQ_TWO_KEYS(KC_L, KC_S) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
    } 
    // LC: select line and copy
    SEQ_TWO_KEYS(KC_L, KC_C) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("c"));
    }  
    // LX: select line and cut
    SEQ_TWO_KEYS(KC_L, KC_X) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("x"));
    }   
     // LB: select line and bold
    SEQ_TWO_KEYS(KC_L, KC_B) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_LGUI("b"));
    }     
    // LD: select line and delete
    SEQ_TWO_KEYS(KC_L, KC_D) {    
      SEND_STRING(SS_LGUI(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT)))); 
      register_code(KC_BSPC);
      unregister_code(KC_BSPC); 
      // cmd left bspc 
      SEND_STRING(SS_LGUI(SS_TAP(X_LEFT ))); 
      register_code(KC_BSPC);
      unregister_code(KC_BSPC); 
    }


    // PS: PRINT SCREEN
    SEQ_TWO_KEYS(KC_P, KC_S) {
      // print portion of the screen      
      SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_4)))  );
      layer_on(_MOUSE);
    }

    // __LAYER SWITCHING__ //
    //
    // J: MOUSE LAYER
    SEQ_ONE_KEY(KC_J) {
      layer_on(_MOUSE); 
    }  
    // K: NUMBERS LAYER
    SEQ_ONE_KEY(KC_K) {
      layer_on(_FUNCTION); 
    }   
    // L: SYMBOLS LAYER 
    SEQ_ONE_KEY(KC_L) {
      layer_on(_SYM); 
    }    
    // ';' NAVIGATION LAYER 
    SEQ_ONE_KEY(KC_SCLN) {
      layer_on(_NAV); 
    } 

    // __STRING SEQUENCES__ //
    SEQ_TWO_KEYS(KC_C, KC_L) {
      SEND_STRING("console.log('',)");
      SEND_STRING(SS_TAP(X_LEFT));
      SEND_STRING(SS_TAP(X_LEFT));
      SEND_STRING(SS_TAP(X_LEFT));
    }
   
    // SEQ_TWO_KEYS(KC_A, KC_S) {
    //   register_code(KC_LGUI);
    //   register_code(KC_S);
    //   unregister_code(KC_S);
    //   unregister_code(KC_LGUI);
    // } 

    leader_end(); 
  }
}



/* The default OLED and rfotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    // if (is_keyboard_master()) {
        // Host Keyboard Layer Status

        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym \n\n"), false);
                oled_write_P(PSTR("! @ # $ %  ^ & * - +\n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("= > ( { [ ] } ) _ "), false);
                oled_write_P(PSTR("\n\n"), false);
                oled_write_P(PSTR("    ~ `     | / \\"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Nummers + FN\n\n"), false);
                oled_write_P(PSTR("1 2 3 4 5\n"), false);
                oled_write_P(PSTR("       f5\n"), false);
                oled_write_P(PSTR("     f11\n"), false);
                oled_write_P(PSTR("\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("MOUSE\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("Arrows n Media\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    // } else {
    //    
    // }
    return false;
}
#endif     

// switch (get_highest_layer(layer_state | default_layer_state)) {
//   case _MOUSE:
//     layer_off(_MOUSE);
//     break;
//   default: 
//   break;
// } 
// case Undo:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_Z));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(G(KC_Z));
//         }
//     }
//     break;
// case Cut:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_X));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(G(KC_X));
//         }
//     }
//     break;
// case Copy:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_C));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(G(KC_C));
//         }
//     }
//     break;
// case Paste:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_V));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(G(KC_V));
//         }
//     }
//     break;
// case PrvWord:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_LEFT));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(A(KC_LEFT));
//         }
//     }
//     break;
// case NxtWord:
//     if (record->event.pressed) {
//         if (user_config.osIsWindows == 1) {
//             tap_code16(C(KC_RGHT));
//         } else if (user_config.osIsWindows == 0) {
//             tap_code16(A(KC_RGHT));
//         }
//     }
//     break;