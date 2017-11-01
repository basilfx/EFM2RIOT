/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_ezr32hg
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

/* Cortex-M0PLUS common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_dma(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_usartrf1_rx(void);
WEAK_DEFAULT void isr_usartrf1_tx(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_pcnt0(void);
WEAK_DEFAULT void isr_rtc(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_vcmp(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_aes(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_timer2(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_dma,                /* 0 - DMA */
    isr_gpio_even,          /* 1 - GPIO_EVEN */
    isr_timer0,             /* 2 - TIMER0 */
    (0UL),                  /* Reserved */
    isr_adc0,               /* 4 - ADC0 */
    isr_i2c0,               /* 5 - I2C0 */
    isr_gpio_odd,           /* 6 - GPIO_ODD */
    isr_timer1,             /* 7 - TIMER1 */
    isr_usartrf1_rx,        /* 8 - USARTRF1_RX */
    isr_usartrf1_tx,        /* 9 - USARTRF1_TX */
    isr_leuart0,            /* 10 - LEUART0 */
    isr_pcnt0,              /* 11 - PCNT0 */
    isr_rtc,                /* 12 - RTC */
    isr_cmu,                /* 13 - CMU */
    isr_vcmp,               /* 14 - VCMP */
    isr_msc,                /* 15 - MSC */
    isr_aes,                /* 16 - AES */
    isr_usart0_rx,          /* 17 - USART0_RX */
    isr_usart0_tx,          /* 18 - USART0_TX */
    (0UL),                  /* Reserved */
    isr_timer2,             /* 20 - TIMER2 */
};
