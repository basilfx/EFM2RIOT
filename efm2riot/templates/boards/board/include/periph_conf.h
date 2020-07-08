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
 * @brief       Configuration of CPU peripherals for the {{ board|upper }} starter kit
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

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cpu.h"
#include "periph_cpu.h"
#include "em_cmu.h"
{% strip 2 %}
    {% if board in ["slwstk6000b"] %}
        #include "board_module.h"
    {% endif %}
{% endstrip %}

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
{% strip 2 %}
    {% if board in ["slwstk6000b"] %}
        #define CLOCK_LFA           cmuSelect_LFRCO
    {% else %}
        #define CLOCK_LFA           cmuSelect_LFXO
    {% endif %}
{% endstrip %}
#endif
#ifndef CLOCK_LFB
{% strip 2 %}
    {% if board in ["slwstk6000b"] %}
        #define CLOCK_LFB           cmuSelect_LFRCO
    {% elif board in ["stk3200"] %}
        #define CLOCK_LFB           cmuSelect_CORELEDIV2
    {% else %}
        #define CLOCK_LFB           cmuSelect_LFXO
    {% endif %}
{% endstrip %}
#endif
{% strip 2 %}
    {% if cpu_series == 1 %}
        #ifndef CLOCK_LFE
        {% strip 2 %}
            {% if board in ["slwstk6000b"] %}
                #define CLOCK_LFE           cmuSelect_LFRCO
            {% else %}
                #define CLOCK_LFE           cmuSelect_LFXO
            {% endif %}
        {% endstrip %}
        #endif
    {% endif %}
{% endstrip %}
/** @} */

{% strip 2, ">" %}
    {% if board in ["slstk3401a", "sltb001a"] %}
        /**
         * @name    DC-DC configuration
         * @{
         */
        #ifdef EMU_DCDCINIT_OFF
        #error "This option will soft-brick your board. Please remove it."
        #endif
        /** @} */
    {% endif %}
{% endstrip %}

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
    {% strip 2 %}
        {% if board in ["slstk3301a", "slstk3401a", "slstk3402a", "slstk3701a", "sltb001a", "slwstk6000b"] %}
            {
                .dev = 0,
                .input = adcPosSelTEMP,
                .reference = adcRef1V25,
                .acq_time = adcAcqTime8
            },
            {
                .dev = 0,
                .input = adcPosSelAVDD,
                .reference = adcRef5V,
                .acq_time = adcAcqTime8
            }
        {% elif board in ["slwstk6220a", "stk3200", "stk3600", "stk3700", "stk3800"] %}
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
        {% endif %}
    {% endstrip %}
};

