/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#include "johanjoensson.h"

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// Automatically enable sniping-mode on the pointer layer.
/* #define CHARYBDIS_AUTO_SNIPING_ON_LAYER _MOUSE */

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /*
         * Base layer, QWERTY layout with homerow-mods (except shift), mod tap for enter and space / shift, combos for tab and escape.
         * As well as Swedish characters.
         * Access to _NUMPAD and _SYMBOLS layers on the thumbs.
         */
	[_BASE] = LAYOUT(

                        KC_Q   , KC_W   , KC_E   , KC_R   , KC_T,                                               KC_Y   , KC_U   , KC_I   , KC_O   , KC_P,
                        KC_A   , HOME_S , KC_D   , HOME_F , KC_G,                                               KC_H   , HOME_J , KC_K   , HOME_L , KC_SCLN,
                        KC_Z   , KC_X   , KC_C   , HOME_V , KC_B,                                               KC_N   , HOME_M , KC_COMM, KC_DOT , KC_SLSH,
                                                            LSFT_SPC, TD(TD_NUM), ESC_CAP,           TD(TD_SYM), LSFT_ENT
                       ),
	[_COLEMAK_DH] = LAYOUT(

                        KC_Q   , KC_W   , KC_F   , KC_P   , KC_B,                                               KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN,
                        HOME_A , CDH_HOME_R, KC_S, CDH_HOME_T , KC_G,                                           KC_M   , CDH_HOME_N , KC_E   , CDH_HOME_I , CDH_HOME_O,
                        KC_Z   , KC_X   , KC_C   , KC_D   , KC_V,                                               KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH,
                                                            LSFT_SPC, TD(TD_NUM), ESC_CAP,  TD(TD_SYM), LSFT_ENT
                       ),
        /*
         * _UCIS Is used for unicode input, the UCIS system requires basic keycodes A-Z, a-z, 0-9 ONLY, no mod-taps, homerow-mods, etc...
         */
	[_UCIS] = LAYOUT(
                        KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,
                        KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                           KC_H   , KC_J   , KC_K   , KC_L   , UC_NEXT,
                        KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                           KC_N   , KC_M   , KC_COMM, KC_DOT , UC_PREV,
                                                   KC_SPC, MO(_NUMPAD), _______,      XXXXXXX, KC_ENT
                       ),
        /*
         * _SYMBOLS gives access to a number row as well as a bunch of symbols. Leader key on left thumb, as well as access to the _FUNCTION layer.
         */
	[_SYMBOLS] = LAYOUT(
                        KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                             KC_CIRC, KC_AMPR, KC_LCBR, KC_RCBR, KC_ASTR,
                        CC_ALPH, CC_BETA, CC_DELT, CC_PI  , TD_BSLS,                             KC_MINS, KC_EQL , KC_LPRN, KC_RPRN, KC_QUOT,
                        CC_GAMM, CC_SIGM, CC_RHO , CC_SNEK, TD_PIPE,                             KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_TILD,
                                                            CC_SHLD, MO(_NAV), _______,     TG(_SYMBOLS), KC_RSFT
                        ),
        /*
         * _NUMPAD gives acces to a numpad like layout on the right hand, RGB settings on the left and access to the _FUNCTION layer on the right thumb.
         */
	[_NUMPAD] = LAYOUT(
                DF(_COLEMAK_DH), UG_SATU, UG_HUEU, UG_VALU, UG_NEXT,                                 KC_ASTR, KC_7   , KC_8   , KC_9   , KC_MINS,
                        UG_TOGG, UG_SATD, UG_HUED, UG_VALD, UG_PREV,                                 KC_SLSH, KC_4   , KC_5   , KC_6   , KC_PLUS,
                      DF(_BASE), XXXXXXX, DT_UP  , DT_DOWN, DT_PRNT,                                 KC_COMM, KC_1   , KC_2   , KC_3   , KC_DOT,
                                                            _______, TG(_NUMPAD), _______,          MO(_NAV), RSFT_T(KC_0)
                        ),
        /*
         * Access backspace and quotation symbols. As well as arrow navigation (vim layout) and home, page up, page down, and end keys with double taps.
         * Left thumb triggers Caps Word.
         */
	[_NAV] = LAYOUT(
                        KC_KB_VOLUME_UP  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                              TD(TD_CAPWORD), KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX,
                        KC_KB_VOLUME_DOWN, KC_F4  , KC_F5  , KC_F6  , KC_F11 ,                              TD_LEFT, TD_DOWN, TD_UP  , TD_RGHT, XXXXXXX,
                        KC_KB_MUTE       , KC_F1  , KC_F2  , KC_F3  , KC_F12 ,                              KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                                                                      _______, TG(_NAV), _______,          TG(_NAV), _______
                        ),
        [_MOUSE] = LAYOUT(
                        _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______,
                        _______, DRGSCRL, SNIPING, _______, _______,                                           _______, _______, SNIPING, DRGSCRL, _______,
                                                            KC_BTN1, KC_BTN2, KC_BTN3,                KC_BTN3, KC_BTN2
                        ),
};

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(_MOUSE);
# if 0
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
#endif
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(_MOUSE);
#if 0
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
#endif
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
