
#ifndef __BCM_H__
#define __BCM_H__

#include <stdint.h>

#define SYSCLOCK_HZ  250000000
#define APBCLOCK_HZ  125000000

#define __bit(X)             (0x01 << X)
#define bit_is_set(X, Y)     (X & (0x01 << Y))
#define bit_not_set(X, Y)    ((X & (0x01 << Y)) == 0)
#define set_bit(X, Y)        X |= __bit(Y)
#define clr_bit(X, Y)        X &= (~__bit(Y))

/*
 * Endereços dos periféricos
 */
#define PERIPH_BASE     0x3f000000
#define GPIO_ADDR       (PERIPH_BASE + 0x200000)
#define AUX_ADDR        (PERIPH_BASE + 0x215000)
#define AUX_MU_ADDR     (AUX_ADDR + 0x40)
#define AUX_SPI1_ADDR   (AUX_ADDR + 0x80)
#define AUX_SPI2_ADDR   (AUX_ADDR + 0xc0)
#define BSC0_ADDR       (PERIPH_BASE + 0x205000)
#define BSC1_ADDR       (PERIPH_BASE + 0x804000)
#define BSC2_ADDR       (PERIPH_BASE + 0x805000)
#define TIMER_ADDR      (PERIPH_BASE + 0x00B400)
#define IRQ_ADDR        (PERIPH_BASE + 0x00B200)
#define DMA_BASE        (PERIPH_BASE + 0x7000)
#define DMA0_ADDR       (DMA_BASE + 0)
#define DMA1_ADDR       (DMA_BASE + 0x100)
#define DMA2_ADDR       (DMA_BASE + 0x200)
#define DMA3_ADDR       (DMA_BASE + 0x300)
#define DMA4_ADDR       (DMA_BASE + 0x400)
#define DMA5_ADDR       (DMA_BASE + 0x500)
#define DMA6_ADDR       (DMA_BASE + 0x600)
#define DMA7_ADDR       (DMA_BASE + 0x700)
#define DMA8_ADDR       (DMA_BASE + 0x800)
#define DMA9_ADDR       (DMA_BASE + 0x900)
#define DMA10_ADDR      (DMA_BASE + 0xa00)
#define DMA11_ADDR      (DMA_BASE + 0xb00)
#define DMA12_ADDR      (DMA_BASE + 0xc00)
#define DMA13_ADDR      (DMA_BASE + 0xd00)
#define DMA14_ADDR      (DMA_BASE + 0xe00)
#define DMA_STATUS_ADDR (DMA_BASE + 0xfe0)
#define DMA_ENABLE_ADDR (DMA_BASE + 0xff0)
#define GPU_MAILBOX_ADDR (PERIPH_BASE + 0x00B880)
#define CORE_ADDR    0x40000000

/*
 * Periférico GPIO
 */
typedef struct {
   uint32_t gpfsel[6];   // Function select (3 bits/gpio)
   unsigned : 32;
   uint32_t gpset[2];    // Output set (1 bit/gpio)
   unsigned : 32;
   uint32_t gpclr[2];    // Output clear (1 bit/gpio)
   unsigned : 32;
   uint32_t gplev[2];    // Input read (1 bit/gpio)
   unsigned : 32;
   uint32_t gpeds[2];    // Event detect status
   unsigned : 32;
   uint32_t gpren[2];    // Rising-edge detect enable
   unsigned : 32;
   uint32_t gpfen[2];    // Falling-edge detect enable
   unsigned : 32;
   uint32_t gphen[2];    // High level detect enable
   unsigned : 32;
   uint32_t gplen[2];    // Low level detect enable
   unsigned : 32;
   uint32_t gparen[2];   // Async rising-edge detect
   unsigned : 32;
   uint32_t gpafen[2];   // Async falling-edge detect
   unsigned : 32;
   uint32_t gppud;       // Pull-up/down enable
   uint32_t gppudclk[2]; // Pull-up/down clock enable
} gpio_reg_t;
#define GPIO_REG(X)  ((volatile gpio_reg_t*)(GPIO_ADDR))->X

/*
 * Periférico AUX
 */
typedef struct {
   uint32_t irq;
   uint32_t enables;
} aux_reg_t;
#define AUX_REG(X)   ((volatile aux_reg_t*)(AUX_ADDR))->X

/*
 * AUX/Mini UART
 */
