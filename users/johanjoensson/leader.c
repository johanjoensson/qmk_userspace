#include QMK_KEYBOARD_H
#include "johanjoensson.h"
void leader_start_user(void) {
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_U)) {
        layer_on(_UCIS);
        ucis_start();
    }
}

