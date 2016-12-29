/*
 * Copyright (C) 2016 Bas Stottelaar
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
 * @brief       CPU specific definitions for hardware crypto peripheral
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef PERIPH_HWCRYPTO_H_
#define PERIPH_HWCRYPTO_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   AES-128 context type definition.
 */
typedef struct {
    hwcrypto_cipher_t cipher;
    hwcrypto_mode_t mode;
    uint8_t key[16] __attribute__((aligned));
    uint8_t iv[16] __attribute__((aligned));
    uint8_t counter[16] __attribute__((aligned));
} hwcrypto_cipher_aes128_context_t;

/**
 * @brief   AES-256 context type definition.
 */
typedef struct {
    hwcrypto_cipher_t cipher;
    hwcrypto_mode_t mode;
    uint8_t key[32] __attribute__((aligned));
    uint8_t iv[16] __attribute__((aligned));
    uint8_t counter[16] __attribute__((aligned));
} hwcrypto_cipher_aes256_context_t;

/**
 * @brief   SHA-1 context type definition.
 */
typedef struct {
    hwcrypto_hash_t hash;
    uint8_t digest[32] __attribute__((aligned));
} hwcrypto_hash_sha1_context_t;

/**
 * @brief   SHA-256 context type definition.
 */
typedef struct {
    hwcrypto_hash_t hash;
    uint8_t digest[32] __attribute__((aligned));
} hwcrypto_hash_sha256_context_t;

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_HWCRYPTO_H_ */
/** @} */
