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

enum custom_keycodes { Undo, Cut, Copy, Paste, NxtWord, PrvWord };

// Aliases for readability
#define QWERTY DF(_QWERTY)  ''

#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)
#define MOUSE MO(_MOUSE)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// LT(MOUSE, KC_SPC)

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
 *                        |LCtrl/| alt  | cmd  | enter| Nmbrs|  | Nav  |Option| Space| CMD  |  ~   |
 *                        |   ⌥  |      |      |      | layer|  | Layer|      |   ⌥  |      |  `   |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  ,      KC_Q ,  KC_W ,  LT(MOUSE,KC_E)  ,       KC_R ,        KC_T ,                                                      KC_Y,        KC_U ,           KC_I ,            KC_O ,     KC_P ,        KC_BSPC,
    KC_LSFT , LCTL_T(KC_A) ,  LALT_T(KC_S)   ,  CMD_T(KC_D)  ,    LT(NAV,KC_F),    KC_G ,                             KC_H, KC_J,   RCMD_T(KC_K) ,    ALT_T(KC_L) ,   RCTL_T(KC_SCLN),   RSFT_T(KC_QUOTE),
     SFT_T(KC_ESC), KC_Z ,  KC_X   ,  KC_C  ,           KC_V ,              KC_B , KC_LBRC, OSL(FKEYS),               KC_CAPS, KC_RBRC, KC_N,        KC_M ,         KC_COMM,          KC_DOT ,   KC_SLSH, RSFT_T(KC_ESC),
                         LCTL_T(KC_ENTER),  LT(NAV, KC_ENTER) ,  LT(MOUSE, KC_ENTER)	, KC_ENTER,    MO(SYM),            LT(NAV,KC_ENTER)  , LT(MOUSE, KC_SPC) , LT(FKEYS,KC_SPC) ,   MO(SYM) , KC_GRV  
    ),

/* 
 * Symbols
 *
 * !@#$%  ^&*+
 * =>({[  ]})_-
 * ±-
 * 
 */
    [_SYM] = LAYOUT(
     _______ , KC_EXLM,   KC_AT, KC_HASH,  KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_MINS, _______,
     _______ , KC_EQL , KC_LABK, KC_LPRN,  KC_LCBR, KC_LBRC,                                     KC_RBRC, KC_RCBR, KC_RPRN, KC_RABK, KC_UNDS, _______,
     _______ , _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_TILD, KC_PIPE, KC_SLSH, KC_BSLS, _______,
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
        _______, KC_ACL0, KC_BTN2, _______, KC_BTN1, _______,                                     KC_WH_D, KC_BTN1, _______, KC_BTN2, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        ),

/*
 * Function Layer: Function keys
 */
    [_FUNCTION] = LAYOUT(
      _______ ,   KC_1 ,    KC_2 ,   KC_3 ,     KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , _______ ,
      _______,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5 ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10, _______,
      _______,  _______,  _______,  _______,  _______,  KC_F11, _______, _______, _______, _______, KC_F12, _______, _______, _______, _______, _______,
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
    }
    return true;
};


/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
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
                oled_write_P(PSTR("! @ # $ %  ^ & * + - \n"), false);
                oled_write_P(PSTR("\n"), false);
                oled_write_P(PSTR("= > ( { [ ] } ) _ "), false);
                oled_write_P(PSTR("\n\n"), false);
                oled_write_P(PSTR("             | / \\"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Nummers + FN\n\n"), false);
                oled_write_P(PSTR("1 2 3 4 5\n"), false);
                oled_write_P(PSTR("       f5\n"), false);
                oled_write_P(PSTR("      f11\n"), false);
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

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif