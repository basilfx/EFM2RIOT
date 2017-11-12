/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_efm32pg12b
 * @{
 *
 * @file
 * @brief           Memory definitions for the EFM32PG12B500F1024IL125 CPU
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author          Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

MEMORY
{
    rom (rx)    : ORIGIN = 0x00000000, LENGTH = 1048576
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 262144
}

INCLUDE cortexm_base.ld
