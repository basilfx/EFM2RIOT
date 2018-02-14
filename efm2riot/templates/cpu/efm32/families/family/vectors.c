/*
 * Copyright (C) 2015-2018 Freie Universität Berlin
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

#include "vectors_cortexm.h"

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void)
{
    dummy_handler_default();
}

/* Silicon Labs specific interrupt vector */
{% strip 2 %}
    {% for irq in irqs %}
        WEAK_DEFAULT void {{ irq.method_name }}(void);
    {% endfor %}
{% endstrip %}

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    {% strip 2 %}
        {% for irq in irqs %}
            [{{ irq.number|ralign(2) }}] = {{ (irq.method_name ~ ",")|align(23) }} /* {{ irq.name }} */
        {% endfor %}
    {% endstrip %}
};
