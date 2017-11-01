/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efr32mg13p
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

/* Cortex-M4 common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_emu(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_wdog1(void);
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
WEAK_DEFAULT void isr_crypto0(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_fpueh(void);
WEAK_DEFAULT void isr_smu(void);
WEAK_DEFAULT void isr_wtimer0(void);
WEAK_DEFAULT void isr_usart2_rx(void);
WEAK_DEFAULT void isr_usart2_tx(void);
WEAK_DEFAULT void isr_i2c1(void);
WEAK_DEFAULT void isr_vdac0(void);
WEAK_DEFAULT void isr_csen(void);
WEAK_DEFAULT void isr_lesense(void);
WEAK_DEFAULT void isr_crypto1(void);
WEAK_DEFAULT void isr_trng0(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_emu,                /* 0 - EMU */
    (0UL),                  /* Reserved */
    isr_wdog0,              /* 2 - WDOG0 */
    isr_wdog1,              /* 3 - WDOG1 */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    isr_ldma,               /* 9 - LDMA */
    isr_gpio_even,          /* 10 - GPIO_EVEN */
    isr_timer0,             /* 11 - TIMER0 */
    isr_usart0_rx,          /* 12 - USART0_RX */
    isr_usart0_tx,          /* 13 - USART0_TX */
    isr_acmp0,              /* 14 - ACMP0 */
    isr_adc0,               /* 15 - ADC0 */
    isr_idac0,              /* 16 - IDAC0 */
    isr_i2c0,               /* 17 - I2C0 */
    isr_gpio_odd,           /* 18 - GPIO_ODD */
    isr_timer1,             /* 19 - TIMER1 */
    isr_usart1_rx,          /* 20 - USART1_RX */
    isr_usart1_tx,          /* 21 - USART1_TX */
    isr_leuart0,            /* 22 - LEUART0 */
    isr_pcnt0,              /* 23 - PCNT0 */
    isr_cmu,                /* 24 - CMU */
    isr_msc,                /* 25 - MSC */
    isr_crypto0,            /* 26 - CRYPTO0 */
    isr_letimer0,           /* 27 - LETIMER0 */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    (0UL),                  /* Reserved */
    isr_rtcc,               /* 31 - RTCC */
    (0UL),                  /* Reserved */
    isr_cryotimer,          /* 33 - CRYOTIMER */
    (0UL),                  /* Reserved */
    isr_fpueh,              /* 35 - FPUEH */
    isr_smu,                /* 36 - SMU */
    isr_wtimer0,            /* 37 - WTIMER0 */
    isr_usart2_rx,          /* 38 - USART2_RX */
    isr_usart2_tx,          /* 39 - USART2_TX */
    isr_i2c1,               /* 40 - I2C1 */
    isr_vdac0,              /* 41 - VDAC0 */
    isr_csen,               /* 42 - CSEN */
    isr_lesense,            /* 43 - LESENSE */
    isr_crypto1,            /* 44 - CRYPTO1 */
    isr_trng0,              /* 45 - TRNG0 */
};
