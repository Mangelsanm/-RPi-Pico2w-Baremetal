#include "app_state.h"
#include  "raspBerryPico.h"

/* Set to 1 so the initial IDLE state is reported at startup */
uint8_t state_changed_g = 1u;

void app_next_state(app_state_t *p_app_state)
{
    SIO->GPIO_OUT_CLR = (1u << 1);
    SIO->GPIO_OUT_CLR = (1u << 2);

    switch(*p_app_state)
    {
        case APP_STATE_IDLE:
            *p_app_state = APP_STATE_RUNNING;
            break;

        case APP_STATE_RUNNING:
            *p_app_state = APP_STATE_DIAGNOSTIC;
            break;

        case APP_STATE_DIAGNOSTIC:
        default:
            *p_app_state = APP_STATE_IDLE;
            break;
    }
    state_changed_g = 1u;
}
