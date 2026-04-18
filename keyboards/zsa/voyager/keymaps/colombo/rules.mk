# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

DEFERRED_EXEC_ENABLE = yes

ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include ${ROOT_DIR}../../../../../rules.mk
ORYX_ENABLE = yes

LTO_ENABLE = yes
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
SPACE_CADET_ENABLE = no
AUDIO_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

KEY_OVERRIDE_ENABLE = yes
REPEAT_KEY_ENABLE = yes
CONSOLE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
LAYER_LOCK_ENABLE = yes
TAP_DANCE_ENABLE = yes

RGB_EFFECTS_ENABLE = yes
ifeq ($(strip $(RGB_EFFECTS_ENABLE)), yes)
	OPT_DEFS += -DRGB_EFFECTS_ENABLE
	SRC += features/rgb_effects.c
	SRC += features/rgb_effect_fade.c
	SRC += features/rgb_effect_modifier.c
	SRC += features/rgb_effect_layer.c
endif

LEADER_COMPOSE_ENABLE = no
ifeq ($(strip $(LEADER_COMPOSE_ENABLE)), yes)
	OPT_DEFS += -DLEADER_COMPOSE_ENABLE
	SRC += features/leader_compose.c
endif
