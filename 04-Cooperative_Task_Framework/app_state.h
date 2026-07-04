#include <stdint.h>
#include "soft_timer.h"

extern uint8_t state_changed_g;
extern stw_timer_t p_diagnostic_timer;

typedef enum
{
    APP_STATE_IDLE = 0,
    APP_STATE_RUNNING,
    APP_STATE_DIAGNOSTIC,
    APP_STATE_COUNT
} app_state_t;

void app_next_state(app_state_t *p_app_state);
 