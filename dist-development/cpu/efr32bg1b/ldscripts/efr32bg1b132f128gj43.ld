/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_efr32bg1b
 * @{
 *
 * @file
 * @brief           Memory definitions for the EFR32BG1B132F128GJ43 CPU
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author          Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

MEMORY
{
    rom (rx)    : ORIGIN = 0x00000000, LENGTH = 131072
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 31744
}

INCLUDE cortexm_base.ld
