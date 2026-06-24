#include <stdint.h>

extern uint8_t state_changed_g;

typedef enum
{
    APP_STATE_IDLE = 0,
    APP_STATE_RUNNING,
    APP_STATE_DIAGNOSTIC,
    APP_STATE_COUNT
} app_state_t;

void app_next_state(app_state_t app_state_g);