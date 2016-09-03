/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32_common
 *
 * @{
 *
 * @file
 * @brief       Low-level hardware cyrpto driver implementation for the EFM32
 *              Gemstone MCUs.
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <string.h>

#include "mutex.h"

#include "periph_conf.h"
#include "periph/hwcrypto.h"

#include "em_cmu.h"
#include "em_crypto.h"

/* guard file in case no HWCRYPTO device is defined */
#if HWCRYPTO_NUMOF
#ifdef _SILICON_LABS_32B_PLATFORM_2

/**
 * @brief   Global lock to ensure mutual exclusive access to crypto hardware.
 */
static mutex_t hwcrypto_lock = MUTEX_INIT;

int hwcrypto_init(void)
{
    /* enable clocks */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_CRYPTO, true);

    return 0;
}

int hwcrypto_cipher_init(hwcrypto_cipher_context_t* context, hwcrypto_cipher_t cipher, const uint8_t* key, uint32_t key_size)
{
    if (cipher == HWCRYPTO_AES128) {
        if (key_size != 16) {
            return -2;
        }

        memcpy(context->key, key, key_size);
    } else if (cipher == HWCRYPTO_AES256) {
        if (key_size != 32) {
            return -2;
        }

        memcpy(context->key, key, key_size);
    } else {
        /* cipher not supported */
        return -1;
    }

    /* store cipher in context */
    context->cipher = cipher;

    return 0;
}

int hwcrypto_cipher_encrypt(hwcrypto_cipher_context_t* context, const uint8_t *plain_block, uint8_t *cipher_block, uint32_t block_size)
{
    if (context->cipher == HWCRYPTO_AES128) {
        if ((block_size % 16) != 0) {
            return -2;
        }

        CRYPTO_AES_ECB128(CRYPTO, cipher_block, plain_block, block_size, context->key, true);
    } else if (context->cipher == HWCRYPTO_AES256) {
        if ((block_size % 16) != 0) {
            return -2;
        }

        CRYPTO_AES_ECB256(CRYPTO, cipher_block, plain_block, block_size, context->key, true);
    } else {
        /* cipher not supported */
        return -1;
    }

    return block_size;
}

int hwcrypto_cipher_decrypt(hwcrypto_cipher_context_t* context, const uint8_t *cipher_block, uint8_t *plain_block, uint32_t block_size)
{
    if (context->cipher == HWCRYPTO_AES128) {
        if ((block_size % 16) != 0) {
            return -2;
        }

        CRYPTO_AES_ECB128(CRYPTO, plain_block, cipher_block, block_size, context->key, false);
    } else if (context->cipher == HWCRYPTO_AES256) {
        if ((block_size % 16) != 0) {
            return -2;
        }

        CRYPTO_AES_ECB256(CRYPTO, plain_block, cipher_block, block_size, context->key, false);
    } else {
        /* cipher not supported */
        return -1;
    }

    return block_size;
}

int hwcrypto_hash_init(hwcrypto_hash_context_t* context, hwcrypto_hash_t hash)
{
    /* store hash in context */
    context->hash = hash;

    return 0;
}

int hwcrypto_hash_update(hwcrypto_hash_context_t* context, const uint8_t* block, uint32_t block_size)
{
    if (context->hash == HWCRYPTO_SHA1) {
        CRYPTO_SHA_1(CRYPTO, block, block_size, context->digest);
    } else if (context->hash == HWCRYPTO_SHA256) {
        CRYPTO_SHA_256(CRYPTO, block, block_size, context->digest);
    } else {
        /* hash not supported */
        return -1;
    }

    return block_size;
}

int hwcrypto_hash_final(hwcrypto_hash_context_t* context, uint8_t* result, uint32_t result_size)
{
    if (context->hash == HWCRYPTO_SHA1) {
        if (result_size > sizeof(CRYPTO_SHA1_Digest_TypeDef)) {
            return -2;
        }

        memcpy(result, context->digest, result_size);
    } else if (context->hash == HWCRYPTO_SHA256) {
        if (result_size > sizeof(CRYPTO_SHA256_Digest_TypeDef)) {
            return -2;
        }

        memcpy(result, context->digest, result_size);
    } else {
        /* hash not supported */
        return -1;
    }

    return result_size;
}

int hwcrypto_acquire(void)
{
    mutex_lock((mutex_t *) &hwcrypto_lock);

    return 0;
}

int hwcrypto_release(void)
{
    mutex_unlock((mutex_t *) &hwcrypto_lock);

    return 0;
}

void hwcrypto_poweron(void)
{
    CMU_ClockEnable(cmuClock_CRYPTO, true);
}

void hwcrypto_poweroff(void)
{
    CMU_ClockEnable(cmuClock_CRYPTO, false);
}

#endif /* _SILICON_LABS_32B_PLATFORM_2 */
#endif /* HWCRYPTO_NUMOF */
