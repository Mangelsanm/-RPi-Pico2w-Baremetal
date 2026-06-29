#include "scheduler.h"
#include "timebase.h"

static uint8_t task_count = 0;
task_t tasks[SCHEDULER_MAX_TASKS];

void scheduler_init(void)
{
    uint8_t i;
    
    for (i = 0u; i < SCHEDULER_MAX_TASKS; i++)
    {
        tasks[i].fn = NULL;
        tasks[i].period_ms = 0u;
        tasks[i].next_run_time = 0u;
        tasks[i].exec_count = 0u;
        tasks[i].max_lateness = 0u;
        tasks[i].enabled = 0u;
        // tasks[i].last_execution_us = 0u;
        // tasks[i].max_execution_us = 0u;
    }
    task_count = 0;
}

int scheduler_add_task(task_fn_t fn, uint32_t period_ms)
{
    uint32_t now;

    if (task_count >= SCHEDULER_MAX_TASKS)
    {
        return -1; // No space for more tasks
    }

    if ((fn == NULL) || (period_ms == 0u))
    {
        return -1; // Invalid parameters
    }

    now = timebase_get_ms();

    tasks[task_count].fn = fn;
    tasks[task_count].period_ms = period_ms;
    tasks[task_count].next_run_time = now + period_ms;
    tasks[task_count].enabled = 1u;

    task_count++;

    return 0; // Task added successfully
}

void scheduler_run(void)
{
    uint32_t i;
    uint32_t now = timebase_get_ms();
    // uint32_t start_time_us, end_time_us, execution_time_us;

    for (i = 0u; i < SCHEDULER_MAX_TASKS; i++)
    {
        if ((tasks[i].enabled == 1) && time_reached_owner(now, tasks[i].next_run_time))
        {
            tasks[i].max_lateness = now - tasks[i].next_run_time;
            // start_time_us = timebase_get_us();
            tasks[i].fn();
            // end_time_us = timebase_get_us();
            
            // execution_time_us = end_time_us - start_time_us;
            // tasks[i].last_execution_us = execution_time_us;
            // if (execution_time_us > tasks[i].max_execution_us)
            // {
            //     tasks[i].max_execution_us = execution_time_us;
            // }
            tasks[i].exec_count++;
            tasks[i].next_run_time += tasks[i].period_ms;
        }
    }
}