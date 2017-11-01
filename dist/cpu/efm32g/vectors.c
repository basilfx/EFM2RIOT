/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32g
 * @{
 *
 * @file
 * @brief       Startup code and interrupt vector definition
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdint.h>
#include "vectors_cortexm.h"

/* get the start of the ISR stack as defined in the linkerscript */
extern uint32_t _estack;

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void)
{
    dummy_handler_default();
}

/* Cortex-M3 common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_dma(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_acmp0(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_dac0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_timer2(void);
WEAK_DEFAULT void isr_usart1_rx(void);
WEAK_DEFAULT void isr_usart1_tx(void);
WEAK_DEFAULT void isr_usart2_rx(void);
WEAK_DEFAULT void isr_usart2_tx(void);
WEAK_DEFAULT void isr_uart0_rx(void);
WEAK_DEFAULT void isr_uart0_tx(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_leuart1(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_pcnt0(void);
WEAK_DEFAULT void isr_pcnt1(void);
WEAK_DEFAULT void isr_pcnt2(void);
WEAK_DEFAULT void isr_rtc(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_vcmp(void);
WEAK_DEFAULT void isr_lcd(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_aes(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_dma,                /* 0 - DMA */
    isr_gpio_even,          /* 1 - GPIO_EVEN */
    isr_timer0,             /* 2 - TIMER0 */
    isr_usart0_rx,          /* 3 - USART0_RX */
    isr_usart0_tx,          /* 4 - USART0_TX */
    isr_acmp0,              /* 5 - ACMP0 */
    isr_adc0,               /* 6 - ADC0 */
    isr_dac0,               /* 7 - DAC0 */
    isr_i2c0,               /* 8 - I2C0 */
    isr_gpio_odd,           /* 9 - GPIO_ODD */
    isr_timer1,             /* 10 - TIMER1 */
    isr_timer2,             /* 11 - TIMER2 */
    isr_usart1_rx,          /* 12 - USART1_RX */
    isr_usart1_tx,          /* 13 - USART1_TX */
    isr_usart2_rx,          /* 14 - USART2_RX */
    isr_usart2_tx,          /* 15 - USART2_TX */
    isr_uart0_rx,           /* 16 - UART0_RX */
    isr_uart0_tx,           /* 17 - UART0_TX */
    isr_leuart0,            /* 18 - LEUART0 */
    isr_leuart1,            /* 19 - LEUART1 */
    isr_letimer0,           /* 20 - LETIMER0 */
    isr_pcnt0,              /* 21 - PCNT0 */
    isr_pcnt1,              /* 22 - PCNT1 */
    isr_pcnt2,              /* 23 - PCNT2 */
    isr_rtc,                /* 24 - RTC */
    isr_cmu,                /* 25 - CMU */
    isr_vcmp,               /* 26 - VCMP */
    isr_lcd,                /* 27 - LCD */
    isr_msc,                /* 28 - MSC */
    isr_aes,                /* 29 - AES */
};
