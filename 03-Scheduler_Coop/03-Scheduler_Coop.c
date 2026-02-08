#include <stdio.h>
#include "pico/stdlib.h"
#include "raspBerryPico.h"

// void TIMER0_SetAlarm(uint32_t alarm_value, TIMER0_Alarm_t alarm)
// {
//     switch (alarm) {
//         case TIMER0_ALARM0:
//             TIMER0->ALARM0 = alarm_value;
//             break;
//         case TIMER0_ALARM1:
//             TIMER0->ALARM1 = alarm_value;
//             break;
//         case TIMER0_ALARM2:
//             TIMER0->ALARM2 = alarm_value;
//             break;
//         case TIMER0_ALARM3:
//             TIMER0->ALARM3 = alarm_value;
//             break;
//         default:
//             // Invalid alarm
//             break;
//     }
// }

void __attribute__((used)) isr_irq0(void)
{
    if (TIMER0->INTR & (1 << 0))
    {
        TIMER0->INTR = (1 << 0);
        SIO->GPIO_OUT ^= (1 << 1);
        TIMER0->ALARM0 = TIMER0->TIMELR + 1000000;
    }
}

int main()
{
    stdio_init_all();

    GPIO1->CTRL &= ~(0x1F);
    GPIO1->CTRL |= (0x05);

    PADS->IO[1] = (0x1 << 0x4) | 0x40;

    SIO->GPIO_OE &= ~(1 << 1);
    SIO->GPIO_OE |= (1 << 1);

    SIO->GPIO_OUT_CLR = (1 << 1);

    TIMER_Handle_t TimerBlink;
    TimerBlink.pTimerx = TIMER0;
    TimerBlink.TIMER_Config.TIMER_Alarm = TIMER0_ALARM0;
    timer_init(&TimerBlink);

    nvic_icpr[0] = (1 << 0); // Clear TIMER0 IRQ pending bit
    nvic_iser[0] |= (1 << 0); // Enable TIMER0 IRQ in NVIC

    while (true) {

    }
}
