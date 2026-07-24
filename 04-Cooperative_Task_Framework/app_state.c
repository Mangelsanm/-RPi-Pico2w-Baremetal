#include "app_state.h"
#include "raspBerryPico.h"
#include "soft_timer.h"
#include "uart.h"

/* variables for the State Machine */
static app_state_t state_table[APP_STATE_COUNT][EVENT_COUNT];
app_state_t p_app_state = APP_STATE_IDLE;

/* Set to 1 so the initial IDLE state is reported at startup */
uint8_t state_changed_g = 1u;
stw_timer_t p_diagnostic_timer = {0};

// void app_next_state(app_state_t *p_app_state)
// {
//     SIO->GPIO_OUT_CLR = (1u << 1);
//     SIO->GPIO_OUT_CLR = (1u << 2);

//     switch(*p_app_state)
//     {
//         case APP_STATE_IDLE:
//             *p_app_state = APP_STATE_RUNNING;
//             break;

//         case APP_STATE_RUNNING:
//             *p_app_state = APP_STATE_DIAGNOSTIC;
//             sw_timer_start(&p_diagnostic_timer, 3000u); // Start a 3-second timer for diagnostic state
//             break;

//         case APP_STATE_DIAGNOSTIC:
//         default:
//             *p_app_state = APP_STATE_IDLE;
//             break;
//     }
//     state_changed_g = 1u;
// }

void app_transition(app_state_t new_state)
{
    switch(p_app_state)
    {
        case APP_STATE_IDLE:
            app_exit_idle();
            break;
            
        case APP_STATE_RUNNING:
            app_exit_running();
            break;

        case APP_STATE_DIAGNOSTIC:
        default:
            app_exit_diagnostic();
            break;
    }

    p_app_state = new_state;

    switch(p_app_state)
    {
        case APP_STATE_IDLE:
            app_enter_idle();
            break;
            
        case APP_STATE_RUNNING:
            app_enter_running();
            break;

        case APP_STATE_DIAGNOSTIC:
        default:
            app_enter_diagnostic();
            break;
    }

    state_changed_g = 1u;
}

void app_fsm_handle_event(event_t event)
{
    app_state_t new_state = state_table[p_app_state][event];

    if(new_state != p_app_state)
    {
        app_transition(new_state);
    }
}

void app_enter_idle(void)
{
    uart_write_string("Enter IDLE\r\n");
}
void app_enter_running(void)
{
    uart_write_string("Enter RUNNING\r\n");
}
void app_enter_diagnostic(void)
{
    uart_write_string("Enter DIAGNOSTIC\r\n");
    sw_timer_start(&p_diagnostic_timer, 3000u); // Start a 3-second timer for diagnostic state
}

void app_exit_idle(void)
{
    uart_write_string("Exit IDLE\r\n");
    SIO->GPIO_OUT_CLR = (1u << 1) | (1u << 2);
}
void app_exit_running(void)
{
    uart_write_string("Exit RUNNING\r\n");
    SIO->GPIO_OUT_CLR = (1u << 1) | (1u << 2);
}
void app_exit_diagnostic(void)
{
    uart_write_string("Exit DIAGNOSTIC\r\n");
    SIO->GPIO_OUT_CLR = (1u << 1) | (1u << 2);
}

void app_fsm_init(void)
{
    state_table[APP_STATE_IDLE][EVENT_BUTTON_PRESS] = APP_STATE_RUNNING;
    state_table[APP_STATE_RUNNING][EVENT_BUTTON_PRESS] = APP_STATE_DIAGNOSTIC;
    state_table[APP_STATE_DIAGNOSTIC][EVENT_BUTTON_PRESS] = APP_STATE_IDLE;
    state_table[APP_STATE_DIAGNOSTIC][EVENT_TIMER_EXPIRED] = APP_STATE_IDLE;
}