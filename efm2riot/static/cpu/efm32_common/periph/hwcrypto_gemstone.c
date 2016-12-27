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

#define ENABLE_DEBUG    (0)
#include "debug.h"

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

int hwcrypto_cipher_init(hwcrypto_cipher_context_t* context, hwcrypto_cipher_t cipher, hwcrypto_mode_t mode)
{
    if (cipher != HWCRYPTO_AES128 && cipher != HWCRYPTO_AES256) {
        /* cipher not supported */
        return -1;
    }

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
            CRYPTO_AES_ECB128(CRYPTO, cipher_block, plain_block, block_size, aes128_context->key, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CBC) {
            CRYPTO_AES_CBC128(CRYPTO, cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CFB) {
            CRYPTO_AES_CFB128(CRYPTO, cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv, encrypt);
        } else if (aes128_context->mode == HWCRYPTO_MODE_OFB) {
            CRYPTO_AES_OFB128(CRYPTO, cipher_block, plain_block, block_size, aes128_context->key, aes128_context->iv);
        } else if (aes128_context->mode == HWCRYPTO_MODE_CTR) {
            CRYPTO_AES_CTR128(CRYPTO, cipher_block, plain_block, block_size, aes128_context->key, aes128_context->counter, NULL);
        } else {
            return -1;
        }
    } else if (context->cipher == HWCRYPTO_AES256) {
        hwcrypto_cipher_aes256_context_t* aes256_context = (hwcrypto_cipher_aes256_context_t*) context;

        if ((block_size % 16) != 0) {
            /* invalid block size */
            return -2;
        }

        if (aes256_context->mode == HWCRYPTO_MODE_ECB) {
            CRYPTO_AES_ECB256(CRYPTO, cipher_block, plain_block, block_size, aes256_context->key, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CBC) {
            CRYPTO_AES_CBC256(CRYPTO, cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CFB) {
            CRYPTO_AES_CFB256(CRYPTO, cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv, encrypt);
        } else if (aes256_context->mode == HWCRYPTO_MODE_OFB) {
            CRYPTO_AES_OFB256(CRYPTO, cipher_block, plain_block, block_size, aes256_context->key, aes256_context->iv);
        } else if (aes256_context->mode == HWCRYPTO_MODE_CTR) {
            CRYPTO_AES_CTR256(CRYPTO, cipher_block, plain_block, block_size, aes256_context->key, aes256_context->counter, NULL);
        } else {
            return -1;
        }
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
    if (hash != HWCRYPTO_SHA1 && hash != HWCRYPTO_SHA256) {
        /* hash not supported */
        return -1;
    }

    /* store hash in context */
    context->hash = hash;

    return 0;
}

int hwcrypto_hash_update(hwcrypto_hash_context_t* context, const uint8_t* block, uint32_t block_size)
{
    if (context->hash == HWCRYPTO_SHA1) {
        hwcrypto_hash_sha1_context_t* sha1_context = (hwcrypto_hash_sha1_context_t*) context;

        CRYPTO_SHA_1(CRYPTO, block, block_size, sha1_context->digest);
    } else if (context->hash == HWCRYPTO_SHA256) {
        hwcrypto_hash_sha256_context_t* sha256_context = (hwcrypto_hash_sha256_context_t*) context;

        CRYPTO_SHA_256(CRYPTO, block, block_size, sha256_context->digest);
    } else {
        /* hash not supported */
        return -1;
    }

    return block_size;
}

int hwcrypto_hash_final(hwcrypto_hash_context_t* context, uint8_t* result, uint32_t result_size)
{
    if (context->hash == HWCRYPTO_SHA1) {
        hwcrypto_hash_sha1_context_t* sha1_context = (hwcrypto_hash_sha1_context_t*) context;

        if (result_size > sizeof(CRYPTO_SHA1_Digest_TypeDef)) {
            return -2;
        }

        memcpy(result, sha1_context->digest, result_size);
    } else if (context->hash == HWCRYPTO_SHA256) {
        hwcrypto_hash_sha256_context_t* sha256_context = (hwcrypto_hash_sha256_context_t*) context;

        if (result_size > sizeof(CRYPTO_SHA256_Digest_TypeDef)) {
            return -2;
        }

        memcpy(result, sha256_context->digest, result_size);
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
