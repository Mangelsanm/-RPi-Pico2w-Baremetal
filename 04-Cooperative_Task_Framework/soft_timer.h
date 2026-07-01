#include <stdint.h>

typedef struct
{
    uint32_t start_time_ms;
    uint32_t timeout_ms;
    uint8_t running;
} soft_timer_t;

void soft_timer_start(soft_timer_t *timer, uint32_t timeout_ms);
void soft_timer_stop(soft_timer_t *timer);
