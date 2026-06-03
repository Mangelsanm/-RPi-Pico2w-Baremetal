#include "raspBerryPico.h"
#include "uart.h"

void uart_init_own(void)
{
    GPIO4->CTRL &= ~(0x1F);
    GPIO4->CTRL |= (0x02);
    PADS->IO[4] &= ~((0x3u << 4) | (0x1u << 8));
    PADS->IO[4] |= (0x1u << 4);

    UART1->CR = 0; // Disable UART1
    
    uart_set_baud_rate(9600); // Set baud rate to 9600
    
    UART1->LCR_H = (0x3u << 5);
    UART1->CR = (0x1u << 8) | (0x1u << 0); // Enable UART1
}

void uart_set_baud_rate(uint32_t baud_rate)
{
    uint32_t baud_div_x64;
    uint32_t integer_div;
    uint32_t fractional_div;

    baud_div_x64 = ((150000000u * 4u) + (baud_rate / 2u)) / baud_rate;

    integer_div = baud_div_x64 / 64u;
    fractional_div = baud_div_x64 % 64u;

    UART1->IBRD = (uint16_t)integer_div;
    UART1->FBRD = (uint8_t)fractional_div;
}

void uart_write_byte(uint8_t byte)
{
    volatile uint8_t debug_last_tx = 0; // For debugging purposes, to track the last transmitted byte
    while (UART1->FR & (0x1u << 5)) {
        // Wait until the transmit FIFO is not full
    }
    UART1->DR = byte; // Write the byte to the data register
    debug_last_tx = byte;
}
void uart_write_string(const char *str)
{
    while (*str != '\0')
    {
        uart_write_byte((uint8_t)*str);
        str++;
    }
}