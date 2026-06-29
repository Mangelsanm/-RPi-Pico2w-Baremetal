#include <stdio.h>
#include "raspBerryPico.h"
#include "timebase.h"

volatile uint32_t system_tick_ms = 0;

void __attribute__((used)) isr_irq0(void)
{
    if (TIMER0->INTR & (1u << 0))
    {
        TIMER0->INTR = (1u << 0);
        TIMER0->ALARM0 = TIMER0->TIMELR + 1000u;
        system_tick_ms++;
    }
}

int time_reached_owner(uint32_t now, uint32_t target)
{
    return ((int32_t)(now - target) >= 0);
}

uint32_t timebase_get_ms(void)
{
    return system_tick_ms;
}

uint32_t timebase_get_us(void)
{
    return TIMER0->TIMELR;
}

void timebase_init(void)
{
    TIMER_Handle_t TimerBlink;
    TimerBlink.pTimerx = TIMER0;
    TimerBlink.TIMER_Config.TIMER_Alarm = TIMER0_ALARM0;
    timer_init(&TimerBlink);
    
    nvic_icpr[0] = (1 << 0); // Clear TIMER0 IRQ pending bit
    nvic_iser[0] |= (1 << 0); // Enable TIMER0 IRQ in NVIC
}