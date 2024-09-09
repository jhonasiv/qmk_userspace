/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#pragma once

#ifndef ORYX_CONFIGURATOR
#    define ORYX_CONFIGURATOR
#endif

#define USB_SUSPEND_WAKEUP_DELAY 0
#define FIRMWARE_VERSION         u8"aZW3V/mAX9X"
#define RAW_USAGE_PAGE           0xFF60
#define RAW_USAGE_ID             0x61
#define LAYER_STATE_16BIT

#define RGB_MATRIX_STARTUP_SPD 60

#define COMBO_TERM 40
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 150

#define LEADER_TIMEOUT 150
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT
#define LEADER_COMPOSE_CONTINUOUS_TRIGGER
