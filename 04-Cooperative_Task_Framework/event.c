#include <stdint.h>
#include "event.h"

static volatile event_t high_queue[EVENT_QUEUE_SIZE];
static volatile event_t normal_queue[EVENT_QUEUE_SIZE];

static volatile uint8_t normal_head = 0;
static volatile uint8_t normal_tail = 0;
static volatile uint8_t high_head = 0;
static volatile uint8_t high_tail = 0;

void event_push(event_t event, event_priority_t priority)
{
    if(priority == HIGH)
    {
        push_high(event);
    }
    else
    {
        push_normal(event);
    }
}

event_t event_pop(void)
{
    // event_t  event = EVENT_NONE;
    // uint8_t next_tail = (event_tail + 1) % EVENT_QUEUE_SIZE; // move this line inside the if statement to avoid unnecessary computation when the queue is empty

    if(high_head != high_tail)
    {
        return pop_high();
    }
    else
    {
        return pop_normal();
    }
}

void push_high(event_t event)
{
    uint8_t next_head = (high_head + 1) % EVENT_QUEUE_SIZE;

    if(next_head != high_tail)
    {
        high_queue[high_head] = event;
        high_head = next_head;
    }
}

event_t pop_high(void)
{
    event_t event = EVENT_NONE;

    if(high_head != high_tail)
    {
        event = high_queue[high_tail];
        high_tail = (high_tail + 1) % EVENT_QUEUE_SIZE;
    }

    return event;
}

void push_normal(event_t event)
{
    uint8_t next_head = (normal_head + 1) % EVENT_QUEUE_SIZE;

    if(next_head != normal_tail)
    {
        normal_queue[normal_head] = event;
        normal_head = next_head;
    }
}

event_t pop_normal(void)
{
    event_t event = EVENT_NONE;

    if(normal_head != normal_tail)
    {
        event = normal_queue[normal_tail];
        normal_tail = (normal_tail + 1) % EVENT_QUEUE_SIZE;
    }
    return event;
}