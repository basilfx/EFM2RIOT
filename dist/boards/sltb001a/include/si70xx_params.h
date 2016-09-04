/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_sltb001a
 * @{
 *
 * @file
 * @brief       Si7006/13/20/21 board specific configuration
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef SI70XX_PARAMS_H
#define SI70XX_PARAMS_H

#include "board.h"
#include "saul_reg.h"
#include "si70xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    Si70xx configuration
 */
static const  si70xx_params_t si70xx_params[] =
{
    {
        .i2c_dev = SI7021_I2C,
        .address = SI70XX_ADDRESS_SI7021,
    }
};

/**
 * @brief   Additional meta information to keep in the SAUL registry.
 */
static const saul_reg_info_t si70xx_saul_reg_info[] =
{
    {
        .name = "si70xx-temp",
    },
    {
        .name = "si70xx-rh",
    }
};

#ifdef __cplusplus
}
#endif

#endif /* SI70XX_PARAMS_H */
/** @} */