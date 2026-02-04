#define APBPERIPH_BASE      0X40000000
#define SIO_BASEADDR        0xD0000000
#define PPB_BASEADDR        0xE0000000

/* NVIC Registers offset */
#define NVIC_ISER0_OFFSET    0xe100
#define NVIC_ICER0_OFFSET    0xe180
#define NVIC_ISPR0_OFFSET    0xe200
#define NVIC_ICPR0_OFFSET    0xe280
/*************************/

#define nvic_iser ((uint32_t *)(PPB_BASEADDR + NVIC_ISER0_OFFSET))
#define nvic_icer ((uint32_t *)(PPB_BASEADDR + NVIC_ICER0_OFFSET))
#define nvic_ispr ((uint32_t *)(PPB_BASEADDR + NVIC_ISPR0_OFFSET))
#define nvic_icpr ((uint32_t *)(PPB_BASEADDR + NVIC_ICPR0_OFFSET))

#define RESET_BASEADDR      (APBPERIPH_BASE + 0x20000)

#define IOBANK0_BASEADDR    (APBPERIPH_BASE + 0x28000)
#define PADSBANK0_BASEADDR  (APBPERIPH_BASE + 0x38000)

#define GPIO0_BASEADDR		(IOBANK0_BASEADDR + 0X0000)
#define GPIO1_BASEADDR		(IOBANK0_BASEADDR + 0X0008)
#define GPIO2_BASEADDR		(IOBANK0_BASEADDR + 0X0010)

#define UART0_BASEADDR      (APBPERIPH_BASE + 0x70000)
#define UART1_BASEADDR      (APBPERIPH_BASE + 0x78000)

#define TIMER0_BASEADDR     (APBPERIPH_BASE + 0xb0000)

typedef struct
{
    volatile uint32_t RESET;        // Reset Control Register (0x000)
    volatile uint32_t WDSEL;        // Watchdog Select Register (0x004)
    volatile uint32_t RESET_DONE;   // Reset Done Register (0x008)
} RESET_RegDef_t;

#define RESET   ((RESET_RegDef_t *)RESET_BASEADDR)

// typedef struct
// {
//     volatile uint32_t GPIO0_STATUS;    // GPIO Status Register (0x000)
//     volatile uint32_t GPIO0_CTRL;      // GPIO Control Register (0x004)
//     volatile uint32_t GPIO1_STATUS;    // GPIO Status Register (0x008)
//     volatile uint32_t GPIO1_CTRL;      // GPIO Control Register (0x00C)
// } IOBANK0_RegDef_t;

typedef struct
{
    volatile uint32_t STATUS;
    volatile uint32_t CTRL;
} IOBANK0_RegDef_t;

#define GPIO0   ((IOBANK0_RegDef_t *)GPIO0_BASEADDR)
#define GPIO1   ((IOBANK0_RegDef_t *)GPIO1_BASEADDR)
#define GPIO2   ((IOBANK0_RegDef_t *)GPIO2_BASEADDR)

typedef struct
{
    volatile uint32_t VOLTAGE_SELECT;
    volatile uint32_t IO[48];
} PADSBANK0_RegDef_t;

#define PADS    ((PADSBANK0_RegDef_t *)PADSBANK0_BASEADDR)

typedef struct
{
    volatile uint32_t CPUID;
    volatile uint32_t GPIO_IN;
    volatile uint32_t GPIO_HI_IN[2];
    volatile uint32_t GPIO_OUT;
    volatile uint32_t GPIO_HI_OUT;
    volatile uint32_t GPIO_OUT_SET;
    volatile uint32_t GPIO_HI_OUT_SET;
    volatile uint32_t GPIO_OUT_CLR;
    volatile uint32_t GPIO_HI_OUT_CLR;
    volatile uint32_t GPIO_OUT_XOR;
    volatile uint32_t GPIO_HI_OUT_XOR;
    volatile uint32_t GPIO_OE;
    volatile uint32_t GPIO_HI_OE;
}SIO_RegDef_t;

#define SIO     ((SIO_RegDef_t *)SIO_BASEADDR)

typedef struct
{
    volatile uint32_t DR;           // Data Register (0x000)
    volatile uint32_t RSR;          // Receive Status / Error Clear (0x004)
    volatile uint32_t RESERVED0[4]; // Padding for 0x008, 0x00C, 0x010, 0x014
    volatile uint32_t FR;           // Flag Register (0x018)
    volatile uint32_t RESERVED1[2]; // Padding for 0x01C, 0x020
    volatile uint32_t IBRD;         // Integer Baud rate divisor (0x024)
    volatile uint32_t FBRD;         // Fractional Baud rate divisor (0x028)
    volatile uint32_t LCR_H;        // Line Control (0x02C)
    volatile uint32_t CR;           // Control Register (0x030)
    volatile uint32_t IFLS;         // FIFO level select (0x034)
    volatile uint32_t IMSC;         // Interrupt mask set/clear (0x038)
    volatile uint32_t RIS;          // Raw interrupt status (0x03C)
    volatile uint32_t MIS;          // Masked interrupt status (0x040)
    volatile uint32_t ICR;          // Interrupt clear (0x044)
} UART_RegDef_t;

#define UART0   ((UART_RegDef_t *)UART0_BASEADDR)
#define UART1   ((UART_RegDef_t *)UART1_BASEADDR)

/*
 * Clock Enable Macros for UARTx Peripherals
 */
#define UART0_PCLK_EN()    do { \
    RESET->RESET &= ~(1 << 26); \
    while(!(RESET->RESET_DONE & (1 << 26))); \
} while(0)
#define UART1_PCLK_EN()    do { \
    RESET->RESET &= ~(1 << 27); \
    while(!(RESET->RESET_DONE & (1 << 27))); \
} while(0)

typedef struct
{
    volatile uint32_t TIMEHW;      // Timer High Write (0x00)
    volatile uint32_t TIMELW;      // Timer Low Write (0x04)
    volatile uint32_t TIMEHR;      // Timer High Read (0x08)
    volatile uint32_t TIMELR;      // Timer Low Read (0x0C)
    volatile uint32_t ALARM0;     // Alarm 0 (0x10)
    volatile uint32_t ALARM1;     // Alarm 1 (0x14)
    volatile uint32_t ALARM2;     // Alarm 2 (0x18)
    volatile uint32_t ALARM3;     // Alarm 3 (0x1C)
    volatile uint32_t ARMED;      // Armed (0x20)
    volatile uint32_t TIMERAWH;   // Raw read from bits 63:32 of time (0x24)
    volatile uint32_t TIMERAWL;   // Raw read from bits 31:0 of time (0x28)
    volatile uint32_t DBGPAUSE;    // Debug Pause (0x2C)
    volatile uint32_t PAUSE;       // Pause (0x30)
    volatile uint32_t LOCKED;      // Locked (0x34)
    volatile uint32_t SOURCE;      // Source (0x38)
    volatile uint32_t INTR;        // Interrupt (0x3C)
    volatile uint32_t INTE;        // Interrupt Enable (0x40)
    volatile uint32_t INTF;       // Interrupt Force (0x44)
    volatile uint32_t INTS;       // Interrupt Status (0x48)
}TIMER_RegDef_t;

#define TIMER0   ((TIMER_RegDef_t *)TIMER0_BASEADDR)

#include "hal_timer.h"