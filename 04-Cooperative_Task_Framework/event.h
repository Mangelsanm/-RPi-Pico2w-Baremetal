
#define EVENT_QUEUE_SIZE 8

typedef enum
{
    EVENT_NONE = 0,
    EVENT_BUTTON_PRESS,
    EVENT_TIMER_EXPIRED,
    EVENT_COUNT,
} event_t;

typedef enum
{
    NORMAL = 0,
    HIGH,
} event_priority_t;

void event_push(event_t event, event_priority_t priority);
event_t event_pop(void);

void push_high(event_t event);
event_t pop_high(void);

void push_normal(event_t event);
event_t pop_normal(void);
