#include "johanjoensson.h"
#include "tapdance.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed
#ifndef PERMISSIVE_HOLD
            || state->interrupted
#endif
        ){
                return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        }else{
                return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
#ifndef PERMISSIVE_HOLD
        if (state->interrupted){
                return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed){
                return TD_DOUBLE_HOLD;
        } else{
                return TD_DOUBLE_TAP;
        }
#else
        if (state->pressed){
                return TD_DOUBLE_HOLD;
        } else{
                return TD_DOUBLE_TAP;
        }
#endif
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    } else if (state->count == 3) {
        if (!state->pressed
#ifndef PERMISSIVE_HOLD
            || state->interrupted
#endif
        ){
                return TD_TRIPLE_TAP;
        } else {
                return TD_TRIPLE_HOLD;
        }
    } else {
            return TD_UNKNOWN;
    }
}

void quad_dance_finished(tap_dance_state_t *state, void *user_data) {
    quad_tap_data_t *quad_tap = (quad_tap_data_t *)user_data;
    quad_tap->tap_state->state = cur_dance(state);
    /* tap_dance_state.state = cur_dance(state); */

    switch (quad_tap->tap_state->state) {
    /* switch (tap_dance_state.state) { */
        case TD_SINGLE_TAP:
                tap_code16(quad_tap->single_tap);
                break;
        case TD_SINGLE_HOLD:
                register_code16(quad_tap->single_hold);
                break;
        case TD_DOUBLE_TAP:
                if(quad_tap->double_tap != 0){
                        tap_code16(quad_tap->double_tap);
                }else{
                        tap_code16(quad_tap->single_tap);
                        register_code16(quad_tap->single_tap);
                }
                break;
        case TD_DOUBLE_HOLD:
                if(quad_tap->double_hold){
                        register_code16(quad_tap->double_hold);
                }else{
                        tap_code16(quad_tap->single_tap);
                        register_code16(quad_tap->single_hold);
                }
                break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
                tap_code16(quad_tap->single_tap);
                tap_code16(quad_tap->single_tap);
                break;
        case TD_TRIPLE_TAP:
                if (quad_tap->triple_tap){
                        tap_code16(quad_tap->triple_tap);
                }else if (quad_tap->double_tap){
                        tap_code16(quad_tap->double_tap);
                        tap_code16(quad_tap->single_tap);
                }else{
                        tap_code16(quad_tap->single_tap);
                        tap_code16(quad_tap->single_tap);
                        tap_code16(quad_tap->single_tap);
                }
                break;
        case TD_TRIPLE_HOLD:
                if (quad_tap->triple_hold){
                        register_code16(quad_tap->triple_hold);
                }else if (quad_tap->double_hold){
                        tap_code16(quad_tap->single_tap);
                        register_code16(quad_tap->double_hold);
                }else if (quad_tap->double_tap){
                        tap_code16(quad_tap->double_tap);
                        register_code16(quad_tap->single_hold);
                }else{
                        tap_code16(quad_tap->single_tap);
                        tap_code16(quad_tap->single_tap);
                        register_code16(quad_tap->single_hold);
                }
                break;
        default:
                break;
    }
}

void quad_dance_reset(tap_dance_state_t *state, void *user_data) {
    quad_tap_data_t *quad_tap = (quad_tap_data_t*)user_data;
    switch (quad_tap->tap_state->state) {
            case TD_SINGLE_TAP:
                    break;
            case TD_SINGLE_HOLD:
                    unregister_code16(quad_tap->single_hold);
                    break;
            case TD_DOUBLE_TAP:
                    break;
            case TD_DOUBLE_HOLD:
                    if(quad_tap->double_hold){
                            unregister_code16(quad_tap->double_hold);
                    }else{
                            unregister_code16(quad_tap->single_hold);
                    }
                    break;
            case TD_DOUBLE_SINGLE_TAP:
                    break;
            case TD_TRIPLE_TAP:
                    break;
            case TD_TRIPLE_HOLD:
                    if(quad_tap->triple_hold){
                            unregister_code16(quad_tap->triple_hold);
                    }else if(quad_tap->double_hold){
                            unregister_code16(quad_tap->double_hold);
                    }else{
                            unregister_code16(quad_tap->single_hold);
                    }
                    break;
            default:
                    break;
    }
    quad_tap->tap_state->state = TD_NONE;
}

