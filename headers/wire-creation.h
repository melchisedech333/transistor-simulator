
#ifndef _H_WIRE_CREATION_
#define _H_WIRE_CREATION_

#include "headers.h"

/**
 * Gate and transistor interface.
 * Note: transistors use positive numbers in ID (>=1).
 */

// Gate interface.
#define GATE_PIN_OUTPUT         -1
#define GATE_PIN_INPUT1         -2
#define GATE_PIN_INPUT2         -3
#define GATE_PIN_VDD            -4
#define GATE_PIN_GROUND         -5

// Transistor interface.
#define PIN_TRANSISTOR_GATE     -6
#define PIN_TRANSISTOR_SOURCE   -7
#define PIN_TRANSISTOR_DRAIN    -8

/**
 * Sub-gate interface.
 */

// Volts control.
#define GATE_SUB1_VDD           -9
#define GATE_SUB2_VDD           -10
#define GATE_SUB3_VDD           -11
#define GATE_SUB4_VDD           -12

// Ground control.
#define GATE_SUB1_GROUND        -13
#define GATE_SUB2_GROUND        -14
#define GATE_SUB3_GROUND        -15
#define GATE_SUB4_GROUND        -16

// Interfaces.
#define GATE_SUB1_INPUT1        -17
#define GATE_SUB1_INPUT2        -18
#define GATE_SUB1_OUTPUT        -19

#define GATE_SUB2_INPUT1        -20
#define GATE_SUB2_INPUT2        -21
#define GATE_SUB2_OUTPUT        -22

#define GATE_SUB3_INPUT1        -23
#define GATE_SUB3_INPUT2        -24
#define GATE_SUB3_OUTPUT        -25

#define GATE_SUB4_INPUT1        -26
#define GATE_SUB4_INPUT2        -27
#define GATE_SUB4_OUTPUT        -28

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
void add_wire_item (wire_t *wires, int input_id, int input_pin, int output_id, int output_pin);
wire_t *create_wire (void);

#endif


