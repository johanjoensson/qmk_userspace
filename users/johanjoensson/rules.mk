INTROSPECTION_KEYMAP_C = johanjoensson.c
# SRC += johanjoensson.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC += rgb_led.c
endif
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC += rgb_matrix.c
endif
ifeq ($(strip $(OLED_ENABLE)), yes)
  # Include my fancy OLED functions source here
  SRC += oled.c
ifdef RIGHT_ANIMATION
  # Include my fancy animations source here
  SRC += animation.c
endif
endif
ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
  # Include my fancy key_overrides source here
  # SRC += key_overrides.c
endif
ifeq ($(strip $(LEADER_ENABLE)), yes)
  # Include my fancy leader functions source here
  SRC += leader.c
endif
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  # Include my fancy tapdance functions source here
  # Currently, these are imported directly into johanjoensson.c for introspection.
  # SRC += tapdance.c
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
  # Include my fancy rgb functions source here
  # The combos are currently begin directly imported into johanjoensson.c for introspection
  # SRC += combos.c
endif
ifeq ($(strip $(UCIS_ENABLE)), yes)
  # Include my fancy unicode input functions source here
  SRC += ucis.c
endif
ifeq ($(strip $(UNICODE_MAP_ENABLE)), yes)
  # Include my fancy unicode map functions source here
  SRC += unicode_map.c
endif
ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
  # Include my fancy caps_word functions source here
  SRC += caps_word.c
else
	# if not using CAPS_WORD, use casemodes instead
  SRC += features/casemodes.c
endif
