#include "app_state.h"

uint8_t state_changed_g = 1u;

void app_next_state(app_state_t app_state_g)
{
    switch(app_state_g)
    {
        case APP_STATE_IDLE:
            app_state_g = APP_STATE_RUNNING;
            break;

        case APP_STATE_RUNNING:
            app_state_g = APP_STATE_DIAGNOSTIC;
            break;

        case APP_STATE_DIAGNOSTIC:
        default:
            app_state_g = APP_STATE_IDLE;
            break;
    }
    state_changed_g = 1u;
}
