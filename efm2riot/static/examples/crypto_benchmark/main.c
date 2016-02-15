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
 * @brief       Hardware AES vs software AES benchmark
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "periph/rtt.h"
#include "hwaes.h"

#include "crypto/ciphers.h"

volatile bool stop;

/* taken from test-crypto-modes-ecb */
static uint8_t KEY[] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};
static uint8_t KEY_LEN = 16;

static uint8_t PLAIN[] = {
    0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
    0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
};
static uint8_t PLAIN_LEN = 16;

static void cb_stop(void *arg)
{
    stop = true;
}

static uint32_t benchmark(cipher_id_t cipher_id, uint32_t duration)
{
    uint8_t data[PLAIN_LEN];
    uint32_t timeout;
    cipher_t cipher;
    uint32_t ops;

    /* setup state */
    stop = false;
    ops = 0;

    /* initialize cipher */
    cipher_init(&cipher, cipher_id, KEY, KEY_LEN);

    /* set alarm */
    timeout = rtt_get_counter() + (duration * RTT_FREQUENCY);
    rtt_set_alarm(timeout, cb_stop, 0);

    /* benchmark until alarm triggers */
    while (!stop) {
        cipher_encrypt(&cipher, PLAIN, data);
        ops++;
    }

    /* return the number of ops achieved */
    return ops;
}

int main(void)
{
    uint32_t ops;

    /* prepare ticker */
    rtt_init();

    /* run tests */
    puts("Starting benchmarks.\n");

    ops = benchmark(CIPHER_AES_128, 10);
    printf("AES: completed %lu ops in 10 seconds.\n", ops);

    ops = benchmark(CIPHER_HWAES_128, 10);
    printf("HWAES: completed %lu ops in 10 seconds.\n", ops);

    puts("Benchmarks done!\n");
}
