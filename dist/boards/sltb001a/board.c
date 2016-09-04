/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_sltb001a
 * @{
 *
 * @file
 * @brief       Board specific implementations SLTB001A board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "board.h"
#include "cpu.h"

#include "periph/gpio.h"

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* initialize the LEDs */
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(LED1_PIN, GPIO_OUT);

    /* initialize the push buttons */
    gpio_init(PB0_PIN, GPIO_IN);
    gpio_init(PB1_PIN, GPIO_IN);

    /* initialize the CCS811 sensor */
#if CCS811_ENABLED
    gpio_init(CCS811_EN_PIN, GPIO_OUT);
    gpio_set(CCS811_EN_PIN);
#endif

    /* initialize the ICM-20648 sensor */
#if ICM_20648_ENABLED
    gpio_init(CCS811_EN_PIN, GPIO_OUT);
    gpio_set(CCS811_EN_PIN);
#endif

    /* initialize the environmental sensors (multiple ones) */
#if BMP280_ENABLED || SI1133_ENABLED || SI7021_ENABLED || SI7210A_ENABLED
    gpio_init(ENV_SENSE_EN_PIN, GPIO_OUT);
    gpio_set(ENV_SENSE_EN_PIN);
#endif
}