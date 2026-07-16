#include "soft_timer.h"
#include "timebase.h"
#include "event.h"

void sw_timer_start(stw_timer_t *timer, uint32_t timeout_ms)
{
    timer->start_time_ms = timebase_get_ms();
    timer->timeout_ms = timeout_ms;
    timer->running = 1;
}

void sw_timer_stop(stw_timer_t *timer)
{
    timer->running = 0;
}

void sw_timer_is_expired(stw_timer_t *timer)
{
    if(timer->running)
    {
        uint32_t now = timebase_get_ms();
        if(time_reached_owner(now, timer->start_time_ms + timer->timeout_ms))
        {
            timer->running = 0;
            event_push(EVENT_TIMER_EXPIRED);
            // return 1; // Timer has expired
        }
    }
}
