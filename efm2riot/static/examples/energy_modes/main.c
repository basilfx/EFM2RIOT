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
 * @brief       Example for comparing different power modes via RIOT-OS API.
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdio.h>

#include "lpm.h"
#include "shell.h"

static int cmd_em0(int argc, char **argv);
static int cmd_em1(int argc, char **argv);
static int cmd_em2(int argc, char **argv);
static int cmd_em3(int argc, char **argv);
static int cmd_em4(int argc, char **argv);

/**
 * @brief   List of shell commands for this example.
 */
static const shell_command_t shell_commands[] = {
    { "em0", "enter ON mode", cmd_em0 },
    { "em1", "enter IDLE mode", cmd_em1 },
    { "em2", "enter SLEEP mode", cmd_em2 },
    { "em3", "enter POWERDOWN mode", cmd_em3 },
    { "em4", "enter OFF mode", cmd_em4 },
    { NULL, NULL, NULL }
};

static int cmd_em0(int argc, char **argv)
{
    lpm_arch_set(LPM_ON);

    return 0;
}

static int cmd_em1(int argc, char **argv)
{
    lpm_arch_set(LPM_IDLE);

    return 0;
}

static int cmd_em2(int argc, char **argv)
{
    lpm_arch_set(LPM_SLEEP);

    return 0;
}

static int cmd_em3(int argc, char **argv)
{
    lpm_arch_set(LPM_POWERDOWN);

    return 0;
}

static int cmd_em4(int argc, char **argv)
{
    lpm_arch_set(LPM_OFF);

    return 0;
}

int main(void)
{
    char line_buf[SHELL_DEFAULT_BUFSIZE];

    /* print some information about the modes */
    puts("This example allows you to put RIOT-OS into several power modes. "
         "The power modes are ON, IDLE, SLEEP, POWERDOWN and OFF. These "
         "modes map onto EM0, EM1, EM2, EM3 and EM4. Each higher-numbered "
         "mode saves more energy. Use the commands em0 - em4 to enter that "
         "mode. Higher-numbered modes require a reset to exit.");
    puts("You can connect the AEM to measure power consumption.");

    /* run the shell and wait for the user to enter a mode */
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
