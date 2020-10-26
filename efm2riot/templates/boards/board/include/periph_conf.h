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
{% strip 1 %}
    #define CLOCK_LFA           {{ peripherals.cmu.lfa }}
{% endstrip %}
#endif
#ifndef CLOCK_LFB
{% strip 1 %}
    #define CLOCK_LFB           {{ peripherals.cmu.lfb }}
{% endstrip %}
#endif
{% strip 2 %}
    {% if cpu_series == 1 %}
        #ifndef CLOCK_LFE
        #define CLOCK_LFE           {{ peripherals.cmu.lfe }}
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

{% strip 2, ">" %}
    {% if peripherals.adc %}
        /**
         * @name    ADC configuration
         * @{
         */
        static const adc_conf_t adc_config[] = {
            {% strip 2 %}
                {% for adc in peripherals.adc %}
                    {
                        .dev = {{ adc.peripheral }},
                        .cmu = cmuClock_{{ adc.peripheral }},
                    }{{ "," if not loop.last }}
                {% endfor %}
            {% endstrip %}
        };

        {% strip 2 %}
            {% for adc in peripherals.adc %}
                static const adc_chan_conf_t adc_channel_config[] = {
                    {% strip 2 %}
                        {% for channel in adc.channels %}
                            {
                                .dev = {{ channel.dev }},
                                .input = {{ channel.input }},
                                .reference = {{ channel.reference }},
                                .acq_time = {{ channel.acq_time }}
                            }{{ "," if not loop.last }}
                        {% endfor %}
                    {% endstrip %}
                };
            {% endfor %}
        {% endstrip %}

        #define ADC_DEV_NUMOF       ARRAY_SIZE(adc_config)
        #define ADC_NUMOF           ARRAY_SIZE(adc_channel_config)
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if development %}
        /**
         * @brief   Crypto configuration.
         */
        #define HWCRYPTO_NUMOF      (1U)
    {% endif %}
{% endstrip %}

{% strip 2, ">" %}
    {% if peripherals.dac %}
        /**
         * @name    DAC configuration
         * @{
         */
        static const dac_conf_t dac_config[] = {
            {% strip 2 %}
                {% for dac in peripherals.dac %}
                    {
                        .dev = {{ dac.peripheral }},
                        .cmu = cmuClock_{{ dac.peripheral }},
                    }{{ "," if not loop.last }}
                {% endfor %}
            {% endstrip %}
        };

        {% strip 2 %}
            {% for dac in peripherals.dac %}
                static const dac_chan_conf_t dac_channel_config[] = {
                    {% strip 2 %}
                        {% for channel in dac.channels %}
                            {
                                .dev = {{ channel.dev }},
                                .index = {{ channel.index }},
                                .ref = {{ channel.ref }},
                            }{{ "," if not loop.last }}
                        {% endfor %}
                    {% endstrip %}
                };
            {% endfor %}
        {% endstrip %}

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
        {% for i2c in peripherals.i2c %}
            {
                .dev = {{ i2c.peripheral }},
                .sda_pin = {{ i2c.sda_pin|riot }},
                .scl_pin = {{ i2c.scl_pin|riot }},
                {% strip 2 %}
                    {% if cpu_series == 0 %}
                        .loc = {{ i2c.loc }},
                    {% elif cpu_series == 1 %}
                        .loc = {{ i2c.sda_loc }} |
                               {{ i2c.scl_loc }},
                    {% endif %}
                {% endstrip %}
                .cmu = cmuClock_{{ i2c.peripheral }},
                .irq = {{ i2c.peripheral }}_IRQn,
                .speed = I2C_SPEED_NORMAL
            }{{ "," if not loop.last }}
        {% endfor %}
    {% endstrip %}
};

#define I2C_NUMOF           ARRAY_SIZE(i2c_config)
{% strip 2 %}
    {% for i2c in peripherals.i2c %}
        #define I2C_{{ loop.index0 }}_ISR           isr_{{ i2c.peripheral|lower }}
    {% endfor %}
{% endstrip %}
/** @} */

