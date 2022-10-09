
#ifndef _H_LOGIC_PORT_
#define _H_LOGIC_PORT_

#include "headers.h"
#include "transistor.h"

#define GATE_NOT 1

typedef struct wires_s {
    int index;
    int input;
    int output;

    struct wires_s *next;    
} wires_t;

typedef struct gate_s {
    
    // Port settings.
    int type;
    int input1;
    int input2;
    int output;

    transistor_t *transistors;
    wires_t *wires;

} gate_t;

gate_t *create_gate (int type);

#endif


