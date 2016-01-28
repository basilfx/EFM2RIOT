/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Frequency test application for EFM32 boards
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"

#include "em_cmu.h"

#define PRINT_FREQ(x) (printf(#x ": %lu Hz\n", CMU_ClockFreqGet(cmuClock_##x)))

int main(void)
{
    /* main branches */
    PRINT_FREQ(CORE);
    PRINT_FREQ(CORELE);
    PRINT_FREQ(HFPER);

    /* sub branches */
    PRINT_FREQ(LFA);
    PRINT_FREQ(LFB);
#ifdef CMU_LFECLKSEL_LFE_DEFAULT
    PRINT_FREQ(LFE);
#endif

    /* ADC */
#ifdef ADC0
    PRINT_FREQ(ADC0);
#endif
#ifdef ADC1
    PRINT_FREQ(ADC1);
#endif

    /* DAC */
#ifdef DAC0
    PRINT_FREQ(DAC0);
#endif
#ifdef DAC1
    PRINT_FREQ(DAC1);
#endif

    /* I2C */
#ifdef I2C0
    PRINT_FREQ(I2C0);
#endif
#ifdef I2C1
    PRINT_FREQ(I2C1);
#endif

    /* RTC and RTCC */
#ifdef RTC
    PRINT_FREQ(RTC);
#endif
#ifdef RTCC
    PRINT_FREQ(RTCC);
#endif

    /* TIMER and LETIMER */
#ifdef TIMER0
    PRINT_FREQ(TIMER0);
#endif
#ifdef TIMER1
    PRINT_FREQ(TIMER1);
#endif
#ifdef TIMER2
    PRINT_FREQ(TIMER2);
#endif
#ifdef TIMER3
    PRINT_FREQ(TIMER3);
#endif
#ifdef LETIMER0
    PRINT_FREQ(LETIMER0);
#endif
#ifdef LETIMER1
    PRINT_FREQ(LETIMER1);
#endif

    /* UART, USART and LEUART */
#ifdef USART0
    PRINT_FREQ(USART0);
#endif
#ifdef USART1
    PRINT_FREQ(USART1);
#endif
#ifdef USART2
    PRINT_FREQ(USART2);
#endif
#ifdef UART0
    PRINT_FREQ(UART0);
#endif
#ifdef UART1
    PRINT_FREQ(UART1);
#endif
#ifdef LEUART0
    PRINT_FREQ(LEUART0);
#endif
#ifdef LEUART1
    PRINT_FREQ(LEUART1);
#endif

    return 0;
}
