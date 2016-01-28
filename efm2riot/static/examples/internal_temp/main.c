/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Internal temperature test application for EFM32 boards
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "cpu.h"
#include "board.h"
#include "xtimer.h"

#include "periph/adc.h"

#define DELAY           (250 * 1000U)

int main(void)
{
    /* initialize ADC */
    if (adc_init(ADC_0, ADC_RES_12BIT) != 0) {
        puts("Unable to initialize ADC, aborting.\n");
        return 1;
    }

    /* factory calibration values */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    float cal_temp = ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    uint32_t cal_value = ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_TEMP1V25_MASK) >> _DEVINFO_ADC0CAL2_TEMP1V25_SHIFT);
#else
    float cal_temp = ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    uint32_t cal_value = ((DEVINFO->ADC0CAL3 & 0xFFF0) >> _DEVINFO_ADC0CAL3_TEMPREAD1V25_SHIFT);
#endif

    while (1) {
        /* convert temperature channel */
        uint32_t value = adc_sample(ADC_0, 0);

        /* convert sample to temperature (taken from sample code) */
        int32_t diff = cal_value - value;

#ifdef _SILICON_LABS_32B_PLATFORM_1
        float temperature = cal_temp - ((float) diff / -6.27);
#else
        float temperature = cal_temp - ((float) diff * 1250) / (4096 * -1.835);
#endif

        /* print the results */
        printf("Temperature: %d.%d degrees celsius\n",
            (int) temperature, (int) (temperature * 100) % 100);

        /* sleep a little while */
        xtimer_usleep(DELAY);
    }

    return 0;
}
