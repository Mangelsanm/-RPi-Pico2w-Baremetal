#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include <stdint.h>

typedef struct
{
    uint32_t start_time_ms;
    uint32_t timeout_ms;
    uint8_t running;
} stw_timer_t;

void sw_timer_start(stw_timer_t *timer, uint32_t timeout_ms);
void sw_timer_stop(stw_timer_t *timer);
void sw_timer_is_expired(stw_timer_t *timer);

#endif
