/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_stk3800
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for the STK3800 starter kit
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
 * @name    Clock configuration
 * @{
 */
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
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    {
        ADC0,                               /* device */
        cmuClock_ADC0,                      /* CMU register */
    }
};

static const adc_chan_conf_t adc_channel_config[] = {
    {
        0,                                  /* device index */
        adcSingleInputTemp,                 /* channel to use */
        adcRef1V25,                         /* channel reference */
        adcAcqTime8                         /* acquisition time */
    },
    {
        0,                                  /* device index */
        adcSingleInputVDDDiv3,              /* channel to use */
        adcRef1V25,                         /* channel reference */
        adcAcqTime8                         /* acquisition time */
    }
};

#define ADC_NUMOF           (2U)
#define ADC_0_EN            (1)
#define ADC_1_EN            (1)
/** @} */

/**
 * @name    DAC configuration
 * @{
 */
static const dac_conf_t dac_config[] = {
    {
        DAC0,                               /* device */
        cmuClock_DAC0,                      /* CMU register */
    }
};

static const dac_chan_conf_t dac_channel_config[] = {
    {
        0,                                  /* DAC channel index */
        1,                                  /* channel to use */
        dacRefVDD,                          /* channel reference */
    }
};

#define DAC_NUMOF           (1U)
#define DAC_0_EN            (1)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {
        I2C0,                               /* device */
        GPIO_PIN(PD, 6),                    /* SDA pin */
        GPIO_PIN(PD, 7),                    /* SCL pin */
        I2C_ROUTE_LOCATION_LOC1,            /* AF location */
        cmuClock_I2C0,                      /* CMU register */
        I2C0_IRQn                           /* IRQ base channel */
    },
    {
        I2C1,                               /* device */
        GPIO_PIN(PC, 4),                    /* SDA pin */
        GPIO_PIN(PC, 5),                    /* SCL pin */
        I2C_ROUTE_LOCATION_LOC0,            /* AF location */
        cmuClock_I2C1,                      /* CMU register */
        I2C1_IRQn                           /* IRQ base channel */
    }
};

#define I2C_NUMOF           (2U)
#define I2C_0_EN            (1)
#define I2C_1_EN            (1)
#define I2C_0_ISR           isr_i2c0
#define I2C_1_ISR           isr_i2c1
/** @} */

/**
 * @name    PWM configuration
 * @{
 */
static const pwm_chan_conf_t pwm_channel_config[] = {
    {
        2,                          /* channel index */
        GPIO_PIN(PE, 2),            /* PWM pin */
        TIMER_ROUTE_LOCATION_LOC1   /* AF location */
    }
};

static const pwm_conf_t pwm_config[] = {
    {
        TIMER3,                     /* device */
        cmuClock_TIMER3,            /* CMU register */
        TIMER3_IRQn,                /* IRQ base channel */
        1,                          /* number of channels */
        pwm_channel_config          /* first channel config */
    }
};

#define PWM_NUMOF           (1U)
#define PWM_0_EN            (1)
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
        USART1,                             /* device */
        GPIO_PIN(PD, 0),                    /* MOSI pin */
        GPIO_PIN(PD, 1),                    /* MISO pin */
        GPIO_PIN(PD, 2),                    /* CLK pin */
        USART_ROUTE_LOCATION_LOC1,          /* AF location */
        cmuClock_USART1,                    /* CMU register */
        USART1_RX_IRQn                      /* IRQ base channel */
    },
    {
        USART2,                             /* device */
        GPIO_UNDEF,                         /* MOSI pin */
        GPIO_PIN(PC, 3),                    /* MISO pin */
        GPIO_PIN(PC, 4),                    /* CLK pin */
        USART_ROUTE_LOCATION_LOC0,          /* AF location */
        cmuClock_USART2,                    /* CMU register */
        USART2_RX_IRQn                      /* IRQ base channel */
    }
};

#define SPI_NUMOF           (2U)
#define SPI_0_EN            (1)
#define SPI_1_EN            (1)
/** @} */

/**
 * @name    Timer configuration
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        {
            TIMER0,             /* lower numbered timer */
            cmuClock_TIMER0     /* pre-scaler bit in the CMU register */
        },
        {
            TIMER1,             /* higher numbered timer, this is the one */
            cmuClock_TIMER1     /* pre-scaler bit in the CMU register */
        },
        TIMER1_IRQn             /* IRQn of the higher numbered timer */
    }
};

#define TIMER_NUMOF         (1U)
#define TIMER_0_EN          (1)
#define TIMER_0_ISR         isr_timer1
#define TIMER_0_MAX_VALUE   (0xffff)
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        UART0,                              /* device */
        GPIO_PIN(PE, 1),                    /* RX pin */
        GPIO_PIN(PE, 0),                    /* TX pin */
        UART_ROUTE_LOCATION_LOC1,           /* AF location */
        cmuClock_UART0,                     /* CMU register */
        UART0_RX_IRQn                       /* IRQ base channel */
    },
    {
        USART1,                             /* device */
        GPIO_PIN(PD, 1),                    /* RX pin */
        GPIO_PIN(PD, 0),                    /* TX pin */
        USART_ROUTE_LOCATION_LOC1,          /* AF location */
        cmuClock_USART1,                    /* CMU register */
        USART1_RX_IRQn                      /* IRQ base channel */
    },
    {
        LEUART0,                            /* device */
        GPIO_PIN(PD, 5),                    /* RX pin */
        GPIO_PIN(PD, 4),                    /* TX pin */
        LEUART_ROUTE_LOCATION_LOC0,         /* AF location */
        cmuClock_LEUART0,                   /* CMU register */
        LEUART0_IRQn                        /* IRQ base channel */
    }
};

#define UART_NUMOF          (3U)
#define UART_0_EN           (1)
#define UART_1_EN           (1)
#define UART_2_EN           (1)
#define UART_0_ISR_RX       isr_uart0_rx
#define UART_1_ISR_RX       isr_usart1_rx
#define UART_2_ISR_RX       isr_leuart0
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
