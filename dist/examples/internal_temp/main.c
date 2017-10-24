/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
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

#define DELAY           (1000 * 1000U)

int main(void)
{
    /* initialize ADC */
    if (adc_init(0) != 0) {
        puts("Unable to initialize ADC, aborting.\n");
        return 1;
    }

    /* factory calibration values */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    float cal_temp = (float) ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    float cal_value = (float) ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_TEMP1V25_MASK) >> _DEVINFO_ADC0CAL2_TEMP1V25_SHIFT);
#else
    float cal_temp = (float) ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) >> _DEVINFO_CAL_TEMP_SHIFT);
    float cal_value = (float) ((DEVINFO->ADC0CAL3 & _DEVINFO_ADC0CAL3_TEMPREAD1V25_MASK) >> _DEVINFO_ADC0CAL3_TEMPREAD1V25_SHIFT);
#endif

    while (1) {
        /* convert temperature channel */
        int32_t value = adc_sample(0, ADC_RES_12BIT);

        /* convert sample to degrees Celsius, using the correction factors */
#ifdef _SILICON_LABS_32B_PLATFORM_1
        float temperature = cal_temp - ((cal_value - value) / -6.27);
#else
        float temperature = cal_temp - ((cal_value - value) / -6.01);
#endif

        /* print the results */
        printf("Temperature: %.2f degrees celsius\n", temperature);

        /* sleep a little while */
        xtimer_usleep(DELAY);
    }

    return 0;
}
