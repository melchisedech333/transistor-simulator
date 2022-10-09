
#ifndef _H_LOGIC_PORT_
#define _H_LOGIC_PORT_

#include "headers.h"
#include "transistor.h"

#define GATE_NOT 1

typedef struct gate_s {
    
    // Port settings.
    int type;
    int input1;
    int input2;
    int output;

    transistor_t *transistors;

} gate_t;

gate_t *create_gate (int type);

#endif

