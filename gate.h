
#ifndef _H_GATE_
#define _H_GATE_

#include "headers.h"
#include "transistor.h"
#include "wire.h"

/**
 * Supported gates.
 */

#define GATE_NOT             1

/**
 * Gate inteface IDs:
 * 
 *   0 -> output
 *  -1 -> input1
 *  -2 -> input2
 *  -3 -> input3
 *  -N -> inputN
 * 
 * Note: transistors use positive numbers (>=1).
 */

#define GATE_PIN_OUTPUT      0
#define GATE_PIN_INPUT1     -1
#define GATE_PIN_INPUT2     -2

typedef struct gate_s {
    int type;
    int input1;
    int input2;
    int output;

    transistor_t *transistors;
    wire_t *wires;
} gate_t;

gate_t *create_gate (int type);

#endif


