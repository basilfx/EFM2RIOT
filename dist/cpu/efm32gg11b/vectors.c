/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32gg11b
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
WEAK_DEFAULT void isr_smu(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_acmp0(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_idac0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_i2c1(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_timer2(void);
WEAK_DEFAULT void isr_timer3(void);
WEAK_DEFAULT void isr_usart1_rx(void);
WEAK_DEFAULT void isr_usart1_tx(void);
WEAK_DEFAULT void isr_usart2_rx(void);
WEAK_DEFAULT void isr_usart2_tx(void);
WEAK_DEFAULT void isr_uart0_rx(void);
WEAK_DEFAULT void isr_uart0_tx(void);
WEAK_DEFAULT void isr_uart1_rx(void);
WEAK_DEFAULT void isr_uart1_tx(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_leuart1(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_pcnt0(void);
WEAK_DEFAULT void isr_pcnt1(void);
WEAK_DEFAULT void isr_pcnt2(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_crypto0(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_fpueh(void);
WEAK_DEFAULT void isr_usart3_rx(void);
WEAK_DEFAULT void isr_usart3_tx(void);
WEAK_DEFAULT void isr_usart4_rx(void);
WEAK_DEFAULT void isr_usart4_tx(void);
WEAK_DEFAULT void isr_wtimer0(void);
WEAK_DEFAULT void isr_wtimer1(void);
WEAK_DEFAULT void isr_wtimer2(void);
WEAK_DEFAULT void isr_wtimer3(void);
WEAK_DEFAULT void isr_i2c2(void);
WEAK_DEFAULT void isr_vdac0(void);
WEAK_DEFAULT void isr_timer4(void);
WEAK_DEFAULT void isr_timer5(void);
WEAK_DEFAULT void isr_timer6(void);
WEAK_DEFAULT void isr_usart5_rx(void);
WEAK_DEFAULT void isr_usart5_tx(void);
WEAK_DEFAULT void isr_csen(void);
WEAK_DEFAULT void isr_lesense(void);
WEAK_DEFAULT void isr_ebi(void);
WEAK_DEFAULT void isr_acmp2(void);
WEAK_DEFAULT void isr_adc1(void);
WEAK_DEFAULT void isr_lcd(void);
WEAK_DEFAULT void isr_sdio(void);
WEAK_DEFAULT void isr_eth(void);
WEAK_DEFAULT void isr_can0(void);
WEAK_DEFAULT void isr_can1(void);
WEAK_DEFAULT void isr_usb(void);
WEAK_DEFAULT void isr_rtc(void);
WEAK_DEFAULT void isr_wdog1(void);
WEAK_DEFAULT void isr_letimer1(void);
WEAK_DEFAULT void isr_trng0(void);
WEAK_DEFAULT void isr_qspi0(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_emu,                /* 0 - EMU */
    isr_wdog0,              /* 1 - WDOG0 */
    isr_ldma,               /* 2 - LDMA */
    isr_gpio_even,          /* 3 - GPIO_EVEN */
    isr_smu,                /* 4 - SMU */
    isr_timer0,             /* 5 - TIMER0 */
    isr_usart0_rx,          /* 6 - USART0_RX */
    isr_usart0_tx,          /* 7 - USART0_TX */
    isr_acmp0,              /* 8 - ACMP0 */
    isr_adc0,               /* 9 - ADC0 */
    isr_idac0,              /* 10 - IDAC0 */
    isr_i2c0,               /* 11 - I2C0 */
    isr_i2c1,               /* 12 - I2C1 */
    isr_gpio_odd,           /* 13 - GPIO_ODD */
    isr_timer1,             /* 14 - TIMER1 */
    isr_timer2,             /* 15 - TIMER2 */
    isr_timer3,             /* 16 - TIMER3 */
    isr_usart1_rx,          /* 17 - USART1_RX */
    isr_usart1_tx,          /* 18 - USART1_TX */
    isr_usart2_rx,          /* 19 - USART2_RX */
    isr_usart2_tx,          /* 20 - USART2_TX */
    isr_uart0_rx,           /* 21 - UART0_RX */
    isr_uart0_tx,           /* 22 - UART0_TX */
    isr_uart1_rx,           /* 23 - UART1_RX */
    isr_uart1_tx,           /* 24 - UART1_TX */
    isr_leuart0,            /* 25 - LEUART0 */
    isr_leuart1,            /* 26 - LEUART1 */
    isr_letimer0,           /* 27 - LETIMER0 */
    isr_pcnt0,              /* 28 - PCNT0 */
    isr_pcnt1,              /* 29 - PCNT1 */
    isr_pcnt2,              /* 30 - PCNT2 */
    isr_rtcc,               /* 31 - RTCC */
    isr_cmu,                /* 32 - CMU */
    isr_msc,                /* 33 - MSC */
    isr_crypto0,            /* 34 - CRYPTO0 */
    isr_cryotimer,          /* 35 - CRYOTIMER */
    isr_fpueh,              /* 36 - FPUEH */
    isr_usart3_rx,          /* 37 - USART3_RX */
    isr_usart3_tx,          /* 38 - USART3_TX */
    isr_usart4_rx,          /* 39 - USART4_RX */
    isr_usart4_tx,          /* 40 - USART4_TX */
    isr_wtimer0,            /* 41 - WTIMER0 */
    isr_wtimer1,            /* 42 - WTIMER1 */
    isr_wtimer2,            /* 43 - WTIMER2 */
    isr_wtimer3,            /* 44 - WTIMER3 */
    isr_i2c2,               /* 45 - I2C2 */
    isr_vdac0,              /* 46 - VDAC0 */
    isr_timer4,             /* 47 - TIMER4 */
    isr_timer5,             /* 48 - TIMER5 */
    isr_timer6,             /* 49 - TIMER6 */
    isr_usart5_rx,          /* 50 - USART5_RX */
    isr_usart5_tx,          /* 51 - USART5_TX */
    isr_csen,               /* 52 - CSEN */
    isr_lesense,            /* 53 - LESENSE */
    isr_ebi,                /* 54 - EBI */
    isr_acmp2,              /* 55 - ACMP2 */
    isr_adc1,               /* 56 - ADC1 */
    isr_lcd,                /* 57 - LCD */
    isr_sdio,               /* 58 - SDIO */
    isr_eth,                /* 59 - ETH */
    isr_can0,               /* 60 - CAN0 */
    isr_can1,               /* 61 - CAN1 */
    isr_usb,                /* 62 - USB */
    isr_rtc,                /* 63 - RTC */
    isr_wdog1,              /* 64 - WDOG1 */
    isr_letimer1,           /* 65 - LETIMER1 */
    isr_trng0,              /* 66 - TRNG0 */
    isr_qspi0,              /* 67 - QSPI0 */
};
