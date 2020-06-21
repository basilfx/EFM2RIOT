/*
 * Copyright (C) 2015-2020 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_{{ board }}
 * @{
 *
 * @file
 * @brief       Board specific implementations {{ board|upper }} board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "board.h"
#include "board_common.h"
{% strip 2 %}
    {% if board in ["slstk3301a", "slstk3401a", "slstk3402a", "sltb001a", "slwstk6000b", "slwstk6220a"]  %}
        #include "periph/gpio.h"
    {% endif %}
{% endstrip %}

{% strip 2, "<" %}
    {% if board in ["sltb001a"]  %}
        #ifdef MODULE_SILABS_PIC
        #include "pic.h"
        #endif
    {% endif %}
{% endstrip %}

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

#ifndef RIOTBOOT
    /* perform common board initialization */
    board_common_init();

    {% strip 3, "<" %}
        {% if board in ["slstk3301a", "slstk3401a", "slstk3402a", "slwstk6000b", "slwstk6220a"] %}
            #ifdef MODULE_SI7021
                /* initialize the Si7021 sensor */
                gpio_init(SI7021_EN_PIN, GPIO_OUT);
                gpio_set(SI7021_EN_PIN);
            #endif
        {% endif %}
    {% endstrip %}

    {% strip 3, "<" %}
        {% if board in ["sltb001a"] %}
            #ifdef MODULE_SILABS_PIC
            #if CCS811_ENABLED
                /* enable the CCS811 air quality/gas sensor */
                pic_write(CCS811_PIC_ADDR, (1 << CCS811_PIC_EN_BIT) | (1 << CCS811_PIC_WAKE_BIT));
            #endif

            #if ICM_20648_ENABLED
                /* enable the IMU sensor */
                pic_write(ICM20648_PIC_ADDR, 1 << ICM20648_PIC_EN_BIT);
            #endif

            #if defined(MODULE_BMP280) || defined(MODULE_SI7021) || SI1133_ENABLED || SI7210_ENABLED
                /* enable the environmental sensors */
                pic_write(ENV_SENSE_PIC_ADDR, 1 << ENV_SENSE_PIC_BIT);
            #endif

            #if RGB_LED1_ENABLED || RGB_LED2_ENABLED || RGB_LED3_ENABLED || RGB_LED4_ENABLED
                /* enable the RGB leds */
                pic_write(RGB_LED_ADDR,
                          (1 << RGB_LED_EN_BIT) |
                          (RGB_LED1_ENABLED << RGB_LED1_EN_BIT) |
                          (RGB_LED2_ENABLED << RGB_LED2_EN_BIT) |
                          (RGB_LED3_ENABLED << RGB_LED3_EN_BIT) |
                          (RGB_LED4_ENABLED << RGB_LED4_EN_BIT));
            #endif
            #endif
        {% endif %}
    {% endstrip %}
#endif
}
