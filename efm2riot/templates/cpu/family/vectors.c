/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
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
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include <stdint.h>
#include "vectors_cortexm.h"

/* get the start of the ISR stack as defined in the linkerscript */
extern uint32_t _estack;

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void)
{
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
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    {% strip 3 %}
        {% for irq in irqs %}
            {% if irq.reserved %}
                (0UL),                  /* Reserved */
            {% else %}
                {{ (irq.method_name ~ ",")|align(23) }} /* {{ irq.number }} - {{ irq.name }} */
            {% endif %}
        {% endfor %}
    {% endstrip %}
};
