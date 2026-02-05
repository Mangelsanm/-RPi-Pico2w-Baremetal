#include <stdio.h>
#include "pico/stdlib.h"
#include "raspBerryPico.h"

void TIMER0_SetAlarm(uint32_t alarm_value, TIMER0_Alarm_t alarm)
{
    switch (alarm) {
        case TIMER0_ALARM0:
            TIMER0->ALARM0 = alarm_value;
            break;
        case TIMER0_ALARM1:
            TIMER0->ALARM1 = alarm_value;
            break;
        case TIMER0_ALARM2:
            TIMER0->ALARM2 = alarm_value;
            break;
        case TIMER0_ALARM3:
            TIMER0->ALARM3 = alarm_value;
            break;
        default:
            // Invalid alarm
            break;
    }
}

int main()
{
    stdio_init_all();

    TIMER_Handle_t TimerBlink;
    TimerBlink.pTimerx = TIMER0;
    TimerBlink.TIMER_Config.TIMER_Alarm = TIMER0_ALARM0;
    

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
