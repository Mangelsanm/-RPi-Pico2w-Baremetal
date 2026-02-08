#include <stdio.h>
#include "raspBerryPico.h"

void timer_init(TIMER_Handle_t *pTimerHandle)
{
    pTimerHandle->pTimerx->INTR = (1 << pTimerHandle->TIMER_Config.TIMER_Alarm);    // Clear specified alarm interrupt
    pTimerHandle->pTimerx->INTE |= (1 << pTimerHandle->TIMER_Config.TIMER_Alarm);   // Enable specified alarm interrupt

    // uint8_t temp = pTimerHandle->TIMER_Config.TIMER_Alarm;
    pTimerHandle->pTimerx->ALARM0 = pTimerHandle->pTimerx->TIMELR + 3000000; // Set alarm 0 for 1 second later
}