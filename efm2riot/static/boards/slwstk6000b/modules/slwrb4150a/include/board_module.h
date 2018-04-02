/*
 * Copyright (C) 2018 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_slwstk6000b
 * @{
 *
 * @file
 * @brief       Specific definitions for SLWRB4150A module.
 *
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef BOARD_MODULE_H
#define BOARD_MODULE_H

#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Pins on the SLWRB4150A module.
 * @{
 */
#define F0      GPIO_PIN(PF, 1)
#define F1      GPIO_PIN(PF, 0)
#define F2      GPIO_PIN(PF, 2)
#define F3      GPIO_PIN(PF, 3)
#define F4      GPIO_UNDEF
#define F5      GPIO_PIN(PA, 5)
#define F6      GPIO_PIN(PA, 0)
#define F7      GPIO_PIN(PA, 1)
#define F8      GPIO_PIN(PA, 2)
#define F9      GPIO_PIN(PA, 3)
#define F10     GPIO_PIN(PF, 4)
#define F11     GPIO_PIN(PF, 5)
#define F12     GPIO_PIN(PF, 6)
#define F13     GPIO_PIN(PF, 7)
#define F14     GPIO_PIN(PD, 15)
#define F15     GPIO_PIN(PC, 8)
#define F16     GPIO_PIN(PC, 6)
#define F17     GPIO_PIN(PD, 15)
#define F18     GPIO_PIN(PD, 13)
#define F19     GPIO_PIN(PB, 13)
#define F20     GPIO_PIN(PB, 12)
#define F21     GPIO_PIN(PB, 11)
#define P0      GPIO_PIN(PA, 2)
#define P1      GPIO_PIN(PC, 6)
#define P2      GPIO_PIN(PA, 3)
#define P3      GPIO_PIN(PC, 7)
#define P4      GPIO_PIN(PF, 6)
#define P5      GPIO_PIN(PC, 8)
#define P6      GPIO_PIN(PF, 7)
#define P7      GPIO_PIN(PC, 9)
#define P8      GPIO_PIN(PF, 4)
#define P9      GPIO_PIN(PA, 0)
#define P10     GPIO_PIN(PF, 3)
#define P11     GPIO_PIN(PA, 1)
#define P12     GPIO_PIN(PC, 10)
#define P13     GPIO_PIN(PC, 11)
#define P14     GPIO_PIN(PA, 4)
#define P15     GPIO_UNDEF
#define P16     GPIO_PIN(PA, 5)
#define P17     GPIO_UNDEF
#define P18     GPIO_PIN(PB, 11)
#define P19     GPIO_UNDEF
#define P20     GPIO_PIN(PB, 12)
#define P21     GPIO_UNDEF
#define P22     GPIO_PIN(PB, 13)
#define P23     GPIO_UNDEF
#define P24     GPIO_PIN(PF, 0)
#define P25     GPIO_UNDEF
#define P26     GPIO_PIN(PF, 1)
#define P27     GPIO_UNDEF
#define P28     GPIO_PIN(PF, 2)
#define P29     GPIO_UNDEF
#define P30     GPIO_UNDEF
#define P31     GPIO_PIN(PD, 13)
#define P32     GPIO_PIN(PF, 5)
#define P33     GPIO_PIN(PD, 14)
#define P34     GPIO_UNDEF
#define P35     GPIO_PIN(PD, 15)
#define P36     GPIO_UNDEF
#define P37     GPIO_PIN(PD, 15)
#define P38     GPIO_UNDEF
#define P39     GPIO_UNDEF
#define P40     GPIO_UNDEF
#define P41     GPIO_UNDEF
#define P42     GPIO_UNDEF
#define P43     GPIO_UNDEF
#define P44     GPIO_UNDEF
#define P45     GPIO_UNDEF
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* BOARD_MODULE_H */
/** @} */
