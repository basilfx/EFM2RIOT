/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_{{ family }}
 * @{
 *
 * @file
 * @brief           Memory definitions for the {{ cpu|upper }} CPU
 *
 * @author          Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author          Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

MEMORY
{
    rom (rx)    : ORIGIN = {{ flash_base|hex(8) }}, LENGTH = {{ flash_size }}
    ram (rwx)   : ORIGIN = {{ sram_base|hex(8) }}, LENGTH = {{ sram_size }}
}

INCLUDE cortexm_base.ld
