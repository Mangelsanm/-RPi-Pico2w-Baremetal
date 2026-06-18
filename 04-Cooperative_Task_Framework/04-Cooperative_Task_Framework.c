#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/sync.h"
#include "timebase.h"
#include "scheduler.h"
#include "app_tasks.h"
#include "uart.h"


int main()
{
    stdio_init_all();
    app_tasks_init();
    uart_init_own();
    timebase_init();
    scheduler_init();

    scheduler_add_task(task_blink, 500);
    scheduler_add_task(task_blink2, 1000);
    scheduler_add_task(task_scheduler_log, 1000);
    scheduler_add_task(task_button_monitor, 10);

    while (true) {
        scheduler_run();
        __wfi();
    }
}
