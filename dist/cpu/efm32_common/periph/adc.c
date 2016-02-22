/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
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

#include "periph_conf.h"
#include "periph/adc.h"

#include "em_cmu.h"
#include "em_adc.h"
#include "em_common_utils.h"

/* guard file in case no ADC device is defined */
#if ADC_NUMOF

typedef struct {
    ADC_Res_TypeDef res;
    uint32_t shift;
    uint32_t max_value;
} adc_state_t;

static adc_state_t adc_state[ADC_NUMOF];

int adc_init(adc_t dev, adc_precision_t precision)
{
    /* check if device is valid */
    if (dev >= ADC_NUMOF) {
        return -1;
    }

    /* store precision, because it is used during scan, not in init */
    switch (precision) {
        case ADC_RES_6BIT:
            adc_state[dev].res = adcRes6Bit;
            adc_state[dev].shift = 0;
            adc_state[dev].max_value = (1 << 6) - 1;
            break;
        case ADC_RES_8BIT:
            adc_state[dev].res = adcRes8Bit;
            adc_state[dev].shift = 0;
            adc_state[dev].max_value = (1 << 8) - 1;
            break;
        case ADC_RES_10BIT:
            adc_state[dev].res = adcRes12Bit;
            adc_state[dev].shift = 2;
            adc_state[dev].max_value = (1 << 12) - 1;
        case ADC_RES_12BIT:
            adc_state[dev].res = adcRes12Bit;
            adc_state[dev].shift = 0;
            adc_state[dev].max_value = (1 << 12) - 1;
            break;
        default:
            /* not supported */
            return -1;
    }

    /* enable clock */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(adc_config[dev].cmu, true);

    /* reset and initialize peripheral */
    EFM32_CREATE_INIT(init, ADC_Init_TypeDef, ADC_INIT_DEFAULT,
        .conf.timebase = ADC_TimebaseCalc(0),
        .conf.prescale = ADC_PrescaleCalc(400000, 0)
    );

    ADC_Reset(adc_config[dev].dev);
    ADC_Init(adc_config[dev].dev, &init.conf);

    return 0;
}

int adc_sample(adc_t dev, int channel)
{
    /* check if channel is valid */
    if (channel >= adc_config[dev].channels) {
        return -1;
    }

    /* setup channel */
    ADC_InitSingle_TypeDef init = ADC_INITSINGLE_DEFAULT;

    init.acqTime = adc_config[dev].channel[channel].acq_time;
    init.reference = adc_config[dev].channel[channel].reference;
    init.resolution = adc_state[dev].res;
#ifdef _SILICON_LABS_32B_PLATFORM_1
    init.input = adc_config[dev].channel[channel].input;
#else
    init.posSel = adc_config[dev].channel[channel].input;
#endif

    ADC_InitSingle(adc_config[dev].dev, &init);

    /* start conversion */
    ADC_Start(adc_config[dev].dev, adcStartSingle);

    /* wait until the ADC has warmed up */
    while (adc_config[dev].dev->STATUS & ADC_STATUS_SINGLEACT);

    /* read sample and shift it to match resolution */
    return ADC_DataSingleGet(adc_config[dev].dev) >> adc_state[dev].shift;
}

void adc_poweron(adc_t dev)
{
    CMU_ClockEnable(adc_config[dev].cmu, true);
}

void adc_poweroff(adc_t dev)
{
    CMU_ClockEnable(adc_config[dev].cmu, false);
}

int adc_map(adc_t dev, int value, int min, int max)
{
    return ((max - min) / adc_state[dev].max_value) * value;
}

float adc_mapf(adc_t dev, int value, float min, float max)
{
    return ((max - min) / ((float) adc_state[dev].max_value)) * value;
}

#endif /* ADC_NUMOF */
