#include "combos.h"

const uint16_t PROGMEM we_combo[]    = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM sd_combo[]    = {HOME_S, KC_D, COMBO_END};
const uint16_t PROGMEM ui_combo[]    = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[]    = {HOME_J, KC_K, COMBO_END};
const uint16_t PROGMEM io_combo[]    = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM kl_combo[]    = {KC_K, HOME_L, COMBO_END};
const uint16_t PROGMEM lscln_combo[] = {HOME_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    [WE_TAB] = COMBO(we_combo, KC_TAB),

#ifdef TAP_DANCE_ENABLE
    [SD_ESC] = COMBO(sd_combo, ESC_CAP),
#else
    [SD_ESC] = COMBO(sd_combo, KC_ESC),
#endif

    [UI_BSP] = COMBO(ui_combo, KC_BSPC),     [IO_ARIN] = COMBO(io_combo, CC_ARIN),     [KL_ADIA] = COMBO(kl_combo, CC_ADIA),     [JK_ODIA] = COMBO(jk_combo, CC_ODIA),

};

uint8_t combo_ref_from_layer(uint8_t layer){
    switch (get_highest_layer(layer_state)){
        case _COLEMAK_DH: return _BASE;
        default: return _BASE;
    }
    return layer;  // important if default is not in case.
}
