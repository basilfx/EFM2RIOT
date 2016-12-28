/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efr32bg12p
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
WEAK_DEFAULT void isr_frc_pri(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_wdog1(void);
WEAK_DEFAULT void isr_frc(void);
WEAK_DEFAULT void isr_modem(void);
WEAK_DEFAULT void isr_rac_seq(void);
WEAK_DEFAULT void isr_rac_rsm(void);
WEAK_DEFAULT void isr_bufc(void);
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
WEAK_DEFAULT void isr_agc(void);
WEAK_DEFAULT void isr_protimer(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_synth(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_rfsense(void);
WEAK_DEFAULT void isr_fpueh(void);
WEAK_DEFAULT void isr_smu(void);
WEAK_DEFAULT void isr_wtimer0(void);
WEAK_DEFAULT void isr_wtimer1(void);
WEAK_DEFAULT void isr_pcnt1(void);
WEAK_DEFAULT void isr_pcnt2(void);
WEAK_DEFAULT void isr_usart2_rx(void);
WEAK_DEFAULT void isr_usart2_tx(void);
WEAK_DEFAULT void isr_i2c1(void);
WEAK_DEFAULT void isr_usart3_rx(void);
WEAK_DEFAULT void isr_usart3_tx(void);
WEAK_DEFAULT void isr_vdac0(void);
WEAK_DEFAULT void isr_csen(void);
WEAK_DEFAULT void isr_lesense(void);
WEAK_DEFAULT void isr_crypto1(void);
WEAK_DEFAULT void isr_trng0(void);

/* interrupt vector table */
ISR_VECTORS const void *interrupt_vector[] = {
    /* Exception stack pointer */
    (void*) (&_estack),             /* pointer to the top of the stack */

    /* Cortex M4 handlers */
    (void*) reset_handler_default,  /* entry point of the program */
    (void*) nmi_default,            /* non maskable interrupt handler */
    (void*) hard_fault_default,     /* hard fault exception */
    (void*) mem_manage_default,     /* memory manage exception */
    (void*) bus_fault_default,      /* bus fault exception */
    (void*) usage_fault_default,    /* usage fault exception */

    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) isr_svc,                /* system call interrupt, in RIOT used for
                                     * switching into thread context on boot */
    (void*) debug_mon_default,      /* debug monitor exception */
    (void*) (0UL),                  /* Reserved */
    (void*) isr_pendsv,             /* pendSV interrupt, in RIOT the actual
                                     * context switching is happening here */
    (void*) isr_systick,            /* SysTick interrupt, not used in RIOT */

    /* EFM32 specific peripheral handlers */
    (void*) isr_emu,                /* 0 - EMU */
    (void*) isr_frc_pri,            /* 1 - FRC_PRI */
    (void*) isr_wdog0,              /* 2 - WDOG0 */
    (void*) isr_wdog1,              /* 3 - WDOG1 */
    (void*) isr_frc,                /* 4 - FRC */
    (void*) isr_modem,              /* 5 - MODEM */
    (void*) isr_rac_seq,            /* 6 - RAC_SEQ */
    (void*) isr_rac_rsm,            /* 7 - RAC_RSM */
    (void*) isr_bufc,               /* 8 - BUFC */
    (void*) isr_ldma,               /* 9 - LDMA */
    (void*) isr_gpio_even,          /* 10 - GPIO_EVEN */
    (void*) isr_timer0,             /* 11 - TIMER0 */
    (void*) isr_usart0_rx,          /* 12 - USART0_RX */
    (void*) isr_usart0_tx,          /* 13 - USART0_TX */
    (void*) isr_acmp0,              /* 14 - ACMP0 */
    (void*) isr_adc0,               /* 15 - ADC0 */
    (void*) isr_idac0,              /* 16 - IDAC0 */
    (void*) isr_i2c0,               /* 17 - I2C0 */
    (void*) isr_gpio_odd,           /* 18 - GPIO_ODD */
    (void*) isr_timer1,             /* 19 - TIMER1 */
    (void*) isr_usart1_rx,          /* 20 - USART1_RX */
    (void*) isr_usart1_tx,          /* 21 - USART1_TX */
    (void*) isr_leuart0,            /* 22 - LEUART0 */
    (void*) isr_pcnt0,              /* 23 - PCNT0 */
    (void*) isr_cmu,                /* 24 - CMU */
    (void*) isr_msc,                /* 25 - MSC */
    (void*) isr_crypto0,            /* 26 - CRYPTO0 */
    (void*) isr_letimer0,           /* 27 - LETIMER0 */
    (void*) isr_agc,                /* 28 - AGC */
    (void*) isr_protimer,           /* 29 - PROTIMER */
    (void*) isr_rtcc,               /* 30 - RTCC */
    (void*) isr_synth,              /* 31 - SYNTH */
    (void*) isr_cryotimer,          /* 32 - CRYOTIMER */
    (void*) isr_rfsense,            /* 33 - RFSENSE */
    (void*) isr_fpueh,              /* 34 - FPUEH */
    (void*) isr_smu,                /* 35 - SMU */
    (void*) isr_wtimer0,            /* 36 - WTIMER0 */
    (void*) isr_wtimer1,            /* 37 - WTIMER1 */
    (void*) isr_pcnt1,              /* 38 - PCNT1 */
    (void*) isr_pcnt2,              /* 39 - PCNT2 */
    (void*) isr_usart2_rx,          /* 40 - USART2_RX */
    (void*) isr_usart2_tx,          /* 41 - USART2_TX */
    (void*) isr_i2c1,               /* 42 - I2C1 */
    (void*) isr_usart3_rx,          /* 43 - USART3_RX */
    (void*) isr_usart3_tx,          /* 44 - USART3_TX */
    (void*) isr_vdac0,              /* 45 - VDAC0 */
    (void*) isr_csen,               /* 46 - CSEN */
    (void*) isr_lesense,            /* 47 - LESENSE */
    (void*) isr_crypto1,            /* 48 - CRYPTO1 */
    (void*) isr_trng0,              /* 49 - TRNG0 */
};
