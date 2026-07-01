#include "soft_timer.h"
#include "timebase.h"

void soft_timer_start(soft_timer_t *timer, uint32_t timeout_ms)
{
    timer->start_time_ms = timebase_get_ms();
    timer->timeout_ms = timeout_ms;
    timer->running = 1;
}

void soft_timer_stop(soft_timer_t *timer)
{
    timer->running = 0;
}