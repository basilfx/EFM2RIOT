/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32tg11b
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

/* Cortex-M0PLUS common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_emu(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_ldma(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_smu(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_usart0(void);
WEAK_DEFAULT void isr_acmp0(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_i2c1(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_usart1(void);
WEAK_DEFAULT void isr_usart2(void);
WEAK_DEFAULT void isr_uart0(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_pcnt0(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_crypto0(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_usart3(void);
WEAK_DEFAULT void isr_wtimer0(void);
WEAK_DEFAULT void isr_wtimer1(void);
WEAK_DEFAULT void isr_vdac0(void);
WEAK_DEFAULT void isr_csen(void);
WEAK_DEFAULT void isr_lesense(void);
WEAK_DEFAULT void isr_lcd(void);
WEAK_DEFAULT void isr_can0(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_emu,                /* 0 - EMU */
    isr_wdog0,              /* 1 - WDOG0 */
    isr_ldma,               /* 2 - LDMA */
    isr_gpio_even,          /* 3 - GPIO_EVEN */
    isr_smu,                /* 4 - SMU */
    isr_timer0,             /* 5 - TIMER0 */
    isr_usart0,             /* 6 - USART0 */
    isr_acmp0,              /* 7 - ACMP0 */
    isr_adc0,               /* 8 - ADC0 */
    isr_i2c0,               /* 9 - I2C0 */
    isr_i2c1,               /* 10 - I2C1 */
    isr_gpio_odd,           /* 11 - GPIO_ODD */
    isr_timer1,             /* 12 - TIMER1 */
    isr_usart1,             /* 13 - USART1 */
    isr_usart2,             /* 14 - USART2 */
    isr_uart0,              /* 15 - UART0 */
    isr_leuart0,            /* 16 - LEUART0 */
    isr_letimer0,           /* 17 - LETIMER0 */
    isr_pcnt0,              /* 18 - PCNT0 */
    isr_rtcc,               /* 19 - RTCC */
    isr_cmu,                /* 20 - CMU */
    isr_msc,                /* 21 - MSC */
    isr_crypto0,            /* 22 - CRYPTO0 */
    isr_cryotimer,          /* 23 - CRYOTIMER */
    isr_usart3,             /* 24 - USART3 */
    isr_wtimer0,            /* 25 - WTIMER0 */
    isr_wtimer1,            /* 26 - WTIMER1 */
    isr_vdac0,              /* 27 - VDAC0 */
    isr_csen,               /* 28 - CSEN */
    isr_lesense,            /* 29 - LESENSE */
    isr_lcd,                /* 30 - LCD */
    isr_can0,               /* 31 - CAN0 */
};
