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
 * @brief       BMP280 board specific configuration
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef BMP280_PARAMS_H
#define BMP280_PARAMS_H

#include "board.h"
#include "saul_reg.h"
// #include "bmp280.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    BMP280 configuration
 */
static const  bmp280_params_t bmp280_params[] =
{
    {
        .i2c_dev = BMP280_I2C,
        .address = BMP280_ADDRESS
    }
};

/**
 * @brief   Additional meta information to keep in the SAUL registry.
 */
static const saul_reg_info_t bmp280_saul_reg_info[] =
{
    {
        .name = "bmp280-press",
    },
    {
        .name = "bmp280-temp",
    },
};

#ifdef __cplusplus
}
#endif

#endif /* BMP280_PARAMS_H */
/** @} */
