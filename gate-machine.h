
#ifndef _H_GATE_MACHINE_
#define _H_GATE_MACHINE_

#include "headers.h"
#include "gate-construction.h"
#include "debug.h"

#define set_sub(VAR)                                                           \
    VAR = (w->input_id == GATE_PIN_INPUT1) ? gate->input1 : gate->input2

#define attr_transistor_input(ITEM)                                            \
    do {                                                                       \
        switch (w->input_id) {                                                 \
            case GATE_SUB1_OUTPUT:                                             \
                if (gate->sub1->output)                                        \
                    ITEM = gate->sub1->output;                                 \
                break;                                                         \
            case GATE_SUB2_OUTPUT:                                             \
                if (gate->sub2->output)                                        \
                    ITEM = gate->sub2->output;                                 \
                break;                                                         \
            case GATE_SUB3_OUTPUT:                                             \
                if (gate->sub3->output)                                        \
                    ITEM = gate->sub3->output;                                 \
                break;                                                         \
            case GATE_SUB4_OUTPUT:                                             \
                if (gate->sub4->output)                                        \
                    ITEM = gate->sub4->output;                                 \
                break;                                                         \
        }                                                                      \
    } while (0)

void process_gate (gate_t *gate);

#endif


