/*
 * Copyright (C) 2014-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32_common
 *
 * @{
 *
 * @file
 * @brief       Low-level SPI driver implementation
 *
 * @author      Ryan Kurte <ryankurte@gmail.com>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 * @author      Christian Amsüss <c@amsuess.com>
 *
 * @}
 */

#include "cpu.h"
#include "sched.h"
#include "thread.h"
#include "mutex.h"

#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/spi.h"

#include "em_device.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_common_utils.h"

/* guard file in case no SPI device is defined */
#if SPI_NUMOF

static mutex_t locks[SPI_NUMOF];

/*static void spi_poweron(spi_t dev)
{
    CMU_ClockEnable(spi_config[dev].cmu, true);
}

static void spi_poweroff(spi_t dev)
{
    CMU_ClockEnable(spi_config[dev].cmu, false);
}*/

void spi_init(spi_t bus)
{
    /* make sure given bus device is valid */
    assert(bus < SPI_NUMOF);

    /* initialize the lock */
    mutex_init(&locks[bus]);
}

int spi_init_master(spi_t dev, spi_conf_t conf, spi_speed_t speed)
{
    /* check if device is valid */
    if (dev >= SPI_NUMOF) {
        return -1;
    }

    /* enable clocks */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(spi_config[dev].cmu, true);

    /* initialize and enable peripheral */
    EFM32_CREATE_INIT(init, USART_InitSync_TypeDef, USART_INITSYNC_DEFAULT,
        .conf.baudrate = (uint32_t) speed,
        .conf.clockMode = (USART_ClockMode_TypeDef) conf,
        .conf.msbf = true
    );

    USART_InitSync(spi_config[dev].dev, &init.conf);

    /* initialize the pins */
    spi_init_pins(dev);

    return 0;
}

int spi_init_slave(spi_t dev, spi_conf_t conf, char (*cb)(char data))
{
    /* not (yet) supported */
    return -1;
}

void spi_init_pins(spi_t dev)
{
    /* configure the pins */
    gpio_init(spi_config[dev].clk_pin, GPIO_OUT);
    gpio_init(spi_config[dev].mosi_pin, GPIO_OUT);
    gpio_init(spi_config[dev].miso_pin, GPIO_IN_PD);

    gpio_set(spi_config[dev].clk_pin);
    gpio_set(spi_config[dev].mosi_pin);

    /* configure pin functions */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    spi_config[dev].dev->ROUTE = (spi_config[dev].loc |
                                  USART_ROUTE_RXPEN |
                                  USART_ROUTE_TXPEN |
                                  USART_ROUTE_CLKPEN);
#else
    spi_config[dev].dev->ROUTELOC0 = spi_config[dev].loc;
    spi_config[dev].dev->ROUTEPEN = (USART_ROUTEPEN_RXPEN |
                                     USART_ROUTEPEN_TXPEN |
                                     USART_ROUTEPEN_CLKPEN);
#endif
}

int spi_acquire(spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
{
    mutex_lock((mutex_t *) &locks[bus]);

    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(spi_config[bus].cmu, true);

    EFM32_CREATE_INIT(init, USART_InitSync_TypeDef, USART_INITSYNC_DEFAULT,
        .conf.baudrate = (uint32_t) clk,
        .conf.clockMode = (USART_ClockMode_TypeDef) mode,
        .conf.msbf = true
    );

    USART_InitSync(spi_config[bus].dev, &init.conf);

    /* configure the pins */
    spi_init_pins(bus);

    return SPI_OK;
}

void spi_release(spi_t dev)
{
    mutex_unlock((mutex_t *) &locks[dev]);
}

void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont,
                        const void *out, void *in, size_t len)
{
    uint8_t *out_buf = (uint8_t *)out;
    uint8_t *in_buf = (uint8_t *)in;

    if (cs != SPI_CS_UNDEF) {
        gpio_clear((gpio_t)cs);
    }

    for (size_t i = 0; i < len; i++) {
        uint8_t ret = USART_SpiTransfer(spi_config[bus].dev, out != NULL ? out_buf[i] : 0);

        if (in != NULL) {
            in_buf[i] = ret;
        }
    }

    if ((!cont) && (cs != SPI_CS_UNDEF)) {
        gpio_set((gpio_t)cs);
    }
}


void spi_transmission_begin(spi_t dev, char reset_val)
{
    return;
}

#endif /* SPI_NUMOF */
