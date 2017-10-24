/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efr32bg1v
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
void dummy_handler(void) {
    dummy_handler_default();
}

/* Cortex-M4 common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_emu(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_ldma(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_acmp0(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_idac0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_usart1_rx(void);
WEAK_DEFAULT void isr_usart1_tx(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_pcnt0(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_crypto(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_fpueh(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_emu,                /* 0 - EMU */
    (0UL),                  /* Reserved */
    isr_wdog0,              /* 2 - WDOG0 */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    isr_ldma,               /* 8 - LDMA */
    isr_gpio_even,          /* 9 - GPIO_EVEN */
    isr_timer0,             /* 10 - TIMER0 */
    isr_usart0_rx,          /* 11 - USART0_RX */
    isr_usart0_tx,          /* 12 - USART0_TX */
    isr_acmp0,              /* 13 - ACMP0 */
    isr_adc0,               /* 14 - ADC0 */
    isr_idac0,              /* 15 - IDAC0 */
    isr_i2c0,               /* 16 - I2C0 */
    isr_gpio_odd,           /* 17 - GPIO_ODD */
    isr_timer1,             /* 18 - TIMER1 */
    isr_usart1_rx,          /* 19 - USART1_RX */
    isr_usart1_tx,          /* 20 - USART1_TX */
    isr_leuart0,            /* 21 - LEUART0 */
    isr_pcnt0,              /* 22 - PCNT0 */
    isr_cmu,                /* 23 - CMU */
    isr_msc,                /* 24 - MSC */
    isr_crypto,             /* 25 - CRYPTO */
    isr_letimer0,           /* 26 - LETIMER0 */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    isr_rtcc,               /* 29 - RTCC */
    (0UL),                  /* Reserved */
    isr_cryotimer,          /* 31 - CRYOTIMER */
    (0UL),                  /* Reserved */
    isr_fpueh,              /* 33 - FPUEH */
};