{% strip 2, ">" %}
    {% if peripherals.pwm %}
        /**
         * @name    PWM configuration
         * @{
         */
        static const pwm_chan_conf_t pwm_channel_config[] = {
            {% strip 3 %}
                {% for pwm in peripherals.pwm %}
                    {% for channel in pwm.channels %}
                        {
                            .index = {{ channel.index }},
                            .pin = {{ channel.pin|riot }},
                            .loc = {{ channel.loc }}
                        }{{ "," if not loop.last }}
                    {% endfor %}
                {% endfor %}
            {% endstrip %}
        };

        static const pwm_conf_t pwm_config[] = {
            {% strip 2 %}
                {% for pwm in peripherals.pwm %}
                    {
                        .dev = {{ pwm.peripheral }},
                        .cmu = cmuClock_{{ pwm.peripheral }},
                        .irq = {{ pwm.peripheral }}_IRQn,
                        .channels = {{ pwm.channels|length }},
                        .channel = pwm_channel_config
                    }{{ "," if not loop.last }}
                {% endfor %}
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
        {% for spi in peripherals.spi %}
            {
                .dev = {{ spi.peripheral }},
                .mosi_pin = {{ spi.mosi_pin|riot }},
                .miso_pin = {{ spi.miso_pin|riot }},
                .clk_pin = {{ spi.clk_pin|riot }},
                {% strip 2 %}
                    {% if cpu_series == 0 %}
                        .loc = {{ spi.loc }},
                    {% elif cpu_series == 1 %}
                        {% strip 2 %}
                            {% if spi.miso_loc %}
                                .loc = {{ spi.mosi_loc }} |
                                       {{ spi.miso_loc }} |
                                       {{ spi.clk_loc }},
                            {% else %}
                                .loc = {{ spi.mosi_loc }} |
                                       {{ spi.clk_loc }},
                            {% endif %}
                        {% endstrip %}
                    {% endif %}
                {% endstrip %}
                .cmu = cmuClock_{{ spi.peripheral }},
                {% strip 2 %}
                    {% if family in ["efm32tg11b"] %}
                        .irq = {{ spi.peripheral }}_IRQn
                    {% else %}
                        .irq = {{ spi.peripheral }}_RX_IRQn
                    {% endif %}
                {% endstrip %}
            }{{ "," if not loop.last }}
        {% endfor %}
    {% endstrip %}
};

#define SPI_NUMOF           ARRAY_SIZE(spi_config)
/** @} */

/**
 * @name    Timer configuration
 *
{% strip 2 %}
    {% if peripherals.timer|find(timer="^LETIMER") %}
          * The implementation can use one low-energy timer
          * or two regular timers in cascade mode.
    {% else %}
         * The implementation uses two timers in cascade mode.
    {% endif %}
{% endstrip %}
 * @{
 */
static const timer_conf_t timer_config[] = {
    {% strip 2 %}
        {% for timer in peripherals.timer %}
            {
                .prescaler = {
                    .dev = {{ timer.prescaler }},
                    {% strip 2 %}
                        {% if timer.prescaler == "NULL" %}
                            .cmu = cmuClock_{{ timer.timer }}
                        {% else %}
                            .cmu = cmuClock_{{ timer.prescaler }}
                        {% endif %}
                    {% endstrip %}
                },
                .timer = {
                    .dev = {{ timer.timer }},
                    .cmu = cmuClock_{{ timer.timer }}
                },
                .irq = {{ timer.timer }}_IRQn,
                .channel_numof = {{ timer.channels }}
            }{{ "," if not loop.last }}
        {% endfor %}
    {% endstrip %}
};

#define TIMER_NUMOF         ARRAY_SIZE(timer_config)
{% strip 2 %}
    {% for timer in peripherals.timer %}
        #define TIMER_{{ loop.index0 }}_ISR         isr_{{ timer.timer|lower }}
    {% endfor %}
{% endstrip %}
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {% strip 2 %}
        {% for uart in peripherals.uart %}
            {
                .dev = {{ uart.peripheral }},
                .rx_pin = {{ uart.rx_pin|riot }},
                .tx_pin = {{ uart.tx_pin|riot }},
                {% strip 2 %}
                    {% if cpu_series == 0 %}
                        .loc = {{ uart.loc }},
                    {% elif cpu_series == 1 %}
                        .loc = {{ uart.rx_loc }} |
                               {{ uart.tx_loc }},
                    {% endif %}
                {% endstrip %}
                .cmu = cmuClock_{{ uart.peripheral }},
                {% strip 2 %}
                    {% if "LEUART" in uart.peripheral %}
                        .irq = {{ uart.peripheral }}_IRQn
                    {% elif family in ["efm32tg11b"] %}
                        .irq = {{ uart.peripheral }}_IRQn
                    {% else %}
                        .irq = {{ uart.peripheral }}_RX_IRQn
                    {% endif %}
                {% endstrip %}
            }{{ "," if not loop.last }}
        {% endfor %}
    {% endstrip %}
};

#define UART_NUMOF          ARRAY_SIZE(uart_config)
{% strip 3 %}
    {% for uart in peripherals.uart %}
        {% if "LEUART" in uart.peripheral %}
            #define UART_{{ loop.index0 }}_ISR_RX       isr_{{ uart.peripheral|lower }}
        {% elif family in ["efm32tg11b"] %}
            #define UART_{{ loop.index0 }}_ISR_RX       isr_{{ uart.peripheral|lower }}
        {% else %}
            #define UART_{{ loop.index0 }}_ISR_RX       isr_{{ uart.peripheral|lower }}_rx
        {% endif %}
    {% endfor %}
{% endstrip %}
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
