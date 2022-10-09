
#ifndef _H_GATE_
#define _H_GATE_

#include "headers.h"
#include "transistor.h"
#include "wire.h"

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
    int vdd;
    int ground;

    transistor_t *transistors;
    wire_t *wires;
} gate_t;

gate_t *create_gate (int type);

#endif


