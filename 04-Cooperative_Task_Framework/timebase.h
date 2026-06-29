#include <stdio.h>

void timebase_init(void);
int time_reached_owner(uint32_t now, uint32_t target);
uint32_t timebase_get_ms(void);
uint32_t timebase_get_us(void);  