typedef struct {
   uint32_t io;
   uint32_t ier;
   uint32_t iir;
   uint32_t lcr;
   uint32_t mcr;
   uint32_t lsr;
   uint32_t msr;
   uint32_t scratch;
   uint32_t cntl;
   uint32_t stat;
   uint32_t baud;
} mu_reg_t;
#define MU_REG(X)    ((volatile mu_reg_t*)(AUX_MU_ADDR))->X

/*
 * AUX/SPI
 */
typedef struct {
   uint32_t cntl0;
   uint32_t cntl1;
   uint32_t stat;  
   uint32_t peek[4];
   unsigned : 32;
   uint32_t io[4];
   uint32_t txhold[4];
} spi_reg_t;
#define SPI_REG(X,Y)  ((volatile spi_reg_t*)(AUX_SPI ## X ## _ADDR))->Y

/*
 * BSC (I2C)
 */
typedef struct {
   uint32_t c;
   uint32_t s;
   uint32_t dlen;
   uint32_t a;
   uint32_t fifo;
   uint32_t div;
   uint32_t del;
   uint32_t clkt;
} bsc_reg_t;
#define BSC_REG(X,Y)  ((volatile bsc_reg_t*)(BSC ## X ## _ADDR))->Y

/*
 * Timer
 */
typedef struct {
   uint32_t load;
   uint32_t value;
   uint32_t control;
   uint32_t ack;
   uint32_t raw_irq;
   uint32_t masked_irq;
   uint32_t reload;
   uint32_t pre;
   uint32_t counter;
} timer_reg_t;
#define TIMER_REG(X)   ((volatile timer_reg_t*)(TIMER_ADDR))->X

/*
 * Controlador de interrupções.
 */
typedef struct {
   uint32_t pending_basic;
   uint32_t pending_1;
   uint32_t pending_2;
   uint32_t fiq;
   uint32_t enable_1;
   uint32_t enable_2;
   uint32_t enable_basic;
   uint32_t disable_1;
   uint32_t disable_2;
   uint32_t disable_basic;
} irq_reg_t;
#define IRQ_REG(X)     ((volatile irq_reg_t*)(IRQ_ADDR))->X

/*
 * Controlador de DMA
 */
typedef struct {
   uint32_t ti;
   uint32_t saddr;
   uint32_t daddr;
   uint32_t length;
   uint32_t stride;
   uint32_t nextcb;
   unsigned : 32;
   unsigned : 32;
} dma_cb_t;

typedef struct {
   uint32_t cs;
   uint32_t cb;
   uint32_t ti;
   uint32_t saddr;
   uint32_t daddr;
   uint32_t length;
   uint32_t stride;
   uint32_t nextcb;
   uint32_t debug;
} dma_reg_t;
#define DMA_CHN_REG(X,Y)  ((volatile dma_reg_t*)(DMA ## X ## _ADDR))->Y
#define DMA_STATUS_REG (*(volatile uint32_t*)DMA_STATUS_ADDR)
#define DMA_ENABLE_REG (*(volatile uint32_t*)DMA_ENABLE_ADDR)

/*
 * Core registers/mailboxes.
 */
typedef struct {
   uint32_t control;
   unsigned : 32; 
   uint32_t timer_pre;
   uint32_t irq_routing;
   uint32_t pmu_irq_enable;
   uint32_t pmu_irq_disable;
   unsigned : 32;
   uint32_t timer_count_lo;
   uint32_t timer_count_hi;
   uint32_t local_routing;
   unsigned : 32;
   uint32_t axi_counters;
   uint32_t axi_irq;
   uint32_t timer_control;
   uint32_t timer_flags;
   unsigned : 32;
   uint32_t timer_irq[4];
   uint32_t mailbox_irq[4];
   uint32_t irq_source[4];
   uint32_t fiq_source[4];
   uint32_t core0_mailbox_write[4];
   uint32_t core1_mailbox_write[4];
   uint32_t core2_mailbox_write[4];
   uint32_t core3_mailbox_write[4];
   uint32_t core0_mailbox_read[4];
   uint32_t core1_mailbox_read[4];
   uint32_t core2_mailbox_read[4];
   uint32_t core3_mailbox_read[4];
} core_reg_t;
#define CORE_REG(X)     ((volatile core_reg_t*)(CORE_ADDR))->X

/*
 * GPU/mailboxes.
 */

typedef struct {
   uint32_t read;
   unsigned : 32;
   unsigned : 32;
   unsigned : 32;
   uint32_t poll;
   uint32_t sender;
   uint32_t status;
   uint32_t config;
   uint32_t write;
} gpumail_reg_t;
#define GPUMAIL_REG(X)     ((volatile gpumail_reg_t*)(GPU_MAILBOX_ADDR))->X

#endif
