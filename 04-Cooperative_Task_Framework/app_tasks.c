#include "app_tasks.h"
#include "raspBerryPico.h"
#include "uart.h"
#include "timebase.h"
#include "scheduler.h"
#include <stdio.h>

static uint8_t button_raw_state;
static uint8_t button_last_raw_state;
static uint8_t button_stable_state;
static uint8_t button_counter;
static uint8_t button_pressed_event;

void app_tasks_init(void)
{
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

    /* GPIO15 as button input */
    GPIO15->CTRL &= ~(0x1F);
    GPIO15->CTRL |= (0x05); /* SIO */

    PADS->IO[15] = (0x1 << 6) | (0x1 << 3); /* IE = 1, Pull-up enabled */

    SIO->GPIO_OE &= ~(1 << 15); /* Input */
}

void task_blink()
{ 
    SIO->GPIO_OUT ^= (1 << 1); // Toggle GPIO1
}

void task_blink2()
{ 
    SIO->GPIO_OUT ^= (1 << 2); // Toggle GPIO2
}

void task_uart_log()
{
    uart_write_string("Task UART Log: Hello from the scheduler!\r\n");
}

void task_scheduler_log(void)
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer),
    "tick=%lu blink1=%lu blink2=%lu\n late1=%lu late2=%lu\r\n",
    (unsigned long)timebase_get_ms(), 
    (unsigned long)tasks[0].exec_count,
    (unsigned long)tasks[1].exec_count,
    (unsigned long)tasks[0].max_lateness,
    (unsigned long)tasks[1].max_lateness);
    uart_write_string(buffer);
}

void task_button_monitor(void)
{
    button_raw_state = (uint8_t)((SIO->GPIO_IN >> 15) & 0x01u);
    button_pressed_event = 0u;

    if(button_raw_state == button_last_raw_state)
    {
        if(button_counter < debounce_threshold)
        {
            button_counter++;
        }
    }
    else
    {
        button_counter = 0u;
    }

    if(button_counter >= debounce_threshold)
    {
        if(button_stable_state != button_raw_state)
        {
            button_stable_state = button_raw_state;
            if(button_stable_state == 0u)
            {
                button_pressed_event = 1u;
            }
        }
    }

    if(button_pressed_event == 1u)
    {
        uart_write_string("button pressed\r\n");
    }

    button_last_raw_state = button_raw_state;
}
