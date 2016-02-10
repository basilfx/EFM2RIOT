/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
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
 * @brief       Low-level timer driver implementation
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "cpu.h"
#include "sched.h"
#include "thread.h"

#include "periph/timer.h"
#include "periph_conf.h"

#include "em_cmu.h"
#include "em_timer.h"

/* guard file in case no TIMER device is defined */
#if TIMER_NUMOF

/**
 * @brief   This timer implementation has three available channels
 */
#define CC_CHANNELS      (3U)

/**
 * @brief   Timer state memory
 */
static timer_isr_ctx_t isr_ctx[TIMER_NUMOF];

int timer_init(tim_t dev, unsigned int ticks_per_us, void (*callback)(int))
{
    TIMER_TypeDef *pre, *tim;

    /* test if given timer device is valid */
    if (dev >= TIMER_NUMOF) {
        return -1;
    }

    /* save callback */
    isr_ctx[dev].cb = callback;

    /* get timers */
    pre = timer_config[dev].prescaler.dev;
    tim = timer_config[dev].timer.dev;

    /* enable clocks */
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(timer_config[dev].prescaler.cmu, true);
    CMU_ClockEnable(timer_config[dev].timer.cmu, true);

    /* reset both timers */
    TIMER_Reset(tim);
    TIMER_Reset(pre);

    /* configure the prescaler top value */
    uint32_t freq = CMU_ClockFreqGet(timer_config[dev].prescaler.cmu);
    uint32_t top = ((freq / 32 / 1000000) - 1) * ticks_per_us;

    TIMER_TopSet(pre, top);
    TIMER_TopSet(tim, 0xffff);

    /* enable interrupts for the channels */
    TIMER_IntClear(tim, TIMER_IFC_CC0 | TIMER_IFC_CC1 | TIMER_IFC_CC2);
    TIMER_IntEnable(tim, TIMER_IEN_CC0 | TIMER_IEN_CC1 | TIMER_IEN_CC2);

    NVIC_ClearPendingIRQ(timer_config[dev].irq);
    NVIC_EnableIRQ(timer_config[dev].irq);

    /* initialize and enable peripherals */
    TIMER_Init_TypeDef init_pre = TIMER_INIT_DEFAULT;
    TIMER_Init_TypeDef init_tim = TIMER_INIT_DEFAULT;

    init_pre.prescale = timerPrescale32;
    init_tim.clkSel = timerClkSelCascade;

    TIMER_Init(tim, &init_tim);
    TIMER_Init(pre, &init_pre);

    return 0;
}

int timer_set(tim_t dev, int channel, unsigned int timeout)
{
    return timer_set_absolute(dev, channel, timer_read(dev) + timeout);
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
    TIMER_TypeDef *tim;

    if (channel < 0 || channel >= CC_CHANNELS) {
        return -1;
    }

    if (value > 0xffff) {
        return -1;
    }

    tim = timer_config[dev].timer.dev;
    tim->CC[channel].CCV = (uint16_t)value;
    tim->CC[channel].CTRL = TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;

    return 0;
}

int timer_clear(tim_t dev, int channel)
{
    timer_config[dev].timer.dev->CC[channel].CTRL = _TIMER_CC_CTRL_MODE_OFF;
    return 0;
}

unsigned int timer_read(tim_t dev)
{
    return (unsigned int) TIMER_CounterGet(timer_config[dev].timer.dev);
}

void timer_stop(tim_t dev)
{
    TIMER_Enable(timer_config[dev].timer.dev, false);
}

void timer_start(tim_t dev)
{
    TIMER_Enable(timer_config[dev].timer.dev, true);
}

void timer_irq_enable(tim_t dev)
{
    NVIC_EnableIRQ(timer_config[dev].irq);
}

void timer_irq_disable(tim_t dev)
{
    NVIC_DisableIRQ(timer_config[dev].irq);
}

void timer_reset(tim_t dev)
{
    TIMER_CounterSet(timer_config[dev].timer.dev, 0);
}

#ifdef TIMER_0_ISR
void TIMER_0_ISR(void)
{
    TIMER_TypeDef *tim = timer_config[0].timer.dev;

    for (int i = 0; i < CC_CHANNELS; i++) {
        if (tim->IF & (TIMER_IF_CC0 << i)) {
            tim->CC[i].CTRL = _TIMER_CC_CTRL_MODE_OFF;
            tim->IFC = (TIMER_IFC_CC0 << i);
            isr_ctx[0].cb(i);
        }
    }
    if (sched_context_switch_request) {
        thread_yield();
    }
}
#endif /* TIMER_0_ISR */

#endif /* TIMER_NUMOF */
