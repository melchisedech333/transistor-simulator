
#include "debug.h"
#include "machine.h"

void show_gate_information (gate_t *gate)
{
    printf("gate type: %s\n", get_gate_name(gate->type));
 
    // Default gate.
    if (!gate->subgate) {
        int total_transistors = 0, total_p = 0, total_n = 0;
        for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
            if (t->type == TYPE_P)
                total_p++;
            else if (t->type == TYPE_N)
                total_n++;    
            total_transistors++;
        }
            
        printf("\ntransistors: %d devices (%d P-TYPE, %d N-TYPE)\n", 
            total_transistors, total_p, total_n);
        for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
            printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
                t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

        int wire_connections = 0;
        for (wire_t *w=gate->wires; w != NULL; w=w->next) 
            wire_connections++;

        printf("\nwires: %d connections.\n", wire_connections);
        for (wire_t *w=gate->wires; w != NULL; w=w->next) 
            printf("\tinput id: %d, input pin: %d -> output id: %d, output pin: %d\n",
                w->input_id, w->input_pin, w->output_id, w->output_pin);

        printf("\nProcess transistors...\n");
        process_gate(gate);
        printf("Process finished.\n\n");
        printf("New state of transistors:\n");

        for (transistor_t *t=gate->transistors; t != NULL; t=t->next)
            printf("\tid: %d, type: %s, gate: %d, drain: %d, source: %d\n", 
                t->id, !t->type ? "P-TYPE" : "N-TYPE", t->gate, t->drain, t->source);

        printf("\n%s:\n"
                "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
                "\tVdd...: %d\n\tGround: %d\n",
                    get_gate_name(gate->type),
                    gate->input1, gate->input2, 
                    gate->output, gate->vdd, gate->ground);

        printf("\n+++++++++++++++++++++++++++\n\n");
    }

    // Subgates.
    else {
        
    }
}


