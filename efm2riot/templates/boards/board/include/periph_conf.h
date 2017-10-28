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
 * @brief       Configuration of CPU peripherals for the {{ board_display_name }} starter kit
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
{% strip 2 %}
    {% if board in ["stk3200"] %}
        #define CLOCK_LFB           cmuSelect_CORELEDIV2
    {% else %}
        #define CLOCK_LFB           cmuSelect_LFXO
    {% endif %}
{% endstrip %}
#endif
{% strip 2 %}
    {% if board in ["slstk3401a", "slstk3402a", "sltb001a"] %}
        #ifndef CLOCK_LFE
        #define CLOCK_LFE           cmuSelect_LFXO
        #endif
    {% endif %}
{% endstrip %}
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
    {% strip 2 %}
        {% if board in ["stk3200", "stk3600", "stk3700", "stk3800", "slwstk6220a"] %}
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
        {% elif board in ["slstk3401a", "slstk3402a", "sltb001a"] %}
            {
                0,                                  /* device index */
                adcPosSelTEMP,                      /* channel to use */
                adcRef1V25,                         /* channel reference */
                adcAcqTime8                         /* acquisition time */
            },
            {
                0,                                  /* device index */
                adcPosSelAVDD,                      /* channel to use */
                adcRef5V,                           /* channel reference */
                adcAcqTime8                         /* acquisition time */
            }
        {% endif %}
    {% endstrip %}
};

#define ADC_NUMOF           (2U)
/** @} */

{% strip 2, ">" %}
    {% if development %}
        /**
         * @brief   Crypto configuration.
         */
        #define HWCRYPTO_NUMOF      (1U)
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if board in ["stk3600", "stk3700", "stk3800", "slwstk6220a"] %}
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
        /** @} */
    {% else %}
        /**
         * @brief   DAC configuration
         */
        #define DAC_NUMOF           (0U)
    {% endif %}
{% endstrip %}

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
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
        {% elif board in ["stk3200"] %}
            {
                I2C0,                               /* device */
                GPIO_PIN(PE, 12),                   /* SDA pin */
                GPIO_PIN(PE, 13),                   /* SCL pin */
                I2C_ROUTE_LOCATION_LOC6,            /* AF location */
                cmuClock_I2C0,                      /* CMU register */
                I2C0_IRQn                           /* IRQ base channel */
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                I2C0,                               /* device */
                GPIO_PIN(PC, 10),                   /* SDA pin */
                GPIO_PIN(PC, 11),                   /* SCL pin */
                I2C_ROUTELOC0_SDALOC_LOC15 |
                    I2C_ROUTELOC0_SCLLOC_LOC15,     /* AF location */
                cmuClock_I2C0,                      /* CMU register */
                I2C0_IRQn                           /* IRQ base channel */
            }
        {% elif board in ["slwstk6220a"] %}
            {
                I2C1,                               /* device */
                GPIO_PIN(PE, 0),                    /* SDA pin */
                GPIO_PIN(PE, 1),                    /* SCL pin */
                I2C_ROUTE_LOCATION_LOC2,            /* AF location */
                cmuClock_I2C1,                      /* CMU register */
                I2C1_IRQn                           /* IRQ base channel */
            }
        {% elif board in ["sltb001a"] %}
            {
                I2C0,                               /* device */
                GPIO_PIN(PC, 10),                   /* SDA pin */
                GPIO_PIN(PC, 11),                   /* SCL pin */
                I2C_ROUTELOC0_SDALOC_LOC15 |
                    I2C_ROUTELOC0_SCLLOC_LOC15,     /* AF location */
                cmuClock_I2C0,                      /* CMU register */
                I2C0_IRQn                           /* IRQ base channel */
            }
        {% endif %}
    {% endstrip %}
};

