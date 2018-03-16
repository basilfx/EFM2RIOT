/*
 * Copyright (C) 2015-2018 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_{{ board }} Silicon Labs {{ board|upper }} starter kit
 * @ingroup     boards
 * @brief       Support for the Silicon Labs {{ board|upper }} starter kit
 * @{
 *
 * @file
 * @brief       Board specific definitions for the {{ board|upper }} starter kit
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Xtimer configuration
 *
 * The timer runs at 250 KHz to increase accuracy.
 * @{
 */
#define XTIMER_HZ           (250000UL)
#define XTIMER_WIDTH        (16)
/** @} */

{% strip 2, ">" %}
    {% if "bc" in features %}
        /**
         * @name    Board controller configuration
         *
         * Define the GPIO pin to enable the BC, to allow serial communication
         * via the USB port.
         * @{
         */
        {% strip 2 %}
            {% if board in ["brd4162a"] %}
                #define BC_PIN              GPIO_PIN(PA, 5)
            {% elif board in ["slstk3401a", "slstk3402a"] %}
                #define BC_PIN              GPIO_PIN(PA, 5)
            {% elif board in ["slstk3701a"] %}
                #define BC_PIN              GPIO_PIN(PE, 1)
            {% elif board in ["slwstk6220a"] %}
                #define BC_PIN              GPIO_PIN(PA, 12)
            {% elif board in ["stk3200"] %}
                #define BC_PIN              GPIO_PIN(PA, 9)
            {% elif board in ["stk3600", "stk3700", "stk3800"] %}
                #define BC_PIN              GPIO_PIN(PF, 7)
            {% endif %}
        {% endstrip %}
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @name    Push button pin definitions
 * @{
 */
{% strip 2 %}
    {% if board in ["brd4162a"] %}
        #define PB0_PIN             GPIO_PIN(PF, 6)
        #define PB1_PIN             GPIO_PIN(PF, 6)
    {% elif board in ["sltb001a"] %}
        #define PB0_PIN             GPIO_PIN(PD, 14)
        #define PB1_PIN             GPIO_PIN(PD, 15)
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define PB0_PIN             GPIO_PIN(PF, 6)
        #define PB1_PIN             GPIO_PIN(PF, 7)
    {% elif board in ["slstk3701a"] %}
        #define PB0_PIN             GPIO_PIN(PC, 8)
        #define PB1_PIN             GPIO_PIN(PC, 9)
    {% elif board in ["slwstk6220a"] %}
        #define PB0_PIN             GPIO_PIN(PE, 3)
        #define PB1_PIN             GPIO_PIN(PE, 2)
    {% elif board in ["stk3200"] %}
        #define PB0_PIN             GPIO_PIN(PC, 8)
        #define PB1_PIN             GPIO_PIN(PC, 9)
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        #define PB0_PIN             GPIO_PIN(PB, 9)
        #define PB1_PIN             GPIO_PIN(PB, 10)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    LED pin definitions
 * @{
 */
{% strip 2 %}
    {% if board in ["brd4162a"] %}
        #define LED0_PIN            GPIO_PIN(PF, 4)
        #define LED1_PIN            GPIO_PIN(PF, 5)
    {% elif board in ["sltb001a"] %}
        #define LED0_PIN            GPIO_PIN(PD, 12)
        #define LED1_PIN            GPIO_PIN(PD, 11)
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define LED0_PIN            GPIO_PIN(PF, 4)
        #define LED1_PIN            GPIO_PIN(PF, 5)
    {% elif board in ["slstk3701a"] %}
        #define LED0R_PIN           GPIO_PIN(PH, 10)
        #define LED0G_PIN           GPIO_PIN(PH, 11)
        #define LED0B_PIN           GPIO_PIN(PH, 12)
        #define LED1R_PIN           GPIO_PIN(PH, 13)
        #define LED1G_PIN           GPIO_PIN(PH, 14)
        #define LED1B_PIN           GPIO_PIN(PH, 15)

        #define LED0_PIN            LED0R_PIN
        #define LED1_PIN            LED1R_PIN
    {% elif board in ["slwstk6220a"] %}
        #define LED0_PIN            GPIO_PIN(PF, 6)
        #define LED1_PIN            GPIO_PIN(PF, 7)
    {% elif board in ["stk3200"] %}
        #define LED0_PIN            GPIO_PIN(PC, 10)
        #define LED1_PIN            GPIO_PIN(PC, 11)
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        #define LED0_PIN            GPIO_PIN(PE, 2)
        #define LED1_PIN            GPIO_PIN(PE, 3)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    Macros for controlling the on-board LEDs
 * @{
 */
#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)
#define LED1_ON             gpio_set(LED1_PIN)
#define LED1_OFF            gpio_clear(LED1_PIN)
#define LED1_TOGGLE         gpio_toggle(LED1_PIN)
/** @} */

{% strip 2, ">" %}
    {% if board in ["slstk3401a", "slstk3402a"] %}
        /**
         * @name    Display configuration
         *
         * Connection to the on-board Sharp Memory LCD (LS013B7DH03).
         * @{
         */
        #define DISP_SPI            SPI_DEV(0)
        #define DISP_COM_PIN        GPIO_PIN(PD, 13)
        #define DISP_CS_PIN         GPIO_PIN(PD, 14)
        #define DISP_EN_PIN         GPIO_PIN(PD, 15)
        /** @} */
    {% elif board in ["slstk3701a"] %}
        /**
         * @name    Display configuration
         *
         * Connection to the on-board Sharp Memory LCD (LS013B7DH03).
         * @{
         */
        #define DISP_SPI            SPI_DEV(0)
        #define DISP_COM_PIN        GPIO_PIN(PA, 11)
        #define DISP_CS_PIN         GPIO_PIN(PC, 14)
        #define DISP_EN_PIN         GPIO_PIN(PA, 9)
        /** @} */
    {% elif board in ["slwstk6220a"] %}
        /**
         * @name    Display configuration
         *
         * Connection to the on-board Sharp Memory LCD (LS013B7DH03).
         * @{
         */
        #define DISP_SPI            SPI_DEV(0)
        #define DISP_COM_PIN        GPIO_PIN(PE, 10)
        #define DISP_CS_PIN         GPIO_PIN(PE, 11)
        #define DISP_SELECT_PIN     GPIO_PIN(PA, 8)
        #define DISP_POWER_PIN      GPIO_PIN(PA, 10)
        /** @} */
    {% elif board in ["stk3200"] %}
        /**
         * @name    Display configuration
         *
         * Connection to the on-board Sharp Memory LCD (LS013B7DH03).
         * @{
         */
        #define DISP_SPI            SPI_DEV(0)
        #define DISP_COM_PIN        GPIO_PIN(PE, 10)
        #define DISP_CS_PIN         GPIO_PIN(PE, 11)
        #define DISP_SELECT_PIN     GPIO_PIN(PA, 8)
        #define DISP_POWER_PIN      GPIO_PIN(PA, 10)
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["slstk3401a"] %}
        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #define SI7021_I2C              I2C_DEV(0)
        #define SI7021_EN_PIN           GPIO_PIN(PD, 9)

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */
    {% elif board in ["slstk3402a"] %}
        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #ifndef SI7021_ENABLED
        #define SI7021_ENABLED          (1)
        #endif
        #define SI7021_I2C              I2C_DEV(0)
        #define SI7021_EN_PIN           GPIO_PIN(PB, 10)

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */
    {% elif board in ["slstk3701a"] %}
        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #ifndef SI7021_ENABLED
        #define SI7021_ENABLED          (1)
        #endif
        #define SI7021_I2C              I2C_DEV(2)
        #define SI7021_EN_PIN           GPIO_PIN(PB, 3)

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */
    {% elif board in ["sltb001a"] %}
        /**
         * @name    Environmental sensors configuration
         *
         * Pin for enabling environmental sensors (BMP280, Si1133, Si7021, Si7210A).
         * @{
         */
        #define ENV_SENSE_PIC_ADDR  (0x01)
        #define ENV_SENSE_PIC_BIT   (0)
        /** @} */

        /**
         * @name    Pressure sensor configuration
         *
         * Connection to the on-board pressure sensor (BMP280).
         * @{
         */
        #define BMP280_I2C              I2C_DEV(0)

        #define BMX280_PARAM_I2C_DEV    BMP280_I2C
        /** @} */

        /**
         * @name    Air quality/gas sensor configuration
         *
         * Connection to the on-board air quality/gas sensor (CCS811).
         * @{
         */
        #ifndef CCS811_ENABLED
        #define CCS811_ENABLED      (0)
        #endif
        #define CCS811_I2C          I2C_DEV(0)
        #define CCS811_PIC_ADDR     (0x03)
        #define CCS811_PIC_EN_BIT   (0x00)
        #define CCS811_PIC_WAKE_BIT (0x01)
        /** @} */

        /**
         * @name    IMU sensor configuration
         *
         * Connection to the on-board IMU sensor (ICM-20648).
         * @{
         */
        #ifndef ICM20648_ENABLED
        #define ICM20648_ENABLED    (0)
        #endif
        #define ICM20648_SPI        SPI_DEV(0)
        #define ICM20648_PIC_ADDR   (0x00)
        #define ICM20648_PIC_EN_BIT (0x00)
        /** @} */

        /**
         * @name    Power and Interrupt controller
         *
         * Pin for communication with the Power and Interrupt Controller.
         * @{
         */
        #define PIC_INT_WAKE_PIN    GPIO_PIN(PD, 10)
        #define PIC_I2C             I2C_DEV(0)
        #define PIC_I2C_ADDR        (0x48)
        /** @} */

        /**
         * @name    RGB leds configuration
         *
         * There are four RGB leds on the board.
         * @{
         */
        #ifndef RGB_LED1_ENABLED
        #define RGB_LED1_ENABLED    (1)
        #endif
        #ifndef RGB_LED2_ENABLED
        #define RGB_LED2_ENABLED    (1)
        #endif
        #ifndef RGB_LED3_ENABLED
        #define RGB_LED3_ENABLED    (1)
        #endif
        #ifndef RGB_LED4_ENABLED
        #define RGB_LED4_ENABLED    (1)
        #endif
        #define RGB_LED_ADDR        (0x04)
        #define RGB_LED_EN_BIT      (0x00)
        #define RGB_LED1_EN_BIT     (0x07)
        #define RGB_LED2_EN_BIT     (0x06)
        #define RGB_LED3_EN_BIT     (0x05)
        #define RGB_LED4_EN_BIT     (0x04)
        /** @} */

        /**
         * @name    UV/Ambient sensor configuration
         *
         * Connection to the on-board UV/ambient light sensor (Si1133).
         * @{
         */
        #ifndef SI1133_ENABLED
        #define SI1133_ENABLED      (0)
        #endif
        #define SI1133_I2C          I2C_DEV(0)
        /** @} */

        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #define SI7021_I2C              I2C_DEV(0)

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */

        /**
         * @name    Hall-effect sensor configuration
         *
         * Connection to the on-board hall-effect sensor (Si7210A). Available on Rev. A02
         * boards only.
         * @{
         */
        #ifndef SI7210A_ENABLED
        #define SI7210A_ENABLED     (0)
        #endif
        #define SI7210A_I2C         I2C_DEV(0)
        /** @} */
    {% elif board in ["slwstk6220a"] %}
        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #define SI7021_I2C              I2C_DEV(0)
        #define SI7021_EN_PIN           GPIO_PIN(PF, 8)

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @brief   Initialize the board (GPIO, sensors, clocks).
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
