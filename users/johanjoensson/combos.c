#include "combos.h"

const uint16_t PROGMEM we_combo[]    = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM sd_combo[]    = {HOME_S, KC_D, COMBO_END};
const uint16_t PROGMEM ui_combo[]    = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM jk_combo[]    = {HOME_J, KC_K, COMBO_END};
const uint16_t PROGMEM io_combo[]    = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM kl_combo[]    = {KC_K, HOME_L, COMBO_END};
const uint16_t PROGMEM lscln_combo[] = {HOME_L, KC_SCLN, COMBO_END};

const uint16_t PROGMEM wf_cdf_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM rs_cdf_combo[] = {CDH_HOME_R, KC_S, COMBO_END};
const uint16_t PROGMEM lu_cdf_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM ne_cdf_combo[] = {CDH_HOME_N, KC_E, COMBO_END};
const uint16_t PROGMEM uy_cdf_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ei_cdf_combo[] = {KC_E, CDH_HOME_I, COMBO_END};
const uint16_t PROGMEM io_cdf_combo[] = {CDH_HOME_I, CDH_HOME_O, COMBO_END};

combo_t key_combos[] = {
    [WE_TAB] = COMBO(we_combo, KC_TAB),      [WF_TAB] = COMBO(wf_cdf_combo, KC_TAB),
/* [ER_STAB] = COMBO(er_combo, LSFT(KC_TAB)), */

#ifdef TAP_DANCE_ENABLE
    [SD_ESC] = COMBO(sd_combo, ESC_CAP),     [RS_ESC] = COMBO(rs_cdf_combo, ESC_CAP),
#else
    [SD_ESC] = COMBO(sd_combo, KC_ESC),      [RS_ESC] = COMBO(rs_cdf_combo, KC_ESC),
#endif

    [UI_BSP] = COMBO(ui_combo, KC_BSPC),     [JK_ENT] = COMBO(jk_combo, KC_ENT),      [IO_ARIN] = COMBO(io_combo, CC_ARIN),     [KL_ADIA] = COMBO(kl_combo, CC_ADIA),     [LSCLN_ODIA] = COMBO(lscln_combo, CC_ODIA),

    [LU_BSP] = COMBO(lu_cdf_combo, KC_BSPC), [NE_ENT] = COMBO(ne_cdf_combo, KC_ENT),  [UY_ARIN] = COMBO(uy_cdf_combo, CC_ARIN), [EI_ADIA] = COMBO(ei_cdf_combo, CC_ADIA), [IO_ODIA] = COMBO(io_cdf_combo, CC_ODIA),
};
