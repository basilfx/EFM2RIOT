/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Low-level ADC driver implementation
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "cpu.h"
#include "mutex.h"

#include "periph_conf.h"
#include "periph/adc.h"

#include "em_cmu.h"
#include "em_adc.h"

static mutex_t adc_lock[ADC_NUMOF] = {
#if ADC_0_EN
    [0] = MUTEX_INIT,
#endif
#if ADC_1_EN
    [1] = MUTEX_INIT,
#endif
};

int adc_init(adc_t line)
{
    /* check if line is valid */
    if (line >= ADC_NUMOF) {
        return -1;
    }

    uint8_t dev = adc_channel_config[line].dev;

    /* enable clock */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(adc_config[dev].cmu, true);

    /* reset and initialize peripheral */
    ADC_Init_TypeDef init = ADC_INIT_DEFAULT;

    init.timebase = ADC_TimebaseCalc(0);
    init.prescale = ADC_PrescaleCalc(400000, 0);

    ADC_Reset(adc_config[dev].dev);
    ADC_Init(adc_config[dev].dev, &init);

    return 0;
}

int adc_sample(adc_t line, adc_res_t res)
{
    uint8_t dev = adc_channel_config[line].dev;

    /* lock device */
    mutex_lock(&adc_lock[dev]);

    /* setup channel */
    ADC_InitSingle_TypeDef init = ADC_INITSINGLE_DEFAULT;

    init.acqTime = adc_channel_config[line].acq_time;
    init.reference = adc_channel_config[line].reference;
    init.resolution = (ADC_Res_TypeDef) (res & 0xFF);
#ifdef _SILICON_LABS_32B_PLATFORM_1
    init.input = adc_channel_config[line].input;
#else
    init.posSel = adc_channel_config[line].input;
#endif

    ADC_InitSingle(adc_config[dev].dev, &init);

    /* start conversion and block until it completes */
    ADC_Start(adc_config[dev].dev, adcStartSingle);

    while (adc_config[dev].dev->STATUS & ADC_STATUS_SINGLEACT);

    int result = ADC_DataSingleGet(adc_config[dev].dev);

    /* for resolutions that are not really supported, shift the result (for
       instance, 10 bit resolution is achieved by shifting a 12 bit sample). */
    result = result >> (res >> 4);

    /* unlock device */
    mutex_unlock(&adc_lock[dev]);

    return result;
}
