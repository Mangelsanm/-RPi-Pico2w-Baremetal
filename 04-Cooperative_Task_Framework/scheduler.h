#include <stdint.h>

#define SCHEDULER_MAX_TASKS 5u

typedef void (*task_fn_t)(void);

typedef struct {
    task_fn_t fn;
    uint32_t period_ms;
    uint32_t next_run_time;
    uint32_t exec_count;
    uint8_t enabled;
    // uint32_t last_execution_us;
    // uint32_t max_execution_us;
} task_t;

extern task_t tasks[SCHEDULER_MAX_TASKS];

int scheduler_add_task(task_fn_t fn, uint32_t period_ms);
void scheduler_init(void);
void scheduler_run(void);
