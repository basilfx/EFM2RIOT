/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Power management peripheral test.
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "periph/pm.h"
#include "shell.h"

static int cmd_pm(int argc, char **argv);
static int cmd_off(int argc, char **argv);
static int cmd_reboot(int argc, char **argv);

/**
 * @brief   List of shell commands for this example.
 */
static const shell_command_t shell_commands[] = {
    { "pm", "enter PM0 mode", cmd_pm },
    { "off", "enter PM1 mode", cmd_off },
    { "reboot", "enter PM2 mode", cmd_reboot },
    { NULL, NULL, NULL }
};

static int cmd_pm(int argc, char **argv)
{
    if (argc != 1) {
        puts("Power mode expected.");
        return 1;
    }

    int mode = atoi(argv[0]);

    if (mode < 0 || mode > PM_NUM_MODES) {
        puts("Value not in range 0 - %d", PM_NUM_MODES);
        return 1;
    }

    puts("MCU will enter %d", mode);

    pm_set(mode);

    return 0;
}

static int cmd_off(int argc, char **argv)
{
    puts("MCU will turn off.");

    pm_off();

    return 0;
}

static int cmd_reboot(int argc, char **argv)
{
    puts("MCU will reboot.");

    pm_reboot();

    return 0;
}

int main(void)
{
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    /* print some information about the modes */
    puts("This test allows you to force RIOT-OS into a power modes. "
         "The power modes are 0 - %d. Lower-numbered power modes may "
         "require a certain event/interrupt before the MCU wakes up.",
         PM_NUM_MODES);

    /* run the shell and wait for the user to enter a mode */
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
