#include QMK_KEYBOARD_H
#include "johanjoensson.h"

#define ANIM_FRAME_TIME 100

void render_space(void) {
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR("                     "), false);
#endif
#ifdef OLED_DISPLAY_128X32
    oled_write_P(PSTR("     "), false);
#endif
}


void render_animation(void)
{
#include "animation.c"
        static uint8_t current_frame = 0;
        static uint8_t animation_index = 0;
        if (current_frame == 0){
            animation_index = rand() % 2;
        }
        static uint32_t frames_len = sizeof(FRAME_INDICES[animation_index])/sizeof(FRAME_INDICES[animation_index][0]);
        static uint32_t anim_timer = 0;

        if (timer_elapsed32(anim_timer) / 2 > ANIM_FRAME_TIME) {
                if (animation_index == 0){
                    oled_set_cursor(0, 12);
                } else {
                    oled_set_cursor(0, 0);
                }
                anim_timer = timer_read32();
                const char *frame = FRAMES[FRAME_INDICES[animation_index][current_frame]];
                current_frame = (current_frame + 1) % frames_len;
                oled_write_raw_P(frame, sizeof(FRAMES[0]));
        }
    oled_set_cursor(0, 16);
}

void render_large_logo(void)
{
#include "logo.c"
    oled_write_raw_P(logo, sizeof(logo));
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(11, 0);
#endif

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(11, 1);
#endif

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(11, 2);
#endif

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(11, 3);
#endif

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void)
{
#include "logo_small.c"
    oled_set_cursor(0, 6);
    oled_write_raw_P(logo_small, sizeof(logo_small));
    oled_set_cursor(0, 10);
}

void render_small_animation(void)
{
#include "kirby_small.c"
    static const uint32_t frames_len = sizeof(FRAME_INDICES)/sizeof(FRAME_INDICES[0]);
    static uint32_t anim_timer = 0;
    static uint8_t current_frame = 0;

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_TIME) {
            oled_set_cursor(0, 0);
            anim_timer = timer_read32();
            const char *frame = FRAMES[FRAME_INDICES[current_frame]];
            current_frame = (current_frame + 1) % frames_len;
            oled_write_raw_P(frame, sizeof(FRAMES[0]));
    }
    oled_set_cursor(0, 4);
}

void render_logo_text(void) {
#include "logo_string.c"
    oled_write_P(PSTR(logo_string), false);
}

void render_kb_LED_state(void) {
#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(0, 5);
#endif
    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
#ifdef OLED_DISPLAY_128X64
    oled_write_P(led_usb_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCROLL") : PSTR("      "), false);
#endif
#ifdef OLED_DISPLAY_128X32
    oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
#endif
}

void render_layer_state(void) {
#ifdef OLED_DISPLAY_128X64
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("Layer:"), false);
#endif
    if(layer_state_is(_BASE)) {
        oled_write_P(PSTR(" BASE"), false);
    } else if(layer_state_is(_COLEMAK_DH)) {
        oled_write_P(PSTR("CM-DH"), false);
    } else if(layer_state_is(_UCIS)) {
        oled_write_P(PSTR(" UCIS"), false);
    } else if(layer_state_is(_SYMBOLS)) {
        oled_write_P(PSTR(" SYM "), false);
    } else if(layer_state_is(_NUMPAD)) {
        oled_write_P(PSTR(" NUM "), false);
    } else if(layer_state_is(_NAV)) {
        oled_write_P(PSTR(" NAV "), false);
    } else if(layer_state_is(_FUNCTION)) {
        oled_write_P(PSTR(" FUN "), false);
    } else if(layer_state_is(_MOUSE)) {
        oled_write_P(PSTR("MOUSE"), false);
    } else {
        oled_write_P(PSTR("OTHER"), false);
    }
}


bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
#ifdef OLED_DISPLAY_128X64
        render_logo();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
        render_layer_state();
        render_kb_LED_state();
#endif
#ifdef OLED_DISPLAY_128X32
        render_small_animation();
        render_logo_text();
        render_space();
        render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
        render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
        render_space();
        render_layer_state();
        render_space();
        render_kb_LED_state();
#endif
    } else {
#ifdef RIGHT_ANIMATION
         render_logo();
         render_animation();
#else
         render_large_logo();
#endif
    }
    return false;
}
