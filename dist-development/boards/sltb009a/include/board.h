/*
 * Copyright (C) 2015-2020 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_sltb009a
 * @{
 *
 * @file
 * @brief       Board specific definitions for the SLTB009A starter kit
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
 * The timer runs at 250 kHz to increase accuracy, or at 32.768 kHz if
 * LETIMER is used.
 * @{
 */
#if IS_ACTIVE(CONFIG_EFM32_XTIMER_USE_LETIMER)
#define XTIMER_DEV          (TIMER_DEV(1))
#define XTIMER_HZ           (32768UL)
#define XTIMER_WIDTH        (16)
#else
#define XTIMER_DEV          (TIMER_DEV(0))
#define XTIMER_HZ           (250000UL)
#define XTIMER_WIDTH        (16)
#endif
#define XTIMER_CHAN         (0)
/** @} */

/**
 * @name    Push button pin definitions
 * @{
 */
#define PB0_PIN             GPIO_PIN(PD, 5)
#define PB1_PIN             GPIO_PIN(PD, 8)
/** @} */

/**
 * @name    LED pin definitions
 * @{
 */
#define LED0R_PIN           GPIO_PIN(PA, 12)
#define LED0G_PIN           GPIO_PIN(PA, 13)
#define LED0B_PIN           GPIO_PIN(PA, 14)
#define LED1R_PIN           GPIO_PIN(PD, 6)
#define LED1G_PIN           GPIO_PIN(PF, 12)
#define LED1B_PIN           GPIO_PIN(PE, 12)
#define LED0_PIN            LED0R_PIN
#define LED1_PIN            LED1R_PIN
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
#ifndef ICM20648_ENABLED
#define ICM20648_ENABLED    0
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
 * @name    UV/Ambient sensor configuration
 *
 * Connection to the on-board UV/ambient light sensor (Si1133).
 * @{
 */
#ifndef SI1133_ENABLED
#define SI1133_ENABLED      0
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
 * Connection to the on-board hall-effect sensor (Si7210).
 * @{
 */
#define SI7210_I2C          I2C_DEV(0)
/** @} */

/**
 * @brief   Initialize the board (GPIO, sensors, clocks).
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
