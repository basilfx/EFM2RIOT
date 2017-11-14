/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_efm32
 * @{
 *
 * @file
 * @brief           Memory definitions for EFM32/EFR32/EZR32 CPUs
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author          Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

MEMORY
{
    rom (rx)    : ORIGIN = _rom_start_addr, LENGTH = _rom_length
    ram (rwx)   : ORIGIN = _ram_start_addr, LENGTH = _ram_length
}

INCLUDE cortexm_base.ld
