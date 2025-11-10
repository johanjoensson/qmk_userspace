#pragma once
#include QMK_KEYBOARD_H

enum keycodes {
    CC_ARIN = SAFE_RANGE, // Å
    CC_ADIA,              // Ä
    CC_ODIA,              // Ö
    CC_ALPH,              // α
    CC_BETA,
    CC_DELT,
    CC_GAMM,
    CC_SIGM,
    CC_RHO,
    CC_PI,
    CC_SNEK,
    CC_CLSH,
    CC_SHLD,
    CAPWORD,
    SNEKCAS,
};

enum layer_names { _BASE = 0, _COLEMAK_DH, _UCIS, _SYMBOLS, _NUMPAD, _NAV, _FUNCTION, _MOUSE, _UNUSED_3, _UNUSED_4, _UNUSED_5, _UNUSED_6, _UNUSED_7, _UNUSED_8, _UNUSED_9, _UNUSED_10, _UNUSED_11 };

#define SYM MO(_SYMBOLS)
#define NUM MO(_NUMPAD)
#define NAV MO(_NAV)

/*
 * Home-row mods
 */
#define HOME_A LGUI_T(KC_A)       /*QWERTY and COLEMAK-DH*/
#define HOME_S LALT_T(KC_S)       /*QWERTY*/
#define HOME_R LALT_T(KC_R)       /*COLEMAK-DH*/
#define HOME_F LCTL_T(KC_F)       /*QWERTY*/
#define HOME_T LCTL_T(KC_T)       /*COLEMAK-DH*/
#define HOME_J LCTL_T(KC_J)       /*QWERTY*/
#define HOME_N LCTL_T(KC_N)       /*COLEMAK-DH*/
#define HOME_L LALT_T(KC_L)       /*QWERTY*/
#define HOME_I LALT_T(KC_I)       /*COLEMAK-DH*/
#define HOME_SCLN LGUI_T(KC_SCLN) /*QWERY*/
#define HOME_O LGUI_T(KC_O)       /*COLEMAK-DH*/
#define LSFT_ENT RSFT_T(KC_ENT)
#define LSFT_SPC LSFT_T(KC_SPC)

/*
 * Mod-taps
 */
#define CONTROL_SPC LT(_NAV, KC_SPC)

#ifndef TAP_DANCE_ENABLE
#    define ESC_CAP KC_ESC
#    define TD_LEFT KC_LEFT
#    define TD_DOWN KC_DOWN
#    define TD_UP KC_UP
#    define TD_RGHT KC_RGHT
#    define TD_BSLS KC_BSLS
#    define TD_PIPE KC_PIPE
#else
#    include "tapdance.h"
#endif
