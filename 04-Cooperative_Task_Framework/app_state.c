#include "app_state.h"
#include "raspBerryPico.h"
#include "soft_timer.h"

/* Set to 1 so the initial IDLE state is reported at startup */
uint8_t state_changed_g = 1u;
stw_timer_t p_diagnostic_timer = {0};

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
            sw_timer_start(&p_diagnostic_timer, 3000u); // Start a 3-second timer for diagnostic state
            *p_app_state = APP_STATE_DIAGNOSTIC;
            break;

        case APP_STATE_DIAGNOSTIC:
        default:
            *p_app_state = APP_STATE_IDLE;
            break;
    }
    state_changed_g = 1u;
}
