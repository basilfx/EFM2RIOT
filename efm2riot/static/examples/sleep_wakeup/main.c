/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Sleep with periodic wakeup via RTT.  The RTT is used to wakeup
 *              the MCU from EM2 (sleep mode).
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "lpm.h"

#include "periph/rtt.h"

/**
 * @brief   Wakeup interval (in seconds).
 */
#define INTERVAL (10U)

int main(void)
{
    uint32_t timeout;

    /* prepare timer */
    rtt_init();

    while (true) {
        /* schedule alarm */
        timeout = rtt_get_counter() + (INTERVAL * RTT_FREQUENCY);
        rtt_set_alarm(timeout, NULL, 0);

        /* say bye-bye */
        printf("I will sleep until %lu.\n", timeout);
        fflush(stdout);

        /* go to sleep */
        lpm_arch_set(LPM_SLEEP);

        /* say hello */
        printf("I woke up at %lu.\n", rtt_get_counter());
        fflush(stdout);
    }

    return 0;
}
