#include <stdio.h>
#include "pico/stdlib.h"
#include "raspBerryPico.h"
#include "hardware/sync.h"

volatile uint32_t system_tick_ms = 0;

typedef struct {
    void (*fn)(void);
    uint32_t period_ms;
    uint32_t next_run_time;
} task_t;

static task_t blink_task;
static task_t blink_task2;

void __attribute__((used)) isr_irq0(void)
{
    if (TIMER0->INTR & (1u << 0))
    {
        TIMER0->INTR = (1u << 0);
        TIMER0->ALARM0 = TIMER0->TIMELR + 1000u;
        system_tick_ms++;
    }
}

void task_blink()
{ 
    SIO->GPIO_OUT ^= (1 << 1); // Toggle GPIO1
}

void task_blink2()
{ 
    SIO->GPIO_OUT ^= (1 << 2); // Toggle GPIO2
}

int main()
{
    stdio_init_all();
    /*GPIO1 Configuration*/
    GPIO1->CTRL &= ~(0x1F);
    GPIO1->CTRL |= (0x05);
    PADS->IO[1] = (0x1 << 0x4) | 0x40;
    SIO->GPIO_OE &= ~(1 << 1);
    SIO->GPIO_OE |= (1 << 1);
    SIO->GPIO_OUT_CLR = (1 << 1);
    
    /*GPIO2 Configuration*/
    GPIO2->CTRL &= ~(0x1F);
    GPIO2->CTRL |= (0x05);
    PADS->IO[2] = (0x1 << 0x4) | 0x40;
    SIO->GPIO_OE &= ~(1 << 2);
    SIO->GPIO_OE |= (1 << 2);
    SIO->GPIO_OUT_CLR = (1 << 2);

    TIMER_Handle_t TimerBlink;
    TimerBlink.pTimerx = TIMER0;
    TimerBlink.TIMER_Config.TIMER_Alarm = TIMER0_ALARM0;
    timer_init(&TimerBlink);

    nvic_icpr[0] = (1 << 0); // Clear TIMER0 IRQ pending bit
    nvic_iser[0] |= (1 << 0); // Enable TIMER0 IRQ in NVIC

    blink_task.fn = task_blink;
    blink_task.period_ms = 500;
    blink_task.next_run_time = system_tick_ms + blink_task.period_ms;
    
    blink_task2.fn = task_blink2;
    blink_task2.period_ms = 1000;
    blink_task2.next_run_time = system_tick_ms + blink_task2.period_ms;

    while (true) {
        uint32_t now = system_tick_ms;
        if ((int32_t)(now - blink_task.next_run_time) >= 0) {
            blink_task.fn();
            blink_task.next_run_time += blink_task.period_ms; // Schedule next run
        }
        if ((int32_t)(now - blink_task2.next_run_time) >= 0) {
            blink_task2.fn();
            blink_task2.next_run_time += blink_task2.period_ms; // Schedule next run
        }
        __wfi();
    }
}
