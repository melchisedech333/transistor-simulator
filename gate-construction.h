
#ifndef _H_GATE_CONSTRUCTION_
#define _H_GATE_CONSTRUCTION_

#include "headers.h"
#include "transistor-creation.h"
#include "wire-creation.h"

#define add_wire(INP_ID, INP_PIN, OUT_ID, OUT_PIN)                             \
    do {                                                                       \
        add_wire_item(gate->wires, INP_ID, INP_PIN, OUT_ID, OUT_PIN);          \
    } while (0)

#define first_p() get_first_transistor_id(gate->transistors, TYPE_P)
#define first_n() get_first_transistor_id(gate->transistors, TYPE_N)

#define remove_first_wire()                                                    \
    do {                                                                       \
        wire_t *w = gate->wires;                                               \
        gate->wires = w->next;                                                 \
        free(w);                                                               \
    } while (0)

/**
 * Supported gates.
 */

#define GATE_NOT    1
#define GATE_NAND   2
#define GATE_XOR    3
#define GATE_AND    4

typedef struct gate_s {
    int type;
    int subgate;    // Gates created using existing ones.
    int subcount;   // Number of sub-gates.

    // Gate interface.
    int input1;
    int input2;
    int output;

    // Circuit interface.
    int vdd;        // Voltage Drain Drain.
    int ground;

    transistor_t *transistors;
    wire_t *wires;

    struct gate_s *sub1;
    struct gate_s *sub2;
    struct gate_s *sub3;
    struct gate_s *sub4;
} gate_t;

gate_t *create_gate (int type);
char *get_gate_name (int type);
void reset_gate (gate_t *gate);
void run_gate (gate_t *gate);

#endif


