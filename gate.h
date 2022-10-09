
#ifndef _H_LOGIC_PORT_
#define _H_LOGIC_PORT_

#include "headers.h"
#include "transistor.h"

#define GATE_NOT 1

/**
 * Gate input/output id:
 * 
 *  1 = -1 -> output
 *  2 = -2 -> input1
 *  3 = -3 -> input2
 *  N = -N -> inputN
 */

typedef struct wire_s {
    int input_id;       // Transistor ID.
    int input_pin;      // Transistor PIN:
                        //  Gate..: 1
                        //  Drain.: 2
                        //  Source: 3
    int output_id;
    int output_pin;

    struct wire_s *next;    
} wire_t;

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