#define ADC_DEV_NUMOF       ARRAY_SIZE(adc_config)
#define ADC_NUMOF           ARRAY_SIZE(adc_channel_config)
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
    {% if board in ["slwstk6220a", "stk3600", "stk3700", "stk3800"] %}
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

        #define DAC_DEV_NUMOF       ARRAY_SIZE(dac_config)
        #define DAC_NUMOF           ARRAY_SIZE(dac_channel_config)
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {% strip 2 %}
        {% if board in ["slstk3301a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PD, 6),
                .scl_pin = GPIO_PIN(PD, 7),
                .loc = I2C_ROUTELOC0_SDALOC_LOC1 |
                       I2C_ROUTELOC0_SCLLOC_LOC1,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["slstk3400a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PD, 6),
                .scl_pin = GPIO_PIN(PD, 7),
                .loc = I2C_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 10),
                .scl_pin = GPIO_PIN(PC, 11),
                .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
                       I2C_ROUTELOC0_SCLLOC_LOC15,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["slstk3701a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 0),
                .scl_pin = GPIO_PIN(PC, 1),
                .loc = I2C_ROUTELOC0_SDALOC_LOC4 |
                       I2C_ROUTELOC0_SCLLOC_LOC4,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            },
            {
                .dev = I2C1,
                .sda_pin = GPIO_PIN(PC, 7),
                .scl_pin = GPIO_PIN(PC, 5),
                .loc = I2C_ROUTELOC0_SDALOC_LOC0 |
                       I2C_ROUTELOC0_SCLLOC_LOC0,
                .cmu = cmuClock_I2C1,
                .irq = I2C1_IRQn,
                .speed = I2C_SPEED_NORMAL
            },
            {
                .dev = I2C2,
                .sda_pin = GPIO_PIN(PI, 4),
                .scl_pin = GPIO_PIN(PI, 5),
                .loc = I2C_ROUTELOC0_SDALOC_LOC7 |
                       I2C_ROUTELOC0_SCLLOC_LOC7,
                .cmu = cmuClock_I2C2,
                .irq = I2C2_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["sltb001a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 10),
                .scl_pin = GPIO_PIN(PC, 11),
                .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
                       I2C_ROUTELOC0_SCLLOC_LOC15,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["sltb004a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 10),
                .scl_pin = GPIO_PIN(PC, 11),
                .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
                       I2C_ROUTELOC0_SCLLOC_LOC15,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["sltb009a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 10),
                .scl_pin = GPIO_PIN(PC, 11),
                .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
                       I2C_ROUTELOC0_SCLLOC_LOC15,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["sltb010a"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PC, 10),
                .scl_pin = GPIO_PIN(PC, 11),
                .loc = I2C_ROUTELOC0_SDALOC_LOC15 |
                       I2C_ROUTELOC0_SCLLOC_LOC15,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["slwstk6000b"] %}
            {
                .dev = I2C0,
                .sda_pin = MODULE_PIN_P13,
                .scl_pin = MODULE_PIN_P12,
                .loc = I2C_ROUTELOC0_SDALOC_LOC16 |
                       I2C_ROUTELOC0_SCLLOC_LOC14,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["slwstk6220a"] %}
            {
                .dev = I2C1,
                .sda_pin = GPIO_PIN(PE, 0),
                .scl_pin = GPIO_PIN(PE, 1),
                .loc = I2C_ROUTE_LOCATION_LOC2,
                .cmu = cmuClock_I2C1,
                .irq = I2C1_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["stk3200"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PE, 12),
                .scl_pin = GPIO_PIN(PE, 13),
                .loc = I2C_ROUTE_LOCATION_LOC6,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% elif board in ["stk3600", "stk3700", "stk3800"] %}
            {
                .dev = I2C0,
                .sda_pin = GPIO_PIN(PD, 6),
                .scl_pin = GPIO_PIN(PD, 7),
                .loc = I2C_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_I2C0,
                .irq = I2C0_IRQn,
                .speed = I2C_SPEED_NORMAL
            },
            {
                .dev = I2C1,
                .sda_pin = GPIO_PIN(PC, 4),
                .scl_pin = GPIO_PIN(PC, 5),
                .loc = I2C_ROUTE_LOCATION_LOC0,
                .cmu = cmuClock_I2C1,
                .irq = I2C1_IRQn,
                .speed = I2C_SPEED_NORMAL
            }
        {% endif %}
    {% endstrip %}
};

#define I2C_NUMOF           ARRAY_SIZE(i2c_config)
{% strip 2 %}
    {% if board in ["slstk3301a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slstk3400a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slstk3701a"] %}
        #define I2C_0_ISR           isr_i2c0
        #define I2C_1_ISR           isr_i2c1
        #define I2C_2_ISR           isr_i2c2
    {% elif board in ["sltb001a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["sltb004a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["sltb009a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["sltb010a"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slwstk6000b"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["slwstk6220a"] %}
        #define I2C_0_ISR           isr_i2c1
    {% elif board in ["stk3200"] %}
        #define I2C_0_ISR           isr_i2c0
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        #define I2C_0_ISR           isr_i2c0
        #define I2C_1_ISR           isr_i2c1
    {% endif %}
{% endstrip %}
/** @} */

{% strip 2, ">" %}
    {% if board in ["stk3600", "stk3700", "stk3800", "slwstk6220a"] %}
        /**
         * @name    PWM configuration
         * @{
         */
        static const pwm_chan_conf_t pwm_channel_config[] = {
            {% strip 2 %}
                {% if board in ["stk3600", "stk3700", "stk3800"] %}
                    {
                        .index = 2,
                        .pin = GPIO_PIN(PE, 2),
                        .loc = TIMER_ROUTE_LOCATION_LOC1
                    }
                {% elif board in ["slwstk6220a"] %}
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
                {% endif %}
            {% endstrip %}
        };

        static const pwm_conf_t pwm_config[] = {
            {% strip 2 %}
                {% if board in ["stk3600", "stk3700", "stk3800"] %}
                    {
                        .dev = TIMER3,
                        .cmu = cmuClock_TIMER3,
                        .irq = TIMER3_IRQn,
                        .channels = 1,
                        .channel = pwm_channel_config
                    }
                {% elif board in ["slwstk6220a"] %}
                    {
                        .dev = TIMER0,
                        .cmu = cmuClock_TIMER0,
                        .irq = TIMER0_IRQn,
                        .channels = 2,
                        .channel = pwm_channel_config
                    }
                {% endif %}
            {% endstrip %}
        };

        #define PWM_DEV_NUMOF       ARRAY_SIZE(pwm_config)
        #define PWM_NUMOF           ARRAY_SIZE(pwm_channel_config)
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @name    RTT configuration
 * @{
 */
{% strip 2 %}
    {% if cpu_series == 0 %}
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
        {% if board in ["slstk3301a"] %}
            {
                .dev = USART0,
                .mosi_pin = GPIO_PIN(PC, 11),
                .miso_pin = GPIO_PIN(PC, 10),
                .clk_pin = GPIO_PIN(PA, 12),
                .loc = USART_ROUTELOC0_RXLOC_LOC2 |
                       USART_ROUTELOC0_TXLOC_LOC2 |
                       USART_ROUTELOC0_CLKLOC_LOC5,
                .cmu = cmuClock_USART0,
                .irq = USART0_IRQn
            }
        {% elif board in ["slstk3400a"] %}
            {
                .dev = USART0,
                .mosi_pin = GPIO_PIN(PE, 10),
                .miso_pin = GPIO_PIN(PE, 11),
                .clk_pin = GPIO_PIN(PE, 12),
                .loc = USART_ROUTE_LOCATION_LOC0,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PC, 6),
                .miso_pin = GPIO_PIN(PC, 7),
                .clk_pin = GPIO_PIN(PC, 8),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11 |
                       USART_ROUTELOC0_CLKLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["slstk3701a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PA, 14),
                .miso_pin = GPIO_UNDEF,
                .clk_pin = GPIO_PIN(PC, 15),
                .loc = USART_ROUTELOC0_TXLOC_LOC6 |
                       USART_ROUTELOC0_CLKLOC_LOC3,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["sltb001a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PC, 6),
                .miso_pin = GPIO_PIN(PC, 7),
                .clk_pin = GPIO_PIN(PC, 8),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11 |
                       USART_ROUTELOC0_CLKLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["sltb004a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PC, 6),
                .miso_pin = GPIO_PIN(PC, 7),
                .clk_pin = GPIO_PIN(PC, 8),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11 |
                       USART_ROUTELOC0_CLKLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["sltb009a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PC, 6),
                .miso_pin = GPIO_PIN(PC, 7),
                .clk_pin = GPIO_PIN(PC, 8),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11 |
                       USART_ROUTELOC0_CLKLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["sltb010a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PC, 6),
                .miso_pin = GPIO_PIN(PC, 7),
                .clk_pin = GPIO_PIN(PC, 8),
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["slwstk6000b"] %}
            {
                .dev = USART1,
                .mosi_pin = MODULE_PIN_F16,
                .miso_pin = MODULE_PIN_P3,
                .clk_pin = MODULE_PIN_F15,
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11 |
                       USART_ROUTELOC0_CLKLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["slwstk6220a"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PD, 0),
                .miso_pin = GPIO_PIN(PD, 1),
                .clk_pin = GPIO_PIN(PD, 2),
                .loc = USART_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["stk3200"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PD, 7),
                .miso_pin = GPIO_PIN(PD, 6),
                .clk_pin = GPIO_PIN(PC, 15),
                .loc = USART_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["stk3600", "stk3700", "stk3800"] %}
            {
                .dev = USART1,
                .mosi_pin = GPIO_PIN(PD, 0),
                .miso_pin = GPIO_PIN(PD, 1),
                .clk_pin = GPIO_PIN(PD, 2),
                .loc = USART_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            },
            {
                .dev = USART2,
                .mosi_pin = GPIO_UNDEF,
                .miso_pin = GPIO_PIN(PC, 3),
                .clk_pin = GPIO_PIN(PC, 4),
                .loc = USART_ROUTE_LOCATION_LOC0,
                .cmu = cmuClock_USART2,
                .irq = USART2_RX_IRQn
            }
        {% endif %}
    {% endstrip %}
};

#define SPI_NUMOF           ARRAY_SIZE(spi_config)
/** @} */

/**
 * @name    Timer configuration
 *
 * The implementation uses two timers in cascade mode.
 * @{
 */
static const timer_conf_t timer_config[] = {
    {% strip 2 %}
        {% if board in ["slstk3301a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["slstk3400a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["slstk3701a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["sltb001a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["sltb004a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["sltb009a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["sltb010a"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["slwstk6000b"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["slwstk6220a"] %}
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
        {% elif board in ["stk3200"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% elif board in ["stk3600", "stk3700", "stk3800"] %}
            {
                {
                    .dev = TIMER0,
                    .cmu = cmuClock_TIMER0
                },
                {
                    .dev = TIMER1,
                    .cmu = cmuClock_TIMER1
                },
                .irq = TIMER1_IRQn
            }
        {% endif %}
    {% endstrip %}
};

#define TIMER_NUMOF         ARRAY_SIZE(timer_config)
{% strip 2 %}
    {% if board in ["slstk3301a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["slstk3400a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["slstk3701a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["sltb001a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["sltb004a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["sltb009a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["sltb010a"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["slwstk6000b"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["slwstk6220a"] %}
        #define TIMER_0_ISR         isr_timer2
    {% elif board in ["stk3200"] %}
        #define TIMER_0_ISR         isr_timer1
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        #define TIMER_0_ISR         isr_timer1
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {% strip 2 %}
        {% if board in ["slstk3301a"] %}
            {
                .dev = USART1,
                .rx_pin = GPIO_PIN(PD, 1),
                .tx_pin = GPIO_PIN(PD, 0),
                .loc = USART_ROUTELOC0_RXLOC_LOC1 |
                       USART_ROUTELOC0_TXLOC_LOC1,
                .cmu = cmuClock_USART1,
                .irq = USART1_IRQn
            }
        {% elif board in ["slstk3400a"] %}
            {
                .dev = USART1,
                .rx_pin = GPIO_PIN(PA, 0),
                .tx_pin = GPIO_PIN(PF, 2),
                .loc = USART_ROUTE_LOCATION_LOC4,
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
        {% elif board in ["slstk3401a", "slstk3402a"] %}
            {
                .dev = USART0,
                .rx_pin = GPIO_PIN(PA, 1),
                .tx_pin = GPIO_PIN(PA, 0),
                .loc = USART_ROUTELOC0_RXLOC_LOC0 |
                       USART_ROUTELOC0_TXLOC_LOC0,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            },
            {
                .dev = USART1,
                .rx_pin = GPIO_PIN(PC, 7),
                .tx_pin = GPIO_PIN(PC, 6),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            },
            {
                .dev = LEUART0,
                .rx_pin = GPIO_PIN(PD, 11),
                .tx_pin = GPIO_PIN(PD, 10),
                .loc = LEUART_ROUTELOC0_RXLOC_LOC18 |
                       LEUART_ROUTELOC0_TXLOC_LOC18,
                .cmu = cmuClock_LEUART0,
                .irq = LEUART0_IRQn
            }
        {% elif board in ["slstk3701a"] %}
            {
                .dev = USART4,
                .rx_pin = GPIO_PIN(PH, 5),
                .tx_pin = GPIO_PIN(PH, 4),
                .loc = USART_ROUTELOC0_RXLOC_LOC4 |
                       USART_ROUTELOC0_TXLOC_LOC4,
                .cmu = cmuClock_USART4,
                .irq = USART4_RX_IRQn
            },
        {% elif board in ["sltb001a"] %}
            {
                .dev = USART0,
                .rx_pin = GPIO_PIN(PA, 1),
                .tx_pin = GPIO_PIN(PA, 0),
                .loc = USART_ROUTELOC0_RXLOC_LOC0 |
                       USART_ROUTELOC0_TXLOC_LOC0,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            },
            {
                .dev = USART1,
                .rx_pin = GPIO_PIN(PC, 6),
                .tx_pin = GPIO_PIN(PC, 7),
                .loc = USART_ROUTELOC0_RXLOC_LOC11 |
                       USART_ROUTELOC0_TXLOC_LOC11,
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            },
            {
                .dev = LEUART0,
                .rx_pin = GPIO_PIN(PD, 11),
                .tx_pin = GPIO_PIN(PD, 10),
                .loc = LEUART_ROUTELOC0_RXLOC_LOC18 |
                       LEUART_ROUTELOC0_TXLOC_LOC18,
                .cmu = cmuClock_LEUART0,
                .irq = LEUART0_IRQn
            }
        {% elif board in ["sltb004a"] %}
            {
                .dev = USART0,
                .rx_pin = GPIO_PIN(PA, 1),
                .tx_pin = GPIO_PIN(PA, 0),
                .loc = USART_ROUTELOC0_RXLOC_LOC0 |
                       USART_ROUTELOC0_TXLOC_LOC0,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            }
        {% elif board in ["sltb009a"] %}
            {
                .dev = USART0,
                .rx_pin = GPIO_PIN(PE, 6),
                .tx_pin = GPIO_PIN(PE, 7),
                .loc = USART_ROUTELOC0_RXLOC_LOC1 |
                       USART_ROUTELOC0_TXLOC_LOC1,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            }
        {% elif board in ["sltb010a"] %}
            {
                .dev = USART1,
                .rx_pin = GPIO_PIN(PA, 6),
                .tx_pin = GPIO_PIN(PA, 5),
                .cmu = cmuClock_USART1,
                .irq = USART1_RX_IRQn
            }
        {% elif board in ["slwstk6000b"] %}
            {
                .dev = USART0,
                .rx_pin = MODULE_PIN_F7,
                .tx_pin = MODULE_PIN_F6,
                .loc = USART_ROUTELOC0_RXLOC_LOC0 |
                       USART_ROUTELOC0_TXLOC_LOC0,
                .cmu = cmuClock_USART0,
                .irq = USART0_RX_IRQn
            }
        {% elif board in ["slwstk6220a"] %}
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
        {% elif board in ["stk3200"] %}
            {
                .dev = LEUART0,
                .rx_pin = GPIO_PIN(PD, 5),
                .tx_pin = GPIO_PIN(PD, 4),
                .loc = LEUART_ROUTE_LOCATION_LOC0,
                .cmu = cmuClock_LEUART0,
                .irq = LEUART0_IRQn
            }
        {% elif board in ["stk3600", "stk3700", "stk3800"] %}
            {
                .dev = UART0,
                .rx_pin = GPIO_PIN(PE, 1),
                .tx_pin = GPIO_PIN(PE, 0),
                .loc = UART_ROUTE_LOCATION_LOC1,
                .cmu = cmuClock_UART0,
                .irq = UART0_RX_IRQn
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
        {% endif %}
    {% endstrip %}
};

#define UART_NUMOF          ARRAY_SIZE(uart_config)
{% strip 2 %}
    {% if board in ["slstk3301a"] %}
        #define UART_0_ISR_RX       isr_usart1
    {% elif board in ["slstk3400a"] %}
        #define UART_0_ISR_RX       isr_usart1_rx
        #define UART_1_ISR_RX       isr_leuart0
    {% elif board in ["slstk3401a", "slstk3402a"] %}
        #define UART_0_ISR_RX       isr_usart0_rx
        #define UART_1_ISR_RX       isr_usart1_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["slstk3701a"] %}
        #define UART_0_ISR_RX       isr_usart4_rx
    {% elif board in ["sltb001a"] %}
        #define UART_0_ISR_RX       isr_usart0_rx
        #define UART_1_ISR_RX       isr_usart1_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["sltb004a"] %}
        #define UART_0_ISR_RX       isr_usart0_rx
    {% elif board in ["sltb009a"] %}
        #define UART_0_ISR_RX       isr_usart0_rx
    {% elif board in ["sltb010a"] %}
        #define UART_0_ISR_RX       isr_usart1_rx
    {% elif board in ["slwstk6000b"] %}
        #define UART_0_ISR_RX       isr_usart0_rx
    {% elif board in ["slwstk6220a"] %}
        #define UART_0_ISR_RX       isr_usart1_rx
        #define UART_1_ISR_RX       isr_usart2_rx
        #define UART_2_ISR_RX       isr_leuart0
    {% elif board in ["stk3200"] %}
        #define UART_0_ISR_RX       isr_leuart0
    {% elif board in ["stk3600", "stk3700", "stk3800"] %}
        #define UART_0_ISR_RX       isr_uart0_rx
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
