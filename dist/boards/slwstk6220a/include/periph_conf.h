/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_slwstk6220a
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for the SLWSTK6220A starter kit
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cpu.h"

#include "periph_cpu.h"

#include "em_cmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Internal macro to calculate *_NUMOF based on config.
 */
#define PERIPH_NUMOF(config)    (sizeof(config) / sizeof(config[0]))

/**
 * @name    Clock configuration
 * @{
 */
#ifndef CMU_HFXOINIT
#define CMU_HFXOINIT        CMU_HFXOINIT_DEFAULT
#endif
#ifndef CMU_LFXOINIT
#define CMU_LFXOINIT        CMU_LFXOINIT_DEFAULT
#endif

#ifndef CLOCK_HF
#define CLOCK_HF            cmuSelect_HFXO
#endif
#ifndef CLOCK_CORE_DIV
#define CLOCK_CORE_DIV      cmuClkDiv_1
#endif
#ifndef CLOCK_LFA
#define CLOCK_LFA           cmuSelect_LFXO
#endif
#ifndef CLOCK_LFB
#define CLOCK_LFB           cmuSelect_LFXO
#endif
/** @} */

/**
 * @name    EMU configuration
 * @{
 */
#ifndef EMU_EM23INIT
#define EMU_EM23INIT         EMU_EM23INIT_DEFAULT
#endif
#ifndef EMU_EM4INIT
#define EMU_EM4INIT         EMU_EM4INIT_DEFAULT
#endif
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    {
        .dev = ADC0,
        .cmu = cmuClock_ADC0,
    }
};

static const adc_chan_conf_t adc_channel_config[] = {
    {
        .dev = 0,
        .input = adcSingleInputTemp,
        .reference = adcRef1V25,
        .acq_time = adcAcqTime8
    },
    {
        .dev = 0,
        .input = adcSingleInputVDDDiv3,
        .reference = adcRef1V25,
        .acq_time = adcAcqTime8
    }
};

#define ADC_DEV_NUMOF       PERIPH_NUMOF(adc_config)
#define ADC_NUMOF           PERIPH_NUMOF(adc_channel_config)
/** @} */

/**
 * @name    DAC configuration
 * @{
 */
static const dac_conf_t dac_config[] = {
    {
        .dev = DAC0,
        .cmu = cmuClock_DAC0,
    }
};

static const dac_chan_conf_t dac_channel_config[] = {
    {
        .dev = 0,
        .index = 1,
        .ref = dacRefVDD,
    }
};

#define DAC_DEV_NUMOF       PERIPH_NUMOF(dac_config)
#define DAC_NUMOF           PERIPH_NUMOF(dac_channel_config)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {
        .dev = I2C1,
        .sda_pin = GPIO_PIN(PE, 0),
        .scl_pin = GPIO_PIN(PE, 1),
        .loc = I2C_ROUTE_LOCATION_LOC2,
        .cmu = cmuClock_I2C1,
        .irq = I2C1_IRQn
    }
};

#define I2C_NUMOF           PERIPH_NUMOF(i2c_config)
#define I2C_0_ISR           isr_i2c1
/** @} */

/**
 * @name    PWM configuration
 * @{
 */
static const pwm_chan_conf_t pwm_channel_config[] = {
    {
        .index = 0,
        .pin = GPIO_PIN(PF, 6),
        .loc = TIMER_ROUTE_LOCATION_LOC2
    },
    {
        .index = 1,
        .pin = GPIO_PIN(PF, 7),
        .loc = TIMER_ROUTE_LOCATION_LOC2
    }
};

static const pwm_conf_t pwm_config[] = {
    {
        .dev = TIMER0,
        .cmu = cmuClock_TIMER0,
        .irq = TIMER0_IRQn,
        .channels = 2,
        .channel = pwm_channel_config
    }
};

#define PWM_DEV_NUMOF       PERIPH_NUMOF(pwm_config)
#define PWM_NUMOF           PERIPH_NUMOF(pwm_channel_config)
/** @} */

/**
 * @brief   RTC configuration
 */
#define RTC_NUMOF           (1U)

/**
 * @name    RTT configuration
 * @{
 */
#define RTT_NUMOF           (1U)

#define RTT_MAX_VALUE       (0xFFFFFF)
#define RTT_FREQUENCY       (1U)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_dev_t spi_config[] = {
    {
        .dev = USART1,
        .mosi_pin = GPIO_PIN(PD, 0),
        .miso_pin = GPIO_PIN(PD, 1),
        .clk_pin = GPIO_PIN(PD, 2),
        .loc = USART_ROUTE_LOCATION_LOC1,
        .cmu = cmuClock_USART1,
        .irq = USART1_RX_IRQn
    }
};

#define SPI_NUMOF           PERIPH_NUMOF(spi_config)
/** @} */

/**
 * @name    Timer configuration
 *
 * The implementation uses two timers in cascade mode.
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        {
            .dev = TIMER1,
            .cmu = cmuClock_TIMER1
        },
        {
            .dev = TIMER2,
            .cmu = cmuClock_TIMER2
        },
        .irq = TIMER2_IRQn
    }
};

#define TIMER_NUMOF         PERIPH_NUMOF(timer_config)
#define TIMER_0_ISR         isr_timer2
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev = USART2,
        .rx_pin = GPIO_PIN(PB, 4),
        .tx_pin = GPIO_PIN(PB, 3),
        .loc = USART_ROUTE_LOCATION_LOC1,
        .cmu = cmuClock_USART2,
        .irq = USART2_RX_IRQn
    },
    {
        .dev = USART1,
        .rx_pin = GPIO_PIN(PD, 1),
        .tx_pin = GPIO_PIN(PD, 0),
        .loc = USART_ROUTE_LOCATION_LOC1,
        .cmu = cmuClock_USART1,
        .irq = USART1_RX_IRQn
    },
    {
        .dev = LEUART0,
        .rx_pin = GPIO_PIN(PD, 5),
        .tx_pin = GPIO_PIN(PD, 4),
        .loc = LEUART_ROUTE_LOCATION_LOC0,
        .cmu = cmuClock_LEUART0,
        .irq = LEUART0_IRQn
    }
};

#define UART_NUMOF          PERIPH_NUMOF(uart_config)
#define UART_0_ISR_RX       isr_usart1_rx
#define UART_1_ISR_RX       isr_usart2_rx
#define UART_2_ISR_RX       isr_leuart0
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
