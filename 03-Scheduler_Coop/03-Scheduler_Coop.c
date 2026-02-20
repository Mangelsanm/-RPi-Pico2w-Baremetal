#include <stdio.h>
#include "pico/stdlib.h"
#include "raspBerryPico.h"

volatile uint32_t system_tick_ms = 0;

void __attribute__((used)) isr_irq0(void)
{
    if (TIMER0->INTR & (1 << 0))
    {
        TIMER0->INTR = (1 << 0);
        TIMER0->ALARM0 = TIMER0->TIMELR + 1000;
        system_tick_ms++;
    }
}

int main()
{
    stdio_init_all();

    TIMER_Handle_t TimerBlink;
    TimerBlink.pTimerx = TIMER0;
    TimerBlink.TIMER_Config.TIMER_Alarm = TIMER0_ALARM0;
    timer_init(&TimerBlink);

    nvic_icpr[0] = (1 << 0); // Clear TIMER0 IRQ pending bit
    nvic_iser[0] |= (1 << 0); // Enable TIMER0 IRQ in NVIC

    while (true) {

    }
}
