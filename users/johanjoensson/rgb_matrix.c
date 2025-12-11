#include "johanjoensson.h"


uint8_t bg_h = 255, bg_s = 255, bg_v = 255, kl_h = 255, kl_s = 255, kl_v = 255;
uint8_t hue_step = 17, val_step = 8, sat_step = 17;


void keyboard_post_init_user(void) {
    // Initialize RGB to static black
    /* rgblight_enable_noeeprom(); */
    /* rgblight_sethsv_noeeprom(HSV_BLACK); */
    /* rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); */
    /* rgblight_layers = rgb_layers; */

}

bool led_update_user(led_t led_state) {
    /* rgblight_set_layer_state(31, led_state.caps_lock); */
    return true;
}
