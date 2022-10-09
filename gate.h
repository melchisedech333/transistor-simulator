
#ifndef _H_LOGIC_PORT_
#define _H_LOGIC_PORT_

#include "headers.h"
#include "transistor.h"

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


