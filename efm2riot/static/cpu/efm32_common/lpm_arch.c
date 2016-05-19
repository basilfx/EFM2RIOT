/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32_common
 * @{
 *
 * @file
 * @brief       Implementation of the kernels power management interface
 *
 * @author      Hauke Petersen <hauke.peterse@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "arch/lpm_arch.h"

#include "em_emu.h"

void lpm_arch_init(void)
{
    EMU_EM23Init_TypeDef init_em23 = EMU_EM23INIT_DEFAULT;
    EMU_EM4Init_TypeDef init_em4 = EMU_EM4INIT_DEFAULT;

    EMU_EM23Init(&init_em23);
    EMU_EM4Init(&init_em4);
}

enum lpm_mode lpm_arch_set(enum lpm_mode target)
{
    switch (target) {
        case LPM_ON:
            /* nothing to do */
            break;
        case LPM_IDLE:
            /* wait for next event or interrupt */
            EMU_EnterEM1();
            break;
        case LPM_SLEEP:
            /* after exiting EM2, clocks are restored */
            EMU_EnterEM2(true);
            break;
        case LPM_POWERDOWN:
            /* after exiting EM3, clocks are restored */
            EMU_EnterEM3(true);
            break;
        case LPM_OFF:
            /* only a reset can wake up from EM4 */
            EMU_EnterEM4();
            break;

        /* do nothing here */
        case LPM_UNKNOWN:
        default:
            break;
    }

    /* no matter which case was selected, instructions executed in EM0 only */
    return LPM_ON;
}

enum lpm_mode lpm_arch_get(void)
{
    /* instructions are executed in EM0 only */
    return LPM_ON;
}

void lpm_arch_awake(void)
{
    return;
}

void lpm_arch_begin_awake(void)
{
    return;
}

void lpm_arch_end_awake(void)
{
    return;
}
