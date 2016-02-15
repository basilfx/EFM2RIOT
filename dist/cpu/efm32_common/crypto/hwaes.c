#include "mutex.h"

#include "hwaes.h"

#include "em_cmu.h"
#ifdef _SILICON_LABS_32B_PLATFORM_1
#include "em_aes.h"
#else
#include "em_crypto.h"
#endif

/**
 * Interface to the hardware AES cipher
 */
static const cipher_interface_t hwaes_interface = {
    AES_BLOCK_SIZE,
    AES_KEY_SIZE,
    hwaes_init,
    hwaes_encrypt,
    hwaes_decrypt
};
const cipher_id_t CIPHER_HWAES_128 = &hwaes_interface;

/**
 * @brief   Global lock for mutual exclusive access to crypto hardware.
 */
static mutex_t hwaes_lock = MUTEX_INIT;

int hwaes_init(cipher_context_t *context, const uint8_t *key, uint8_t key_size)
{
    int i = 0;

    /* prepare key */
    if (key_size < CIPHERS_MAX_KEY_SIZE) {
        /* fill up by concatenating key to as long as needed */
        for (i = 0; i < CIPHERS_MAX_KEY_SIZE; i++) {
            context->context[i] = key[(i % key_size)];
        }
    }
    else {
        for (i = 0; i < CIPHERS_MAX_KEY_SIZE; i++) {
            context->context[i] = key[i];
        }
    }

    /* enable clocks */
    CMU_ClockEnable(cmuClock_HFPER, true);
#ifdef _SILICON_LABS_32B_PLATFORM_1
    CMU_ClockEnable(cmuClock_AES, true);
#else
    CMU_ClockEnable(cmuClock_CRYPTO, true);
#endif

    return 1;
}

int hwaes_encrypt(const cipher_context_t *context, const uint8_t *plain_block,
                uint8_t *cipher_block)
{
    /* lock peripheral */
    mutex_lock((mutex_t *) &hwaes_lock);

    /* encrypt data */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    AES_ECB128(cipher_block, plain_block, 16, context->context, true);
#else
    CRYPTO_AES_ECB128(cipher_block, plain_block, 16, context->context, true);
#endif

    /* unlock peripheral */
    mutex_unlock((mutex_t *) &hwaes_lock);

    return 1;
}

int hwaes_decrypt(const cipher_context_t *context, const uint8_t *cipher_block,
                uint8_t *plain_block)
{
    /* lock peripheral */
    mutex_lock((mutex_t *) &hwaes_lock);

    /* decrypt data */
#ifdef _SILICON_LABS_32B_PLATFORM_1
    AES_ECB128(plain_block, cipher_block, 16, context->context, false);
#else
    CRYPTO_AES_ECB128(plain_block, cipher_block, 16, context->context, false);
#endif

    /* unlock peripheral */
    mutex_unlock((mutex_t *) &hwaes_lock);

    return 1;
}
