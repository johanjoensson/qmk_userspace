# Copyright 2022 splitkb.com <support@splitkb.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CONVERT_TO = liatris
LTO_ENABLE = yes

# NOTE: These are already enabled by default at the revision level
ENCODER_ENABLE = no
OLED_ENABLE = yes

# RGB Matrix is enabled at the revision level,
# while we use the regular RGB underglow for testing
LED_MATRIX_ENABLE = no
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no
BACKLIGHT_ENABLE = no
WS2812_DRIVER = vendor

KEY_OVERRIDE_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
COMBO_ENABLE = yes

UNICODE_COMMON = yes
UCIS_ENABLE = no

CAPS_WORD_ENABLE = yes

CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
AUDIO_ENABLE = no
MUSIC_ENABLE = no
AVR_USE_MINIMAL_PRINTF = yes
