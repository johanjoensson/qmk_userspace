#pragma once
#include QMK_KEYBOARD_H

typedef enum {
    /*
     * All different states a tap dance can be in,
     * and UNKNOWN
     */
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    /*
     * Keep track of the tap dance state
     */
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

typedef struct {
    /*
     * User data, store all tap/hold keycodes as well as the dance state
     */
    uint16_t  single_tap;
    uint16_t  single_hold;
    uint16_t  double_tap;
    uint16_t  double_hold;
    uint16_t  triple_tap;
    uint16_t  triple_hold;
    td_tap_t *tap_state;
} quad_tap_data_t;

typedef struct {
    /*
     * User data, store all tap/hold layers as well as the dance state
     */
    uint8_t   single_tap;
    uint8_t   single_hold;
    uint8_t   double_tap;
    uint8_t   double_hold;
    uint8_t   triple_tap;
    uint8_t   triple_hold;
    td_tap_t *tap_state;
} quad_tap_layer_data_t;

enum {
    TD_LEFT_HOME = 0,
    TD_DOWN_PGDN,
    TD_UP_PGUP,
    TD_RGHT_END,
    TD_ESC_CAPS,
    TD_BSLS_GRV,
    TD_PIPE_TILD,
    TD_SYM,
    TD_NUM,
    TD_MOUSE,
    TD_CAPWORD,
};

#define ESC_CAP TD(TD_ESC_CAPS)
#define TD_LEFT TD(TD_LEFT_HOME)
#define TD_DOWN TD(TD_DOWN_PGDN)
#define TD_UP TD(TD_UP_PGUP)
#define TD_RGHT TD(TD_RGHT_END)
#define TD_BSLS TD(TD_BSLS_GRV)
#define TD_PIPE TD(TD_PIPE_TILD)
/*
 * Triple tap hold tap dances for triggering various keycodes.
 * Keycode 0 corresponds to an undefined key.
 * Single tap:  Trigger single_tap on tap
 * Single hold: Trigger single_hold on hold
 * Double tap:  Trigger double_tap on double tap,
 *              if undefined trigger single_tap twice
 * Double hold: Trigger double_hold after tap and hold,
 *              if not defined trigger single_tap followed by single_hold
 * Triple tap:  Trigger triple_tap on triple tap,
 *              if not defined and double_tap defined trigger single_tap
 *              followed by double_tap. If double_tap is not defined trigger
 *              single_tap three times
 * Triple hold: Trigger triple_hold on tap, tap hold,
 *              if not defined and double_hold is defined trigger single_tap
 *              followed by double_hold. If double_hold is not defined but
 *              double_tap is, trigger double_tap followed by single_hold.
 *              If double_tap is not defined, trigger single_tap twice followed
 *              by single_hold.
 */
#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                                                                        \
    {                                                                                                                               \
        .fn        = {NULL, quad_dance_finished, quad_dance_reset, NULL},                                                           \
        .user_data = (void *)&((quad_tap_data_t){tap, hold, 0, 0, 0, 0, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

#define ACTION_TAP_DANCE_DOUBLE_TAP_HOLD(single_tap, single_hold, double_tap, double_hold)                                                                           \
    {                                                                                                                                                                \
        .fn        = {NULL, quad_dance_finished, quad_dance_reset, NULL},                                                                                            \
        .user_data = (void *)&((quad_tap_data_t){single_tap, single_hold, double_tap, double_hold, 0, 0, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

#define ACTION_TAP_DANCE_TRIPLE_TAP_HOLD(single_tap, single_hold, double_tap, double_hold, triple_tap, triple_hold)                                                                     \
    {                                                                                                                                                                                   \
        .fn        = {NULL, quad_dance_finished, quad_dance_reset, NULL},                                                                                                               \
        .user_data = (void *)&((quad_tap_data_t){single_tap, single_hold, double_tap, double_hold, triple_tap, triple_hold, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

/*
 * Triple tap hold tap dances for triggering layer shifts.
 * Layer 255 corresponds to an undefined layer.
 * Single tap:  Oneshot layer shift to single_tap
 * Single hold: Activate single_hold while held
 * Double tap:  Toggle double_tap
 * Double hold: Activate double_hold while held,
 *              if not defined trigger single tap followed by single hold`
 * Triple tap:  Toggle triple_tap,
 *              if not defined and double tap defined trigger single tap
 *              followed by double tap. If double tap is not defined trigger
 *              single tap.
 * Triple hold: Activate triple_hold while held,
 *              if not defined and double hold is defined trigger single tap
 *              followed by double hold. If double hold is not defined but
 *              double tap is trigger double tap followed by single hold.
 *              If double tap is not defined, trigger single hold.
 */
#define ACTION_TAP_DANCE_TAP_HOLD_LAYER(single_tap, single_hold)                                                                                                \
    {                                                                                                                                                           \
        .fn        = {NULL, quad_dance_layer_finished, quad_dance_layer_reset, NULL},                                                                           \
        .user_data = (void *)&((quad_tap_layer_data_t){single_tap, single_hold, 255, 255, 255, 255, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

#define ACTION_TAP_DANCE_DOUBLE_TAP_HOLD_LAYER(single_tap, single_hold, double_tap, double_hold)                                                                               \
    {                                                                                                                                                                          \
        .fn        = {NULL, quad_dance_layer_finished, quad_dance_layer_reset, NULL},                                                                                          \
        .user_data = (void *)&((quad_tap_layer_data_t){single_tap, single_hold, double_tap, double_hold, 255, 255, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

#define ACTION_TAP_DANCE_TRIPLE_TAP_HOLD_LAYER(single_tap, single_hold, double_tap, double_hold, triple_tap, triple_hold)                                                                     \
    {                                                                                                                                                                                         \
        .fn        = {NULL, quad_dance_layer_finished, quad_dance_layer_reset, NULL},                                                                                                         \
        .user_data = (void *)&((quad_tap_layer_data_t){single_tap, single_hold, double_tap, double_hold, triple_tap, triple_hold, &((td_tap_t){.is_press_action = true, .state = TD_NONE})}), \
    }

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);

td_state_t cur_dance(tap_dance_state_t *state);
void       quad_dance_finished(tap_dance_state_t *state, void *user_data);
void       quad_dance_reset(tap_dance_state_t *state, void *user_data);
void       quad_dance_layer_finished(tap_dance_state_t *state, void *user_data);
void       quad_dance_layer_reset(tap_dance_state_t *state, void *user_data);
void       caps_word_dance_finished(tap_dance_state_t *state, void *user_data);
void       caps_word_dance_reset(tap_dance_state_t *state, void *user_data);
