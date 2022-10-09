
#ifndef _H_WIRE_
#define _H_WIRE_

#include "headers.h"

/**
 * Gate and transistor interface.
 * Note: transistors use positive numbers in ID (>=1).
 */

#define GATE_PIN_OUTPUT         -1
#define GATE_PIN_INPUT1         -2
#define GATE_PIN_INPUT2         -3
#define GATE_PIN_VDD            -4
#define GATE_PIN_GROUND         -5

#define PIN_TRANSISTOR_GATE     -6
#define PIN_TRANSISTOR_SOURCE   -7
#define PIN_TRANSISTOR_DRAIN    -8

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

wire_t *get_wires (int total);

#endif


