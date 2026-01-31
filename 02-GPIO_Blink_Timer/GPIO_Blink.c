#include "pico/stdlib.h"
#include "raspBerryPico.h"
#include <stdint.h>

void __attribute__((used)) isr_irq0(void)
{
    if (TIMER0->INTR & (1 << 0))
    {
        TIMER0->INTR = (1 << 0);
        SIO->GPIO_OUT ^= (1 << 1);
        TIMER0->ALARM0 = TIMER0->TIMELR + 500000;
    }
}

int main()
{
    stdio_init_all();

    uint32_t watch1 = (GPIO1->CTRL);

    GPIO1->CTRL &= ~(0x1F);
    GPIO1->CTRL |= (0x05);

    PADS->IO[1] = (0x1 << 0x4) | 0x40;

    SIO->GPIO_OE &= ~(1 << 1);
    SIO->GPIO_OE |= (1 << 1);

    SIO->GPIO_OUT_CLR = (1 << 1);

    TIMER0->INTR = (1 << 0);
    TIMER0->INTE |= (1 << 0);
    TIMER0->ALARM0 = TIMER0->TIMELR + 1000000; // 2000 ms
    
    nvic_icpr[0] = (1 << 0); // Clear TIMER0 IRQ pending bit
    nvic_iser[0] |= (1 << 0); // Enable TIMER0 IRQ in NVIC

    while(1)
    {
        // __wfi();   // Wait For Interrupt
        // SIO->GPIO_OUT ^= (1 << 1);
        // sleep_ms(50);
    }
}
