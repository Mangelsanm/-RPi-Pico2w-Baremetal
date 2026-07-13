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

// void app_next_state(app_state_t *p_app_state);
void app_transition(app_state_t *p_app_state, app_state_t new_state);

/* Entry Actions */
static void app_enter_idle(void);
static void app_enter_running(void);
static void app_enter_diagnostic(void);

/* Exit Actions */
static void app_exit_idle(void);
static void app_exit_running(void);
static void app_exit_diagnostic(void);