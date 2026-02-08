
typedef  enum {
    TIMER0_ALARM0 = 0,
    TIMER0_ALARM1,
    TIMER0_ALARM2,
    TIMER0_ALARM3
}TIMER0_Alarm_t;

typedef struct
{
    TIMER0_Alarm_t TIMER_Alarm;
}TIMER_Config_t;


typedef struct
{
    TIMER_RegDef_t *pTimerx;
    TIMER_Config_t TIMER_Config;
}TIMER_Handle_t;

void timer_init(TIMER_Handle_t *pTimerHandle);
void timer_irqInterruptConfig();