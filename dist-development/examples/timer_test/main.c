/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Timer test application for EFM32 boards
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"

#include "periph/gpio.h"
#include "periph/timer.h"

#include "xtimer.h"

int main(void)
{
    gpio_t pin = GPIO_PIN(PC, 11);
    
    gpio_init(pin, GPIO_OUT);
    
    while (1) {
        gpio_set(pin);
        xtimer_usleep(10);
        gpio_clear(pin);
        xtimer_usleep(10);
    }

    return 0;
}
