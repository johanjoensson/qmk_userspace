#include QMK_KEYBOARD_H
#include "johanjoensson.h"

void enable_xcase_with(uint16_t delimiter);

void leader_start_user(void) {
}

void leader_end_user(void) {
#ifdef UCIS_ENABLE
    if (leader_sequence_one_key(KC_U)) {
        layer_on(_UCIS);
        ucis_start();
    }
#endif
    // Leader, S, C for snake_case
    if (leader_sequence_two_keys(KC_S, KC_C)) {
        enable_xcase_with(KC_UNDS);
    }
    // Leader, K, C for kebab-case
    else if (leader_sequence_two_keys(KC_K, KC_C)) {
        enable_xcase_with(KC_MINS);
    }
    // Leader, C, C for camelCase
    else if (leader_sequence_two_keys(KC_X, KC_C)) {
        enable_xcase_with(KC_LSFT);
    }
}
