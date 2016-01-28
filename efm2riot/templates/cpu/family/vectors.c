/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_{{ family }}
 * @{
 *
 * @file
 * @brief       Startup code and interrupt vector definition
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdint.h>
#include "vectors_cortexm.h"

/* get the start of the ISR stack as defined in the linkerscript */
extern uint32_t _estack;

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void) {
    dummy_handler_default();
}

/* Cortex-{{ architecture|upper }} common interrupt vectors */
WEAK_DEFAULT void isr_svc(void);
WEAK_DEFAULT void isr_pendsv(void);
WEAK_DEFAULT void isr_systick(void);

/* Silicon Labs specific interrupt vector */
{% strip 3 %}
    {% for irq in irqs %}
        {% if not irq.reserved %}
            WEAK_DEFAULT void {{ irq.method_name }}(void);
        {% endif %}
    {% endfor %}
{% endstrip %}

/* interrupt vector table */
ISR_VECTORS const void *interrupt_vector[] = {
    /* Exception stack pointer */
    (void*) (&_estack),             /* pointer to the top of the stack */

    /* Cortex {{ architecture|upper }} handlers */
    (void*) reset_handler_default,  /* entry point of the program */
    (void*) nmi_default,            /* non maskable interrupt handler */
    (void*) hard_fault_default,     /* hard fault exception */
    {% strip 2 %}
        {% if architecture in ["m0", "m0plus"] %}
            (void*) (0UL),                  /* Reserved */
            (void*) (0UL),                  /* Reserved */
            (void*) (0UL),                  /* Reserved */
        {% else %}
            (void*) mem_manage_default,     /* memory manage exception */
            (void*) bus_fault_default,      /* bus fault exception */
            (void*) usage_fault_default,    /* usage fault exception */
        {% endif %}
    {% endstrip %}

    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) (0UL),                  /* Reserved */
    (void*) isr_svc,                /* system call interrupt, in RIOT used for
                                     * switching into thread context on boot */
    {% strip 2 %}
        {% if architecture in ["m0", "m0plus"] %}
            (void*) (0UL),                  /* Reserved */
        {% else %}
            (void*) debug_mon_default,      /* debug monitor exception */
        {% endif %}
    {% endstrip %}
    (void*) (0UL),                  /* Reserved */
    (void*) isr_pendsv,             /* pendSV interrupt, in RIOT the actual
                                     * context switching is happening here */
    (void*) isr_systick,            /* SysTick interrupt, not used in RIOT */

    /* EFM32 specific peripheral handlers */
    {% strip 3 %}
        {% for irq in irqs %}
            {% if irq.reserved %}
                (void*) (0UL),                  /* Reserved */
            {% else %}
                (void*) {{ (irq.method_name ~ ",")|align(23) }} /* {{ irq.number }} - {{ irq.name }} */
            {% endif %}
        {% endfor %}
    {% endstrip %}
};
