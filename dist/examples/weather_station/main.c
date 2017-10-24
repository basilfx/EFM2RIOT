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
 * @brief       Sensor values displayed on the low-power memory LCD. The RTT
 *              is used to wakeup the MCU from EM2 (sleep mode).
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "xtimer.h"

#include "u8g2.h"
#include "si70xx.h"

#include "periph/gpio.h"
#include "periph/adc.h"

#include "images.h"

/**
 * @brief   Wakeup interval (in seconds).
 */
#define INTERVAL (30U)

/**
 * @brief   RIOT-OS pin maping of U8g2 pin numbers to RIOT-OS GPIO pins.
 */
static gpio_t pins[] = {
    [U8X8_PIN_CS] = DISP_CS_PIN,
};

/**
 * @brief   Bit mapping to indicate which pins are set.
 */
static uint32_t pins_enabled = (
    (1 << U8X8_PIN_CS)
);

static float get_battery_voltage(void)
{
    int32_t value = adc_sample(1, ADC_RES_12BIT);

    return (((float) value) / 4096.0) * 5.0;
}

static float get_internal_temp(void)
{
    float cal_temp = (float) ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    float cal_value = (float) ((DEVINFO->ADC0CAL3 & _DEVINFO_ADC0CAL3_TEMPREAD1V25_MASK) >> _DEVINFO_ADC0CAL3_TEMPREAD1V25_SHIFT);

    /* convert temperature channel */
    int32_t value = adc_sample(0, ADC_RES_12BIT);

    return cal_temp - ((cal_value - value) / -6.01);
}

int main(void)
{
    char buffer[5][16];

    u8g2_t u8g2;
    si70xx_t dev;
    uint32_t timeout;
    int16_t temperature;
    uint16_t humidity;

    /* prepare display */
    gpio_init(DISP_COM_PIN, GPIO_OUT);
    gpio_init(DISP_EN_PIN, GPIO_OUT);

    gpio_set(DISP_COM_PIN);
    gpio_set(DISP_EN_PIN);

    u8g2_Setup_ls013b7dh03_128x128_1(&u8g2, U8G2_R0, u8x8_byte_riotos_hw_spi, u8x8_gpio_and_delay_riotos);

    u8x8_SetPins(u8g2_GetU8x8(&u8g2), pins, pins_enabled);
    u8x8_SetDevice(u8g2_GetU8x8(&u8g2), DISP_SPI);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    /* prepare sensor (the enable pin is not toggled during sleep) */
    gpio_init(SI7021_EN_PIN, GPIO_OUT);
    gpio_set(SI7021_EN_PIN);

    si70xx_init(&dev, SI7021_I2C, SI70XX_ADDRESS_SI7021);

    while (1) {
        /* measure temperature via Si7021 */
        si70xx_get_both(&dev, &humidity, &temperature);

        /* wakeup/init adc */
        adc_init(0);
        adc_init(1);

        /* display results */
        snprintf(buffer[0], 16, "%d.%02d %%", humidity / 100, humidity % 100);
        snprintf(buffer[1], 16, "%d.%02d C", temperature / 100, temperature % 100);
        snprintf(buffer[2], 16, "%.2f C", get_internal_temp());
        snprintf(buffer[3], 16, "%.2f V", get_battery_voltage());
        snprintf(buffer[4], 16, "%lu s", xtimer_now() / 1000);

        u8g2_FirstPage(&u8g2);

        do {
            u8g2_SetDrawColor(&u8g2, 1);
            u8g2_SetFont(&u8g2, u8g2_font_helvB12_tf);

            /* humidity */
            u8g2_DrawBitmap(&u8g2, 2, 20 - 16 + 2, 2, 16, image_rh);
            u8g2_DrawStr(&u8g2, 25, 20, buffer[0]);

            /* temperature */
            u8g2_DrawBitmap(&u8g2, 2, 40 - 16 + 2, 2, 16, image_temperature);
            u8g2_DrawStr(&u8g2, 25, 40, buffer[1]);

            /* internal temperature */
            u8g2_DrawBitmap(&u8g2, 2, 60 - 16 + 2, 2, 16, image_temperature);
            u8g2_DrawStr(&u8g2, 25, 60, buffer[2]);

            /* battery voltage */
            u8g2_DrawBitmap(&u8g2, 2, 80 - 16 + 2, 2, 16, image_battery);
            u8g2_DrawStr(&u8g2, 25, 80, buffer[3]);

            /* time */
            u8g2_DrawBitmap(&u8g2, 2, 100 - 16 + 2, 2, 16, image_clock);
            u8g2_DrawStr(&u8g2, 25, 100, buffer[4]);
        } while (u8g2_NextPage(&u8g2));

        /* go to sleep */
        xtimer_sleep(INTERVAL);
    }

    return 0;
}
