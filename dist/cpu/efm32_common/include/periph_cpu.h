/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32_common
 * @{
 *
 * @file
 * @brief       CPU specific definitions for internal peripheral handling
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef CPU_PERIPH_H_
#define CPU_PERIPH_H_

#include "mutex.h"

#include "cpu_conf.h"

#include "em_adc.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_usart.h"
#ifdef _SILICON_LABS_32B_PLATFORM_1
#include "em_dac.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Enable support for Low-power peripherals (if supported by CPU).
 * @{
 */
#ifndef LOW_POWER_ENABLED
#define LOW_POWER_ENABLED   (1)
#endif
/** @} */

/**
 * @brief   Internal macro for combining ADC resolution (x) with number of
 *          shifts (y).
 */
#define ADC_MODE(x, y)     ((y << 4) | x)

/**
 * @brief   Possible ADC resolution settings
 * @{
 */
#define HAVE_ADC_RES_T
typedef enum {
    ADC_RES_6BIT = ADC_MODE(adcRes6Bit, 0),     /**< ADC resolution: 6 bit */
    ADC_RES_8BIT = ADC_MODE(adcRes8Bit, 0),     /**< ADC resolution: 8 bit */
    ADC_RES_10BIT = ADC_MODE(adcRes12Bit, 2),   /**< ADC resolution: 10 bit (shifted from 12 bit) */
    ADC_RES_12BIT = ADC_MODE(adcRes12Bit, 0),   /**< ADC resolution: 12 bit */
} adc_res_t;
/** @} */

/**
 * @brief   ADC device configuration
 * @{
 */
typedef struct {
    ADC_TypeDef *dev;                 /**< ADC device used */
    CMU_Clock_TypeDef cmu;            /**< the device CMU channel */
} adc_conf_t;

typedef struct {
    uint8_t dev;                      /**< device index */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    ADC_SingleInput_TypeDef input;    /**< input channel */
#else
    ADC_PosSel_TypeDef input;         /**< input channel */
#endif
    ADC_Ref_TypeDef reference;        /**< channel voltage reference */
    ADC_AcqTime_TypeDef acq_time;     /**< channel acquisition time */
} adc_chan_conf_t;
/** @} */

/**
 * @brief   Length of CPU ID in octets.
 */
#define CPUID_LEN           (8U)

/**
 * @brief   DAC device configuration
 * @{
 */
#if defined(DAC_COUNT) && DAC_COUNT > 0
typedef struct {
    DAC_TypeDef *dev;       /**< DAC device used */
    CMU_Clock_TypeDef cmu;  /**< the device CMU channel */
} dac_conf_t;

typedef struct {
    uint8_t dev;            /**< device index */
    uint8_t index;          /**< channel index */
    DAC_Ref_TypeDef ref;    /**< channel voltage reference */
} dac_chan_conf_t;
#endif
/** @} */

/**
 * @brief   Define a custom type for GPIO pins.
 * @{
 */
#define HAVE_GPIO_T
typedef uint32_t gpio_t;
/** @} */

/**
 * @brief   Definition of a fitting UNDEF value.
 */
#define GPIO_UNDEF          (0xffffffff)

/**
 * @brief   Mandatory function for defining a GPIO pins.
 */
#define GPIO_PIN(x, y)      ((gpio_t) ((x << 4) | y))

/**
 * @brief   Internal macro for combining pin mode (x) and pull-up/down (y).
 */
#define GPIO_MODE(x, y)     ((x << 1) | y)

/**
 * @brief   Available ports on the EFM32.
 */
enum {
    PA = gpioPortA,         /**< port A */
    PB = gpioPortB,         /**< port B */
    PC = gpioPortC,         /**< port C */
    PD = gpioPortD,         /**< port D */
#if _GPIO_PORT_E_PIN_COUNT
    PE = gpioPortE,         /**< port E */
#endif
    PF = gpioPortF          /**< port F */
};

/**
 * @brief   Override direction values.
 * @{
 */
#define HAVE_GPIO_MODE_T
typedef enum {
    GPIO_IN    = GPIO_MODE(gpioModeInput, 0),             /**< pin as input */
    GPIO_IN_PD = GPIO_MODE(gpioModeInputPull, 0),         /**< pin as input with pull-down */
    GPIO_IN_PU = GPIO_MODE(gpioModeInputPull, 1),         /**< pin as input with pull-up */
    GPIO_OUT   = GPIO_MODE(gpioModePushPull, 0),          /**< pin as output */
    GPIO_OD    = GPIO_MODE(gpioModeWiredAnd, 1),          /**< pin as open-drain */
    GPIO_OD_PU = GPIO_MODE(gpioModeWiredAndPullUp, 1),    /**< pin as open-drain with pull-up */
} gpio_mode_t;
/** @} */

/**
 * @brief   Override active flank configuration values.
 * @{
 */
#define HAVE_GPIO_FLANK_T
typedef enum {
    GPIO_FALLING = 2,       /**< emit interrupt on falling flank */
    GPIO_RISING = 1,        /**< emit interrupt on rising flank */
    GPIO_BOTH = 3           /**< emit interrupt on both flanks */
} gpio_flank_t;
/** @} */

/**
 * @brief   Override hardware crypto supported methods.
 * @{
 */
#define HAVE_HWCRYPTO_AES128
#define HAVE_HWCRYPTO_AES256
#ifdef _SILICON_LABS_32B_PLATFORM_2
#define HAVE_HWCRYPTO_SHA1
#define HAVE_HWCRYPTO_SHA256
#endif
/** @} */

/**
 * @brief   Override I2C speed values.
 * @{
 */
#define HAVE_I2C_SPEED_T
typedef enum {
    I2C_SPEED_LOW = 10000,            /**< low speed mode: ~10kbit/s */
    I2C_SPEED_NORMAL = 100000,        /**< normal mode: ~100kbit/s */
    I2C_SPEED_FAST = 400000,          /**< fast mode: ~400kbit/sj */
    I2C_SPEED_FAST_PLUS = 1000000,    /**< fast plus mode: ~1Mbit/s */
    I2C_SPEED_HIGH = 3400000,         /**< high speed mode: ~3.4Mbit/s */
} i2c_speed_t;
/** @} */

/**
 * @brief   I2C device configuration.
 */
typedef struct {
    I2C_TypeDef *dev;       /**< USART device used */
    gpio_t sda_pin;         /**< pin used for SDA */
    gpio_t scl_pin;         /**< pin used for SCL */
    uint32_t loc;           /**< location of I2C pins */
    CMU_Clock_TypeDef cmu;  /**< the device CMU channel */
    IRQn_Type irq;          /**< the devices base IRQ channel */
} i2c_conf_t;

/**
 * @brief   PWM device configuration.
 * @{
 */
typedef struct {
    uint8_t index;          /**< TIMER channel to use */
    gpio_t pin;             /**< pin used for pwm */
    uint32_t loc;           /**< location of the pin */
} pwm_chan_conf_t;

typedef struct {
    TIMER_TypeDef *dev;               /**< TIMER device used */
    CMU_Clock_TypeDef cmu;            /**< the device CMU channel */
    IRQn_Type irq;                    /**< the devices base IRQ channel */
    uint8_t channels;                 /**< the number of available channels */
    const pwm_chan_conf_t* channel;   /**< pointer to first channel config */
} pwm_conf_t;
/** @} */

/**
 * @brief   Override SPI clocks.
 * @{
 */
#define HAVE_SPI_CONF_T
typedef enum {
    SPI_CONF_FIRST_RISING = usartClockMode0,
    SPI_CONF_SECOND_RISING = usartClockMode1,
    SPI_CONF_FIRST_FALLING = usartClockMode2,
    SPI_CONF_SECOND_FALLING = usartClockMode3
} spi_conf_t;
/** @} */

/**
 * @brief   Define a set of pre-defined SPI clock speeds.
 * @{
 */
#define HAVE_SPI_SPEED_T
typedef enum {
    SPI_SPEED_100KHZ = 100000,        /**< drive the SPI bus with 100KHz */
    SPI_SPEED_400KHZ = 400000,        /**< drive the SPI bus with 400KHz */
    SPI_SPEED_1MHZ = 1000000,         /**< drive the SPI bus with 1MHz */
    SPI_SPEED_5MHZ = 5000000,         /**< drive the SPI bus with 5MHz */
    SPI_SPEED_10MHZ = 10000000        /**< drive the SPI bus with 10MHz */
} spi_speed_t;
/** @} */

/**
 * @brief   SPI device configuration.
 */
typedef struct {
    USART_TypeDef *dev;     /**< USART device used */
    gpio_t mosi_pin;        /**< pin used for MOSI */
    gpio_t miso_pin;        /**< pin used for MISO */
    gpio_t clk_pin;         /**< pin used for CLK */
    uint32_t loc;           /**< location of USART pins */
    CMU_Clock_TypeDef cmu;  /**< the device CMU channel */
    IRQn_Type irq;          /**< the devices base IRQ channel */
} spi_dev_t;

/**
 * @brief   Declare needed generic SPI functions.
 * @{
 */
#define PERIPH_SPI_NEEDS_TRANSFER_BYTES
#define PERIPH_SPI_NEEDS_TRANSFER_REG
#define PERIPH_SPI_NEEDS_TRANSFER_REGS
/** @} */

/**
 * @brief   Override the timer type.
 * @{
 */
#define HAVE_TIMER_T
typedef uint32_t tim_t;
/** @} */

/**
 * @brief   Override the timer undefined value.
 */
#define TIMER_UNDEF         (0xffffffff)

/**
 * @brief   Define timer configuration values
 *
 * @note    The two timers must be adjacent to each other (e.g. TIMER0 and
 *          TIMER1, or TIMER2 and TIMER3, etc.).
 * @{
 */
typedef struct {
    TIMER_TypeDef *dev;
    CMU_Clock_TypeDef cmu;
} timer_dev_t;

typedef struct {
    timer_dev_t prescaler;  /**< the lower numbered neighboring timer */
    timer_dev_t timer;      /**< the higher numbered timer */
    IRQn_Type irq;          /**< number of the higher timer IRQ channel */
} timer_conf_t;
/** @} */

/**
 * @brief   UART device configuration.
 */
typedef struct {
    void *dev;              /**< UART, USART or LEUART device used */
    gpio_t rx_pin;          /**< pin used for RX */
    gpio_t tx_pin;          /**< pin used for TX */
    uint32_t loc;           /**< location of USART pins */
    CMU_Clock_TypeDef cmu;  /**< the device CMU channel */
    IRQn_Type irq;          /**< the devices base IRQ channel */
} uart_conf_t;

#ifdef __cplusplus
}
#endif

#endif /* CPU_PERIPH_H_ */
/** @} */