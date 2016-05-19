/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Periodic wakeup for measuring temperature via Si7021. The RTT
 *              is used to wakeup the MCU from EM2 (sleep mode).
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "lpm.h"
#include "xtimer.h"

#include "si70xx.h"

#include "periph/rtt.h"
#include "periph/gpio.h"

/**
 * @brief   Wakeup interval (in seconds).
 */
#define INTERVAL (60U)

int main(void)
{
    si70xx_t dev;
    uint32_t timeout;
    int16_t temperature;
    uint16_t humidity;

    /* prepare timer */
    rtt_init();

    /* prepare sensor (the enable pin is not toggled during sleep) */
    gpio_init(SI7021_EN_PIN, GPIO_OUT);
    gpio_set(SI7021_EN_PIN);

    si70xx_init(&dev, SI7021_I2C, SI70XX_ADDRESS_SI7021);

    while (1) {
        /* prepare sleep between measurements */
        timeout = rtt_get_counter() + (INTERVAL * RTT_FREQUENCY);
        rtt_set_alarm(timeout, NULL, 0);

        /* measure temperature */
        si70xx_get_both(&dev, &humidity, &temperature);

        /* display results */
        printf("relative humidity: %d.%02d\n", humidity / 100, humidity % 100);
        printf("temperature: %d.%02d C\n", temperature / 100, temperature % 100);
        fflush(stdout);

        /* go to sleep */
        lpm_arch_set(LPM_SLEEP);

        /* it needs some time to stabilize after sleep */
        xtimer_usleep(1000);
    }

    return 0;
}