{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define I2C_NUMOF           (2U)
        #define I2C_0_ISR           isr_i2c0
        #define I2C_1_ISR           isr_i2c1
    {% elif board in ["stk3200"] %}
        #define I2C_NUMOF           (1U)
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define I2C_NUMOF           (1U)
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slwstk6220a"] %}
        #define I2C_NUMOF           (1U)
        #define I2C_0_ISR           isr_i2c1
    {% elif board in ["sltb001a"] %}
        #define I2C_NUMOF           (1U)
        #define I2C_0_ISR           isr_i2c0
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    PWM configuration
 * @{
 */
static const pwm_chan_conf_t pwm_channel_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
            {
                2,                          /* channel index */
                GPIO_PIN(PE, 2),            /* PWM pin */
                TIMER_ROUTE_LOCATION_LOC1   /* AF location */
            }
        {% elif board in ["stk3200"] %}
            /* no available channels */
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            /* no available channels */
        {% elif board in ["slwstk6220a"] %}
            {
                0,                          /* channel index */
                GPIO_PIN(PF, 6),            /* PWM pin */
                TIMER_ROUTE_LOCATION_LOC2   /* AF location */
            },
            {
                1,                          /* channel index */
                GPIO_PIN(PF, 7),            /* PWM pin */
                TIMER_ROUTE_LOCATION_LOC2   /* AF location */
            }
        {% elif board in ["sltb001a"] %}
            /* no available channels */
        {% endif %}
    {% endstrip %}
};

static const pwm_conf_t pwm_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
            {
                TIMER3,                     /* device */
                cmuClock_TIMER3,            /* CMU register */
                TIMER3_IRQn,                /* IRQ base channel */
                1,                          /* number of channels */
                pwm_channel_config          /* first channel config */
            }
        {% elif board in ["stk3200"] %}
            /* no available timers */
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            /* no available timers */
        {% elif board in ["slwstk6220a"] %}
            {
                TIMER0,                     /* device */
                cmuClock_TIMER0,            /* CMU register */
                TIMER0_IRQn,                /* IRQ base channel */
                2,                          /* number of channels */
                pwm_channel_config          /* first channel config */
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            /* no available timers */
        {% elif board in ["sltb001a"] %}
            /* no available timers */
        {% endif %}
    {% endstrip %}
};

{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define PWM_NUMOF                    (1U)
    {% elif board in ["stk3200"] %}
        #define PWM_NUMOF                    (0U)
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define PWM_NUMOF                    (0U)
    {% elif board in ["slwstk6220a"] %}
        #define PWM_NUMOF                    (1U)
    {% elif board in ["sltb001a"] %}
        #define PWM_NUMOF                    (0U)
    {% endif %}
{% endstrip %}
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

{% strip 2 %}
    {% if cpu_platform == 1 %}
        #define RTT_MAX_VALUE       (0xFFFFFF)
        #define RTT_FREQUENCY       (1U)
    {% else %}
        #define RTT_MAX_VALUE       (0xFFFFFFFF)
        #define RTT_FREQUENCY       (1U)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_dev_t spi_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
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
        {% elif board in ["stk3200"] %}
            {
                USART1,                             /* device */
                GPIO_PIN(PD, 7),                    /* MOSI pin */
                GPIO_PIN(PD, 6),                    /* MISO pin */
                GPIO_PIN(PC, 15),                   /* CLK pin */
                USART_ROUTE_LOCATION_LOC1,          /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                USART1,                             /* device */
                GPIO_PIN(PC, 6),                    /* MOSI pin */
                GPIO_PIN(PC, 7),                    /* MISO pin */
                GPIO_PIN(PC, 8),                    /* CLK pin */
                USART_ROUTELOC0_RXLOC_LOC11 |
                    USART_ROUTELOC0_TXLOC_LOC11 |
                    USART_ROUTELOC0_CLKLOC_LOC11,   /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            }
        {% elif board in ["slwstk6220a"] %}
            {
                USART1,                             /* device */
                GPIO_PIN(PD, 0),                    /* MOSI pin */
                GPIO_PIN(PD, 1),                    /* MISO pin */
                GPIO_PIN(PD, 2),                    /* CLK pin */
                USART_ROUTE_LOCATION_LOC1,          /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            }
        {% elif board in ["sltb001a"] %}
            {
                USART1,                             /* device */
                GPIO_PIN(PC, 6),                    /* MOSI pin */
                GPIO_PIN(PC, 7),                    /* MISO pin */
                GPIO_PIN(PC, 8),                    /* CLK pin */
                USART_ROUTELOC0_RXLOC_LOC11 |
                    USART_ROUTELOC0_TXLOC_LOC11 |
                    USART_ROUTELOC0_CLKLOC_LOC11,   /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            }
        {% endif %}
    {% endstrip %}
};

{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define SPI_NUMOF           (2U)
    {% elif board in ["stk3200"] %}
        #define SPI_NUMOF           (1U)
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define SPI_NUMOF           (1U)
    {% elif board in ["slwstk6220a"] %}
        #define SPI_NUMOF           (1U)
    {% elif board in ["sltb001a"] %}
        #define SPI_NUMOF           (1U)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    Timer configuration
 * @{
 */
static const timer_conf_t timer_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
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
        {% elif board in ["stk3200"] %}
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
        {% elif board in ["slstk3401a", "slstk3402a"] %}
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
        {% elif board in ["slwstk6220a"] %}
            {
                {
                    TIMER1,             /* lower numbered timer */
                    cmuClock_TIMER1     /* pre-scaler bit in the CMU register */
                },
                {
                    TIMER2,             /* higher numbered timer, this is the one */
                    cmuClock_TIMER2     /* pre-scaler bit in the CMU register */
                },
                TIMER2_IRQn             /* IRQn of the higher numbered timer */
            }
        {% elif board in ["sltb001a"] %}
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
        {% endif %}
    {% endstrip %}
};

{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define TIMER_NUMOF         (1U)
        #define TIMER_0_ISR         isr_timer1
        #define TIMER_0_MAX_VALUE   (0xffff)
    {% elif board in ["stk3200"] %}
        #define TIMER_NUMOF         (1U)
        #define TIMER_0_ISR         isr_timer1
        #define TIMER_0_MAX_VALUE   (0xffff)
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define TIMER_NUMOF         (1U)
        #define TIMER_0_ISR         isr_timer1
        #define TIMER_0_MAX_VALUE   (0xffff)
    {% elif board in ["slwstk6220a"] %}
        #define TIMER_NUMOF         (1U)
        #define TIMER_0_ISR         isr_timer2
        #define TIMER_0_MAX_VALUE   (0xffff)
    {% elif board in ["sltb001a"] %}
        #define TIMER_NUMOF         (1U)
        #define TIMER_0_ISR         isr_timer1
        #define TIMER_0_MAX_VALUE   (0xffff)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {% strip 2 %}
        {% if board in ["stk3600", "stk3700", "stk3800"] %}
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
        {% elif board in ["stk3200"] %}
            {
                LEUART0,                            /* device */
                GPIO_PIN(PD, 5),                    /* RX pin */
                GPIO_PIN(PD, 4),                    /* TX pin */
                LEUART_ROUTE_LOCATION_LOC0,         /* AF location */
                cmuClock_LEUART0,                   /* CMU register */
                LEUART0_IRQn                        /* IRQ base channel */
            },
            {
                USART1,                             /* device */
                GPIO_PIN(PD, 6),                    /* RX pin */
                GPIO_PIN(PD, 7),                    /* TX pin */
                USART_ROUTE_LOCATION_LOC2,          /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                USART0,                             /* device */
                GPIO_PIN(PA, 1),                    /* RX pin */
                GPIO_PIN(PA, 0),                    /* TX pin */
                USART_ROUTELOC0_RXLOC_LOC0 |
                    USART_ROUTELOC0_TXLOC_LOC0,     /* AF location */
                cmuClock_USART0,                    /* CMU register */
                USART0_RX_IRQn                      /* IRQ base channel */
            },
            {
                USART1,                             /* device */
                GPIO_PIN(PC, 6),                    /* RX pin */
                GPIO_PIN(PC, 7),                    /* TX pin */
                USART_ROUTELOC0_RXLOC_LOC11 |
                    USART_ROUTELOC0_TXLOC_LOC11,    /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            },
            {
                LEUART0,                            /* device */
                GPIO_PIN(PD, 11),                   /* RX pin */
                GPIO_PIN(PD, 10),                   /* TX pin */
                LEUART_ROUTELOC0_RXLOC_LOC18 |
                    LEUART_ROUTELOC0_TXLOC_LOC18,   /* AF location */
                cmuClock_LEUART0,                   /* CMU register */
                LEUART0_IRQn                        /* IRQ base channel */
            }
        {% elif board in ["slwstk6220a"] %}
            {
                USART2,                             /* device */
                GPIO_PIN(PB, 4),                    /* RX pin */
                GPIO_PIN(PB, 3),                    /* TX pin */
                USART_ROUTE_LOCATION_LOC1,          /* AF location */
                cmuClock_USART2,                    /* CMU register */
                USART2_RX_IRQn                      /* IRQ base channel */
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
        {% elif board in ["sltb001a"] %}
            {
                USART0,                             /* device */
                GPIO_PIN(PA, 1),                    /* RX pin */
                GPIO_PIN(PA, 0),                    /* TX pin */
                USART_ROUTELOC0_RXLOC_LOC0 |
                    USART_ROUTELOC0_TXLOC_LOC0,     /* AF location */
                cmuClock_USART0,                    /* CMU register */
                USART0_RX_IRQn                      /* IRQ base channel */
            },
            {
                USART1,                             /* device */
                GPIO_PIN(PC, 6),                    /* RX pin */
                GPIO_PIN(PC, 7),                    /* TX pin */
                USART_ROUTELOC0_RXLOC_LOC11 |
                    USART_ROUTELOC0_TXLOC_LOC11,    /* AF location */
                cmuClock_USART1,                    /* CMU register */
                USART1_RX_IRQn                      /* IRQ base channel */
            },
            {
                LEUART0,                            /* device */
                GPIO_PIN(PD, 11),                   /* RX pin */
                GPIO_PIN(PD, 10),                   /* TX pin */
                LEUART_ROUTELOC0_RXLOC_LOC18 |
                    LEUART_ROUTELOC0_TXLOC_LOC18,   /* AF location */
                cmuClock_LEUART0,                   /* CMU register */
                LEUART0_IRQn                        /* IRQ base channel */
            }
        {% endif %}
    {% endstrip %}
};

{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define UART_NUMOF          (3U)
        #define UART_0_ISR_RX       isr_uart0_rx
        #define UART_1_ISR_RX       isr_usart1_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["stk3200"] %}
        #define UART_NUMOF          (2U)
        #define UART_0_ISR_RX       isr_leuart0
        #define UART_1_ISR_RX       isr_usart1_rx
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define UART_NUMOF          (3U)
        #define UART_0_ISR_RX       isr_usart0_rx
        #define UART_1_ISR_RX       isr_usart1_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["slwstk6220a"] %}
        #define UART_NUMOF          (3U)
        #define UART_0_ISR_RX       isr_usart1_rx
        #define UART_1_ISR_RX       isr_usart2_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["sltb001a"] %}
        #define UART_NUMOF          (3U)
        #define UART_0_ISR_RX       isr_usart0_rx
        #define UART_1_ISR_RX       isr_usart1_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% endif %}
{% endstrip %}
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
