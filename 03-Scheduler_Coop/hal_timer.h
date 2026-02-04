#include "raspBerryPico.h"

typedef struct
{
    TIMER_Alarm_t TIMER_Alarm;
}TIMER_Config_t;


typedef struct
{
    TIMER_RegDef_t *pTimerx;
    TIMER_Config_t TIMER_Config;
}TIMER_Handle_t;

typedef  enum {
    TIMER0_ALARM0 = 0,
    TIMER0_ALARM1,
    TIMER0_ALARM2,
    TIMER0_ALARM3
} TIMER0_Alarm_t;

void timer_init(TIMER_RegDef_t *pTimerx)
// {
//     pTimerx->INTR = 0xFFFFFFFF; // Clear all interrupts
//     pTimerx->INTE = 0;          // Disable all interrupts
// }