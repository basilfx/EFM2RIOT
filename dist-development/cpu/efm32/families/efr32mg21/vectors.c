/*
 * Copyright (C) 2015-2018 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efr32mg21
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

#include "vectors_cortexm.h"

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void)
{
    dummy_handler_default();
}

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_setamperhost(void);
WEAK_DEFAULT void isr_sembrx(void);
WEAK_DEFAULT void isr_sembtx(void);
WEAK_DEFAULT void isr_smu_secure(void);
WEAK_DEFAULT void isr_smu_privileged(void);
WEAK_DEFAULT void isr_emu(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_timer2(void);
WEAK_DEFAULT void isr_timer3(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_usart1_rx(void);
WEAK_DEFAULT void isr_usart1_tx(void);
WEAK_DEFAULT void isr_usart2_rx(void);
WEAK_DEFAULT void isr_usart2_tx(void);
WEAK_DEFAULT void isr_icache0(void);
WEAK_DEFAULT void isr_burtc(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_syscfg(void);
WEAK_DEFAULT void isr_ldma(void);
WEAK_DEFAULT void isr_lfxo(void);
WEAK_DEFAULT void isr_lfrco(void);
WEAK_DEFAULT void isr_ulfrco(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_i2c1(void);
WEAK_DEFAULT void isr_emudg(void);
WEAK_DEFAULT void isr_emuse(void);
WEAK_DEFAULT void isr_agc(void);
WEAK_DEFAULT void isr_bufc(void);
WEAK_DEFAULT void isr_frc_pri(void);
WEAK_DEFAULT void isr_frc(void);
WEAK_DEFAULT void isr_modem(void);
WEAK_DEFAULT void isr_protimer(void);
WEAK_DEFAULT void isr_rac_rsm(void);
WEAK_DEFAULT void isr_rac_seq(void);
WEAK_DEFAULT void isr_prortc(void);
WEAK_DEFAULT void isr_synth(void);
WEAK_DEFAULT void isr_acmp0(void);
WEAK_DEFAULT void isr_acmp1(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_wdog1(void);
WEAK_DEFAULT void isr_hfxo00(void);
WEAK_DEFAULT void isr_hfrco0(void);
WEAK_DEFAULT void isr_hfrcoem23(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_aes(void);
WEAK_DEFAULT void isr_iadc(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_dpll0(void);
WEAK_DEFAULT void isr_sw0(void);
WEAK_DEFAULT void isr_sw1(void);
WEAK_DEFAULT void isr_sw2(void);
WEAK_DEFAULT void isr_sw3(void);
WEAK_DEFAULT void isr_kernel0(void);
WEAK_DEFAULT void isr_kernel1(void);
WEAK_DEFAULT void isr_m33cti0(void);
WEAK_DEFAULT void isr_m33cti1(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    [ 0] = isr_setamperhost,       /* SETAMPERHOST */
    [ 1] = isr_sembrx,             /* SEMBRX */
    [ 2] = isr_sembtx,             /* SEMBTX */
    [ 3] = isr_smu_secure,         /* SMU_SECURE */
    [ 4] = isr_smu_privileged,     /* SMU_PRIVILEGED */
    [ 5] = isr_emu,                /* EMU */
    [ 6] = isr_timer0,             /* TIMER0 */
    [ 7] = isr_timer1,             /* TIMER1 */
    [ 8] = isr_timer2,             /* TIMER2 */
    [ 9] = isr_timer3,             /* TIMER3 */
    [10] = isr_rtcc,               /* RTCC */
    [11] = isr_usart0_rx,          /* USART0_RX */
    [12] = isr_usart0_tx,          /* USART0_TX */
    [13] = isr_usart1_rx,          /* USART1_RX */
    [14] = isr_usart1_tx,          /* USART1_TX */
    [15] = isr_usart2_rx,          /* USART2_RX */
    [16] = isr_usart2_tx,          /* USART2_TX */
    [17] = isr_icache0,            /* ICACHE0 */
    [18] = isr_burtc,              /* BURTC */
    [19] = isr_letimer0,           /* LETIMER0 */
    [20] = isr_syscfg,             /* SYSCFG */
    [21] = isr_ldma,               /* LDMA */
    [22] = isr_lfxo,               /* LFXO */
    [23] = isr_lfrco,              /* LFRCO */
    [24] = isr_ulfrco,             /* ULFRCO */
    [25] = isr_gpio_odd,           /* GPIO_ODD */
    [26] = isr_gpio_even,          /* GPIO_EVEN */
    [27] = isr_i2c0,               /* I2C0 */
    [28] = isr_i2c1,               /* I2C1 */
    [29] = isr_emudg,              /* EMUDG */
    [30] = isr_emuse,              /* EMUSE */
    [31] = isr_agc,                /* AGC */
    [32] = isr_bufc,               /* BUFC */
    [33] = isr_frc_pri,            /* FRC_PRI */
    [34] = isr_frc,                /* FRC */
    [35] = isr_modem,              /* MODEM */
    [36] = isr_protimer,           /* PROTIMER */
    [37] = isr_rac_rsm,            /* RAC_RSM */
    [38] = isr_rac_seq,            /* RAC_SEQ */
    [39] = isr_prortc,             /* PRORTC */
    [40] = isr_synth,              /* SYNTH */
    [41] = isr_acmp0,              /* ACMP0 */
    [42] = isr_acmp1,              /* ACMP1 */
    [43] = isr_wdog0,              /* WDOG0 */
    [44] = isr_wdog1,              /* WDOG1 */
    [45] = isr_hfxo00,             /* HFXO00 */
    [46] = isr_hfrco0,             /* HFRCO0 */
    [47] = isr_hfrcoem23,          /* HFRCOEM23 */
    [48] = isr_cmu,                /* CMU */
    [49] = isr_aes,                /* AES */
    [50] = isr_iadc,               /* IADC */
    [51] = isr_msc,                /* MSC */
    [52] = isr_dpll0,              /* DPLL0 */
    [53] = isr_sw0,                /* SW0 */
    [54] = isr_sw1,                /* SW1 */
    [55] = isr_sw2,                /* SW2 */
    [56] = isr_sw3,                /* SW3 */
    [57] = isr_kernel0,            /* KERNEL0 */
    [58] = isr_kernel1,            /* KERNEL1 */
    [59] = isr_m33cti0,            /* M33CTI0 */
    [60] = isr_m33cti1,            /* M33CTI1 */
};
