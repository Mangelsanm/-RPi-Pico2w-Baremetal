
#define EVENT_QUEUE_SIZE 8

typedef enum
{
    EVENT_NONE = 0,
    EVENT_BUTTON_PRESS,
    EVENT_TIMER_EXPIRED,
    EVENT_COUNT,
} event_t;

void event_push(event_t event);
event_t event_pop(void);
