
#ifndef _H_MACHINE_
#define _H_MACHINE_

#include "headers.h"
#include "gate.h"

#define set_sub(VAR)                                                           \
    VAR = (w->input_id == GATE_PIN_INPUT1) ? gate->input1 : gate->input2

void show_gate_information (gate_t *gate);
void process_gate (gate_t *gate);

#endif


