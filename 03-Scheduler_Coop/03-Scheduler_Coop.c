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

    TIMER0->INTR = (1 << TIMER0_ALARM0); // Clear alarm 0 interrupt
    TIMER0->INTE |= (1 << TIMER0_ALARM0); // Enable alarm 0 interrupt

    

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
