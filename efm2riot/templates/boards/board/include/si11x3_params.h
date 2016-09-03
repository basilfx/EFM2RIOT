/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
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
 * @brief       Si1133/Si1153 board specific configuration
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef SI11X3_PARAMS_H
#define SI11X3_PARAMS_H

#include "board.h"
#include "saul_reg.h"
// #include "si11x3.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Si11x3 configuration
 */
static const  si11x3_params_t si11x3_params[] =
{
    {
        .i2c_dev = SI1133_I2C,
        .address = SI11x3_ADDRESS_SI1133
    }
};

/**
 * @brief   Additional meta information to keep in the SAUL registry.
 */
static const saul_reg_info_t si11x3_saul_reg_info[] =
{
    {
        .name = "si11x3-uv",
    },
};

#ifdef __cplusplus
}
#endif

#endif /* SI11X3_PARAMS_H */
/** @} */
