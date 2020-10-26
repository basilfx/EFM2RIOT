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
 * @brief       Board specific definitions for the {{ board|upper }} starter kit
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
{% strip 2, "", 2 %}
  {% if board in ["slstk3400a"] %}
     * @author      Akshai M <mail@akshaim.in>
  {% endif %}
  {% if board in ["slwstk6000b"] %}
     * @author      Kai Beckmann <kai.beckmann@hs-rm.de>
  {% endif %}
{% endstrip %}
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

{% strip 2 %}
    {% if "letimer" in mappings.xtimer %}
        /**
         * @name    Xtimer configuration
         *
         * The timer runs at {{ mappings.xtimer.default.frequency|freq }} to increase accuracy, or at {{ mappings.xtimer.letimer.frequency|freq }} if
         * LETIMER is used.
         * @{
         */
        #if IS_ACTIVE(CONFIG_EFM32_XTIMER_USE_LETIMER)
        #define XTIMER_DEV          (TIMER_DEV({{ mappings.xtimer.letimer.device }}))
        #define XTIMER_HZ           ({{ mappings.xtimer.letimer.frequency }}UL)
        #define XTIMER_WIDTH        ({{ mappings.xtimer.letimer.width }})
        #else
        #define XTIMER_DEV          (TIMER_DEV({{ mappings.xtimer.default.device }}))
        #define XTIMER_HZ           ({{ mappings.xtimer.default.frequency }}UL)
        #define XTIMER_WIDTH        ({{ mappings.xtimer.default.width }})
        #endif
        #define XTIMER_CHAN         (0)
        /** @} */
    {% else %}
        /**
         * @name    Xtimer configuration
         *
         * The timer runs at {{ mappings.xtimer.default.frequency|freq }}.
         * @{
         */
        #define XTIMER_DEV          (TIMER_DEV({{ mappings.xtimer.default.device }}))
        #define XTIMER_HZ           ({{ mappings.xtimer.default.frequency }}UL)
        #define XTIMER_WIDTH        ({{ mappings.xtimer.default.width }})
        #define XTIMER_CHAN         (0)
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if "bc" in mappings %}
        /**
         * @name    Board controller configuration
         *
         * Define the GPIO pin to enable the BC, to allow serial communication
         * via the USB port.
         * @{
         */
        #define BC_PIN              {{ mappings.bc.pin|riot }}
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @name    Push button pin definitions
 * @{
 */
{% strip 2 %}
    {% for button in mappings.buttons %}
        #define {{ button.name|align(19) }} {{ button.pin|riot }}
    {% endfor %}
{% endstrip %}
/** @} */

/**
 * @name    LED pin definitions
 * @{
 */
{% strip 2 %}
    {% for led in mappings.leds %}
        #define {{ led.name|align(19) }} {{ led.pin|riot }}
    {% endfor %}
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
    {% if "ls013b7dh03" in mappings %}
        /**
         * @name    Display configuration
         *
         * Connection to the on-board Sharp Memory LCD (LS013B7DH03).
         * @{
         */
        #define DISP_SPI            SPI_DEV({{ mappings.ls013b7dh03.spi }})
        #define DISP_COM_PIN        {{ mappings.ls013b7dh03.com_pin|riot }}
        #define DISP_CS_PIN         {{ mappings.ls013b7dh03.cs_pin|riot }}
        {% strip 2 %}
            {% if "en_pin" in mappings.ls013b7dh03 %}
                #define DISP_EN_PIN         {{ mappings.ls013b7dh03.en_pin|riot }}
            {% endif %}
            {% if "select_pin" in mappings.ls013b7dh03 %}
                #define DISP_SELECT_PIN     {{ mappings.ls013b7dh03.select_pin|riot }}
            {% endif %}
            {% if "power_pin" in mappings.ls013b7dh03 %}
                #define DISP_POWER_PIN      {{ mappings.ls013b7dh03.power_pin|riot }}
            {% endif %}
        {% endstrip %}
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if "si7021" in mappings %}
        /**
         * @name    Temperature sensor configuration
         *
         * Connection to the on-board temperature/humidity sensor (Si7021).
         * @{
         */
        #define SI7021_I2C              I2C_DEV({{ mappings.si7021.i2c }})
        #define SI7021_EN_PIN           {{ mappings.si7021.en_pin|riot }}

        #define SI70XX_PARAM_I2C_DEV    SI7021_I2C
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["slstk3301a"] %}
        /**
         * @name    Hall-effect sensor configuration
         *
         * Connection to the on-board hall-effect sensor (Si7210    ).
         * @{
         */
        #define SI7210_I2C              I2C_DEV(0)
        #define SI7210_EN_PIN           GPIO_PIN(PC, 12)
        /** @} */
    {% elif board in ["sltb001a"] %}
        /**
         * @name    Environmental sensors configuration
         *
         * Pin for enabling environmental sensors (BMP280, Si1133, Si7021, Si7210).
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
         * Connection to the on-board hall-effect sensor (Si7210). Available on Rev. A02
         * boards only.
         * @{
         */
        #define SI7210_I2C          I2C_DEV(0)
        /** @} */
    {% elif board in ["sltb004a"] %}
        /**
         * @name    Environmental sensors configuration
         *
         * Pin for enabling environmental sensors (BMP280, Si1133, Si7021, Si7210).
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
         * Connection to the on-board hall-effect sensor (Si7210).
         * @{
         */
        #define SI7210_I2C          I2C_DEV(0)
        /** @} */
    {% elif board in ["sltb009a"] %}
        /**
         * @name    Environmental sensors configuration
         *
         * Pin for enabling environmental sensors (Si1133, Si7021, Si7210).
         * @{
         */
        #define ENV_SENSE_PIC_ADDR  (0x01)
        #define ENV_SENSE_PIC_BIT   (0)
        /** @} */

        /**
         * @name    IMU sensor configuration
         *
         * Connection to the on-board IMU sensor (ICM-20648).
         * @{
         */
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
         * @name    UV/Ambient sensor configuration
         *
         * Connection to the on-board UV/ambient light sensor (Si1133).
         * @{
         */
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
         * Connection to the on-board hall-effect sensor (Si7210).
         * @{
         */
        #define SI7210_I2C          I2C_DEV(0)
        /** @} */
    {% elif board in ["sltb010a"] %}
        /**
         * @name    Environmental sensors configuration
         *
         * Pin for enabling environmental sensors (Si1133, Si7021, Si7210).
         * @{
         */
        #define ENV_SENSE_PIC_ADDR  (0x01)
        #define ENV_SENSE_PIC_BIT   (0)
        /** @} */

        /**
         * @name    IMU sensor configuration
         *
         * Connection to the on-board IMU sensor (ICM-20648).
         * @{
         */
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
         * @name    UV/Ambient sensor configuration
         *
         * Connection to the on-board UV/ambient light sensor (Si1133).
         * @{
         */
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
         * Connection to the on-board hall-effect sensor (Si7210).
         * @{
         */
        #define SI7210_I2C          I2C_DEV(0)
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
