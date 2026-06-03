#include "app_tasks.h"
#include "raspBerryPico.h"

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
}

void task_blink()
{ 
    SIO->GPIO_OUT ^= (1 << 1); // Toggle GPIO1
}

void task_blink2()
{ 
    SIO->GPIO_OUT ^= (1 << 2); // Toggle GPIO2
}