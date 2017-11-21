/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
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
 * @brief       Board specific implementations {{ board_display_name }} board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "board.h"
#include "cpu.h"

#include "periph/gpio.h"
{% strip 2, ">" %}
    {% if board in ["sltb001a"] %}
        #include "periph/i2c.h"
    {% endif %}
{% endstrip %}

{% strip 3, ">" %}
    {% if board not in ["sltb001a"] %}
        {% if architecture not in ["m0", "m0plus"] %}
            #include "em_dbg.h"
            #include "em_gpio.h"
        {% endif %}
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["sltb001a"] %}
        #if BMP280_ENABLED || CCS811_ENABLED || ICM_20648_ENABLED || \
            SI1133_ENABLED || SI7021_ENABLED || SI7210A_ENABLED || \
            RGB_LED1_ENABLED || RGB_LED2_ENABLED || RGB_LED3_ENABLED || \
            RGB_LED4_ENABLED
        static inline void board_usleep(uint32_t delay)
        {
            /* decrement + compare take two cycles, therefore divide by two */
            uint32_t count = (delay * (SystemCoreClock / 1000 / 1000)) / 2;

            while (count--) {}
        }

        static void board_pic_init(void)
        {
            gpio_init(PIC_INT_WAKE_PIN, GPIO_OD);
            gpio_set(PIC_INT_WAKE_PIN);

            i2c_init_master(PIC_I2C, I2C_SPEED_NORMAL);
        }

        static void board_pic_write(uint8_t addr, uint8_t value)
        {
            /* toggle the pin for 4 us */
            gpio_clear(PIC_INT_WAKE_PIN);
            board_usleep(4);

            /* write to gpio expander */
            i2c_acquire(PIC_I2C);
            uint8_t bytes[] = { addr, value };
            i2c_write_bytes(PIC_I2C, PIC_I2C_ADDR, bytes, 2);
            i2c_release(PIC_I2C);

            /* put PIC in sleep mode again */
            gpio_set(PIC_INT_WAKE_PIN);
        }
        #endif
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3600", "stk3700", "stk3800"] %}
        static void aem_init(void)
        {
            if (DBG_Connected()) {
                /* enable GPIO clock for configuring SWO pins */
                CMU_ClockEnable(cmuClock_HFPER, true);
                CMU_ClockEnable(cmuClock_GPIO, true);

                /* enable debug peripheral via SWO */
                {% strip 2 %}
                    {% if cpu_series == 0 %}
                        DBG_SWOEnable(GPIO_ROUTE_SWLOCATION_LOC0);
                    {% else %}
                        DBG_SWOEnable(GPIO_ROUTELOC0_SWVLOC_LOC0);
                    {% endif %}
                {% endstrip %}

                /* enable trace in core debug */
                CoreDebug->DHCSR |= CoreDebug_DHCSR_C_DEBUGEN_Msk;
                CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

                /* enable PC and IRQ sampling output */
                DWT->CTRL = 0x400113FF;

                /* set TPIU prescaler to 16 */
                TPI->ACPR = 15;

                /* set protocol to NRZ */
                TPI->SPPR = 2;

                /* disable continuous formatting */
                TPI->FFCR = 0x100;

                /* unlock ITM and output data */
                ITM->LAR = 0xC5ACCE55;
                ITM->TCR = 0x10009;
            }
        }
    {% endif %}
{% endstrip %}

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    {% strip 3, ">" %}
        {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3600", "stk3700", "stk3800"] %}
                /* enable core debug output AEM */
            #if AEM_ENABLED
                aem_init();
            #endif
        {% endif %}
    {% endstrip %}

    {% strip 3, ">" %}
        {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a", "stk3200", "stk3600", "stk3700", "stk3800"] %}
                /* enable the board controller, to enable virtual com port */
            #if BC_ENABLED
                gpio_init(BC_PIN, GPIO_OUT);
                gpio_set(BC_PIN);
            #endif
        {% endif %}
    {% endstrip %}

    /* initialize the LEDs */
    gpio_init(LED0_PIN, GPIO_OUT);
    gpio_init(LED1_PIN, GPIO_OUT);

    /* initialize the push buttons */
    gpio_init(PB0_PIN, GPIO_IN);
    gpio_init(PB1_PIN, GPIO_IN);

    {% strip 3, "<" %}
        {% if board in ["slstk3401a", "slstk3402a", "slwstk6220a"] %}
                /* initialize the Si7021 sensor */
            #if SI7021_ENABLED
                gpio_init(SI7021_EN_PIN, GPIO_OUT);
                gpio_set(SI7021_EN_PIN);
            #endif
        {% endif %}
    {% endstrip %}

    {% strip 3, "<" %}
        {% if board in ["sltb001a"] %}
                /* initialize the environmental sensors (multiple ones) */
            #if BMP280_ENABLED || CCS811_ENABLED || ICM_20648_ENABLED || \
                SI1133_ENABLED || SI7021_ENABLED || SI7210A_ENABLED || \
                RGB_LED1_ENABLED || RGB_LED2_ENABLED || RGB_LED3_ENABLED || \
                RGB_LED4_ENABLED
                board_pic_init();
            #endif

                /* enable the CCS811 air quality/gas sensor */
            #if CCS811_ENABLED
                board_pic_write(CCS811_PIC_ADDR, (1 << CCS811_PIC_EN_BIT) | (1 << CCS811_PIC_WAKE_BIT));
            #endif

                /* enable the IMU sensor */
            #if ICM_20648_ENABLED
                board_pic_write(ICM20648_PIC_ADDR, 1 << ICM20648_PIC_EN_BIT);
            #endif

                /* enable the environmental sensors */
            #if BMP280_ENABLED || SI1133_ENABLED || SI7021_ENABLED || SI7210A_ENABLED
                board_pic_write(ENV_SENSE_PIC_ADDR, 1 << ENV_SENSE_PIC_BIT);
            #endif

                /* enable the RGB leds */
            #if RGB_LED1_ENABLED || RGB_LED2_ENABLED || RGB_LED3_ENABLED || RGB_LED4_ENABLED
                board_pic_write(RGB_LED_ADDR,
                    (1 << RGB_LED_EN_BIT) |
                    (RGB_LED1_ENABLED << RGB_LED1_EN_BIT) |
                    (RGB_LED2_ENABLED << RGB_LED2_EN_BIT) |
                    (RGB_LED3_ENABLED << RGB_LED3_EN_BIT) |
                    (RGB_LED4_ENABLED << RGB_LED4_EN_BIT));
            #endif
        {% endif %}
    {% endstrip %}
}
