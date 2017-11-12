/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_efr32fg13p
 * @{
 *
 * @file
 * @brief           Memory definitions for the EFR32FG13P232F512GM32 CPU
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author          Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

MEMORY
{
    rom (rx)    : ORIGIN = 0x00000000, LENGTH = 524288
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 65536
}

INCLUDE cortexm_base.ld
