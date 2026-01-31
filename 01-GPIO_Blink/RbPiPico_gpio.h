#include "raspBerryPico.h"
#include <stdint.h>

void hal_gpio_init(IOBANK0_RegDef_t *GPIOx, uint8_t pin_number, uint8_t function);