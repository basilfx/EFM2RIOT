/*
 * Copyright (C) 2016-2017 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efm32_common
 * @ingroup     drivers_periph_hwcrypto
 * @{
 *
 * @file
 * @brief       Low-level hardware cyrpto driver implementation
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 * @}
 */

#include <string.h>

#include "mutex.h"
#include "assert.h"

#include "periph_conf.h"
#include "periph/hwcrypto.h"

#include "em_cmu.h"
#include "em_aes.h"

#ifdef _SILICON_LABS_32B_PLATFORM_1

/**
 * @brief   Global lock to ensure mutual exclusive access to crypto hardware.
 */
static mutex_t hwcrypto_lock = MUTEX_INIT;

/**
 * @brief   Increment 128-bit counter.
 */
static void hwcrypto_cipher_increment(uint8_t* ctr)
{
    uint64_t* hi = (uint64_t*) ctr[0];
    uint64_t* lo = (uint64_t*) ctr[8];

    if (*lo == UINT64_MAX && *hi == UINT64_MAX) {
        *lo = 0;
        *hi = 0;
    } else if (*lo == UINT64_MAX) {
        *lo = 0;
        *hi = *hi + 1;
    } else {
        *lo = *lo + 1;
    }
}

int hwcrypto_init(void)
{
    /* enable clocks */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_AES, true);

    return 0;
}

int hwcrypto_cipher_init(hwcrypto_cipher_context_t* context, hwcrypto_cipher_t cipher, hwcrypto_mode_t mode)
{
#ifdef AES_CTRL_AES256
    if (cipher != HWCRYPTO_AES128 && cipher != HWCRYPTO_AES256) {
        /* cipher not supported */
        return -1;
    }
#else
    if (cipher != HWCRYPTO_AES128) {
        /* cipher not supported */
        return -1;
    }
#endif

    context->cipher = cipher;
    context->mode = mode;

    return 0;
}

int hwcrypto_cipher_set(hwcrypto_cipher_context_t* context, hwcrypto_opt_t option, const void* value, uint32_t size)
{
    if (context->cipher == HWCRYPTO_AES128) {
        hwcrypto_cipher_aes128_context_t* aes128_context = (hwcrypto_cipher_aes128_context_t *) context;

        if (option == HWCRYPTO_OPT_KEY) {
            if (size != 16) {
                /* incorrect key size */
                return -2;
            }

            memcpy(aes128_context->key, value, 16);
        } else if (option == HWCRYPTO_OPT_IV) {
            if (size != 16) {
                /* incorrect iv size */
                return -2;
            }

            memcpy(aes128_context->iv, value, 16);
        } else if (option == HWCRYPTO_OPT_COUNTER) {
            if (size != 16) {
                /* incorrect counter size */
                return -2;
            }

            memcpy(aes128_context->counter, value, 16);
        } else {
            return -1;
        }
#ifdef AES_CTRL_AES256
    } else if (context->cipher == HWCRYPTO_AES256) {
        hwcrypto_cipher_aes256_context_t* aes256_context = (hwcrypto_cipher_aes256_context_t *) context;

        if (option == HWCRYPTO_OPT_KEY) {
            if (size != 32) {
                /* incorrect key size */
                return -2;
            }

            memcpy(aes256_context->key, value, 32);
        } else if (option == HWCRYPTO_OPT_IV) {
            if (size != 16) {
                /* incorrect iv size */
                return -2;
            }

            memcpy(aes256_context->iv, value, 16);
        } else if (option == HWCRYPTO_OPT_COUNTER) {
            if (size != 16) {
                /* incorrect counter size */
                return -2;
            }

            memcpy(aes256_context->counter, value, 16);
        } else {
            return -1;
        }
#endif
    } else {
        return -1;
    }

    return 0;
}

static int hwcrypto_cipher_encrypt_decrypt(hwcrypto_cipher_context_t* context, const uint8_t *plain_block, uint8_t *cipher_block, uint32_t block_size, bool encrypt)
{
    /* blocks must be aligned */
    assert(!((intptr_t) plain_block & 0x03));
    assert(!((intptr_t) cipher_block & 0x03));

    if (context->cipher == HWCRYPTO_AES128) {
        hwcrypto_cipher_aes128_context_t* aes128_context = (hwcrypto_cipher_aes128_context_t*) context;

        if ((block_size % 16) != 0) {
            /* invalid block size */
            return -2;
        }

        if (aes128_context->mode == HWCRYPTO_MODE_ECB) {
            AES_ECB128(cipher_block, plain_block, block_size, aes128_context->key, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CBC) {
            AES_CBC128(cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CFB) {
            AES_CFB128(cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_OFB) {
            AES_OFB128(cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CTR) {
            AES_CTR128(cipher_block, plain_block, block_size, aes128_context->key, aes128_context->counter, hwcrypto_cipher_increment);
        } else {
            return -1;
        }
#ifdef AES_CTRL_AES256
    } else if (context->cipher == HWCRYPTO_AES256) {
        hwcrypto_cipher_aes256_context_t* aes256_context = (hwcrypto_cipher_aes256_context_t*) context;

        if ((block_size % 16) != 0) {
            /* invalid block size */
            return -2;
        }

        if (aes256_context->mode == HWCRYPTO_MODE_ECB) {
            AES_ECB256(cipher_block, plain_block, block_size, aes256_context->key, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CBC) {
            AES_CBC256(cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CFB) {
            AES_CFB256(cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_OFB) {
            AES_OFB256(cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CTR) {
            AES_CTR256(cipher_block, plain_block, block_size, aes256_context->key, aes256_context->counter, hwcrypto_cipher_increment);
        } else {
            return -1;
        }
#endif
    } else {
        return -1;
    }

    return block_size;
}

int hwcrypto_cipher_encrypt(hwcrypto_cipher_context_t* context, const uint8_t *plain_block, uint8_t *cipher_block, uint32_t block_size)
{
    return hwcrypto_cipher_encrypt_decrypt(context, plain_block, cipher_block, block_size, true);
}

int hwcrypto_cipher_decrypt(hwcrypto_cipher_context_t* context, const uint8_t *cipher_block, uint8_t *plain_block, uint32_t block_size)
{
    return hwcrypto_cipher_encrypt_decrypt(context, cipher_block, plain_block, block_size, false);
}

int hwcrypto_hash_init(hwcrypto_hash_context_t* context, hwcrypto_hash_t hash)
{
    /* not supported */
    return -1;
}

int hwcrypto_hash_update(hwcrypto_hash_context_t* context, const uint8_t* block, uint32_t block_size)
{
    /* not supported */
    return -1;
}

int hwcrypto_hash_final(hwcrypto_hash_context_t* context, uint8_t* result, uint32_t result_size)
{
    /* not supported */
    return -1;
}

int hwcrypto_acquire(void)
{
    mutex_lock(&hwcrypto_lock);

    return 0;
}

int hwcrypto_release(void)
{
    mutex_unlock(&hwcrypto_lock);

    return 0;
}

void hwcrypto_poweron(void)
{
    CMU_ClockEnable(cmuClock_AES, true);
}

void hwcrypto_poweroff(void)
{
    CMU_ClockEnable(cmuClock_AES, false);
}

#endif /* _SILICON_LABS_32B_PLATFORM_1 */