void quad_dance_layer_finished(tap_dance_state_t *state, void *user_data) {
    quad_tap_layer_data_t *quad_tap = (quad_tap_layer_data_t*)user_data;
    quad_tap->tap_state->state = cur_dance(state);
    switch (quad_tap->tap_state->state) {
        case TD_SINGLE_TAP:
                set_oneshot_layer(quad_tap->single_tap, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
                break;
        case TD_SINGLE_HOLD:
                layer_on(quad_tap->single_hold);
                break;
        case TD_DOUBLE_TAP:
                if(quad_tap->double_tap < 255){
                        layer_on(quad_tap->double_tap);
                }
                break;
        case TD_DOUBLE_HOLD:
                if(quad_tap->double_hold < 255){
                        layer_on(quad_tap->double_hold);
                }else{
                        set_oneshot_layer(quad_tap->single_tap, ONESHOT_START);
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                        layer_on(quad_tap->single_hold);
                }
                break;
        case TD_DOUBLE_SINGLE_TAP:
                break;
        case TD_TRIPLE_TAP:
                if (quad_tap->triple_tap < 255){
                        layer_on(quad_tap->triple_tap);
                }else{
                        set_oneshot_layer(quad_tap->single_tap, ONESHOT_START);
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                }
                break;
        case TD_TRIPLE_HOLD:
                if (quad_tap->triple_hold < 255){
                        layer_on(quad_tap->triple_hold);
                }else if (quad_tap->double_hold < 255){
                        set_oneshot_layer(quad_tap->single_tap, ONESHOT_START);
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                        layer_on(quad_tap->double_hold);
                }else if (quad_tap->double_tap < 255){
                        layer_on(quad_tap->double_tap);
                        layer_on(quad_tap->single_hold);
                }else{
                        set_oneshot_layer(quad_tap->single_tap, ONESHOT_START);
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                }
                break;
        default:
                break;
    }
}

void quad_dance_layer_reset(tap_dance_state_t *state, void *user_data) {
    quad_tap_layer_data_t *quad_tap = (quad_tap_layer_data_t*)user_data;
    switch (quad_tap->tap_state->state) {
            case TD_SINGLE_TAP:
                    break;
            case TD_SINGLE_HOLD:
                    layer_off(quad_tap->single_hold);
                    break;
            case TD_DOUBLE_TAP:
                    break;
            case TD_DOUBLE_HOLD:
                    if (quad_tap->double_hold < 255){
                            layer_off(quad_tap->double_hold);
                    }else{
                            layer_off(quad_tap->single_hold);
                    }
                    break;
            case TD_DOUBLE_SINGLE_TAP:
                    break;
            case TD_TRIPLE_TAP:
                    break;
            case TD_TRIPLE_HOLD:
                    if (quad_tap->triple_hold < 255){
                            layer_off(quad_tap->triple_hold);
                    } else if (quad_tap->double_hold < 255){
                            layer_off(quad_tap->double_hold);
                    } else if (quad_tap->double_tap < 255){
                            layer_off(quad_tap->single_hold);
                    }else{
                            layer_off(quad_tap->single_hold);
                    }
                    break;
            default:
                    break;
    }
    quad_tap->tap_state->state = TD_NONE;
}

#include "features/casemodes.h"
void caps_word_dance_finished(tap_dance_state_t *state, void *user_data)
{
     td_state_t dance_state = cur_dance(state);
     switch(dance_state){
             case TD_SINGLE_TAP:
                     enable_caps_word();
                     enable_xcase_with(KC_UNDS);
                     break;
             case TD_SINGLE_HOLD:
                     break;
             case TD_DOUBLE_TAP:
                     enable_xcase_with(KC_UNDS);
                     break;
             case TD_DOUBLE_HOLD:
             case TD_DOUBLE_SINGLE_TAP:
             case TD_TRIPLE_TAP:
             case TD_TRIPLE_HOLD:
             default:
                     break;
     }
}

void caps_word_dance_reset(tap_dance_state_t *state, void *user_data)
{}


tap_dance_action_t tap_dance_actions[] = {
    [TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
    [TD_DOWN_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
    [TD_UP_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
    [TD_RGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END),
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_BSLS_GRV] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSLS, KC_GRV),
    [TD_PIPE_TILD] = ACTION_TAP_DANCE_TAP_HOLD(KC_PIPE, KC_TILD),
    [TD_SYM] = ACTION_TAP_DANCE_TRIPLE_TAP_HOLD_LAYER(_SYMBOLS, _SYMBOLS, _SYMBOLS, _NAV, _MOUSE, 255),
    [TD_NUM] = ACTION_TAP_DANCE_TRIPLE_TAP_HOLD_LAYER(_NUMPAD, _NUMPAD, _NUMPAD, _NAV, _MOUSE, 255),
    [TD_CAPWORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caps_word_dance_finished, caps_word_dance_reset),
};
