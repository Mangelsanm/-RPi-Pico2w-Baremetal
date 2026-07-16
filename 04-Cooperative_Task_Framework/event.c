#include <stdint.h>
#include "event.h"

static volatile event_t event_queue[EVENT_QUEUE_SIZE];
static volatile uint8_t event_head = 0;
static volatile uint8_t event_tail = 0;

void event_push(event_t event)
{
    uint8_t next_head = (event_head + 1) % EVENT_QUEUE_SIZE;

    if(next_head != event_tail)
    {
        event_queue[event_head] = event;
        event_head = next_head;
    }
}

event_t event_pop(void)
{
    event_t  event = EVENT_NONE;
    uint8_t next_tail = (event_tail + 1) % EVENT_QUEUE_SIZE;

    if(event_head != event_tail)
    {
        event = event_queue[event_tail];
        event_tail = next_tail;
    }
    return event;
}