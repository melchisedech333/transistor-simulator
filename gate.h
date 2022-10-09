
#ifndef _H_GATE_
#define _H_GATE_

#include "headers.h"
#include "transistor.h"
#include "wire.h"

#define add_wire(INP_ID, INP_PIN, OUT_ID, OUT_PIN)                              \
    do {                                                                        \
        add_wire_item(gate->wires, INP_ID, INP_PIN, OUT_ID, OUT_PIN);           \
    } while (0)

#define first_p() get_first_transistor_id(gate->transistors, TYPE_P)
#define first_n() get_first_transistor_id(gate->transistors, TYPE_N)

/**
 * Supported gates.
 */

#define GATE_NOT             1

typedef struct gate_s {
    int type;

    // Gate interface.
    int input1;
    int input2;
    int output;

    // Circuit interface.
    int vdd;        // Voltage Drain Drain.
    int ground;

    transistor_t *transistors;
    wire_t *wires;
} gate_t;

gate_t *create_gate (int type);
char *get_gate_name (int type);

#endif


