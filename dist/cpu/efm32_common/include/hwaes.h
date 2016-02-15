#ifndef HWAES_H
#define HWAES_H

#include "crypto/aes.h"
#include "crypto/ciphers.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const cipher_id_t CIPHER_HWAES_128;

int hwaes_init(cipher_context_t *context, const uint8_t *key, uint8_t key_size);

int hwaes_encrypt(const cipher_context_t *context, const uint8_t *plain_block,
                uint8_t *cipher_block);

int hwaes_decrypt(const cipher_context_t *context, const uint8_t *cipher_block,
                uint8_t *plain_block);

#ifdef __cplusplus
}
#endif

#endif /* HWAES_H */
