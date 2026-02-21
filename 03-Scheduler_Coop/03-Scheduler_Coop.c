#include <stdio.h>
#include "pico/stdlib.h"
#include "raspBerryPico.h"

volatile uint32_t system_tick_ms = 0;
uint32_t last_blink_time = 0;

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
        uint32_t now = system_tick_ms;
        if (now - last_blink_time >= 1000) {
            SIO->GPIO_OUT ^= (1 << 1); // Toggle GPIO1
            last_blink_time += 1000; // Schedule next toggle in 1 second
        }
    }
}
