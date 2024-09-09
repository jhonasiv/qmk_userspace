# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

DEFERRED_EXEC_ENABLE = yes

ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include ${ROOT_DIR}../../../../../rules.mk
ORYX_ENABLE = yes
RGB_MATRIX_CUSTOM_KB = yes

KEY_OVERRIDE_ENABLE = yes
REPEAT_KEY_ENABLE = yes
CONSOLE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

RGB_BLINK_ENABLE = yes
ifeq ($(strip $(RGB_BLINK_ENABLE)), yes)
	OPT_DEFS += -DRGB_BLINKING_ENABLE
	SRC += features/rgb_blink.c
endif

LEADER_COMPOSE_ENABLE = no
ifeq ($(strip $(LEADER_COMPOSE_ENABLE)), yes)
	OPT_DEFS += -DLEADER_COMPOSE_ENABLE
	SRC += features/leader_compose.c
endif
