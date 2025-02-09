#include "color.h"

typedef void (*rgb_light_management_callback_t)(void);

typedef enum {
    LIGHTING_OFF,
    LIGHTING_ON,
    LIGHTING_TOGGLE_ON,
    LIGHTING_TOGGLE_OFF,
} rgb_lighting_state_t;

typedef struct {
    uint8_t              key_id;
    uint8_t              on_layer;
    RGB                  color;
    rgb_lighting_state_t state;

    rgb_light_management_callback_t on_callback;
    rgb_light_management_callback_t off_callback;
    rgb_light_management_callback_t effect_callback;
} ManagedKeyRGB;

#if defined(MATRIX_ROWS) && defined(MATRIX_COLS)
// Support managing alls keys from the keyboard from all layers that QMK supports
#    define MAX_RGB_LIGHTING_MANAGED_KEYS 32 * MATRIX_ROWS *MATRIX_COLS
#else
#    error "To use RGB light management the MATRIX_ROWS and MATRIX_COLS macros must be defined"
#endif

typedef struct {
    ManagedKeyRGB keys[MAX_RGB_LIGHTING_MANAGED_KEYS];
} RGBLightingManager;
