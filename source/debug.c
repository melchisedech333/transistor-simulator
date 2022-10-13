
#include "debug.h"
#include "gate-machine.h"

static void show_gate_minimal_information (gate_t *gate);

void run_debug_mode (gate_t *gate)
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
        printf("Total of sub-gates: %d\n\n", gate->subcount);

        for (int a=0; a<gate->subcount; a++) {
            printf("-> Sub-gate %d:\n\n", (a+1));

            switch (a) {
                case 0: show_gate_minimal_information(gate->sub1); break;
                case 1: show_gate_minimal_information(gate->sub2); break;
                case 2: show_gate_minimal_information(gate->sub3); break;
                case 3: show_gate_minimal_information(gate->sub4); break;
            }
        }

        printf("\nProcess transistors...\n");
        process_gate(gate);
        printf("Process finished.\n\n");
        printf("New state of transistors:\n");

        for (int a=0; a<gate->subcount; a++) {
            printf("-> Sub-gate %d:\n\n", (a+1));

            switch (a) {
                case 0: show_gate_minimal_information(gate->sub1); break;
                case 1: show_gate_minimal_information(gate->sub2); break;
                case 2: show_gate_minimal_information(gate->sub3); break;
                case 3: show_gate_minimal_information(gate->sub4); break;
            }
        }

        printf("%s:\n"
                "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
                "\tVdd...: %d\n\tGround: %d\n",
                    get_gate_name(gate->type),
                    gate->input1, gate->input2, 
                    gate->output, gate->vdd, gate->ground);

        printf("\n+++++++++++++++++++++++++++\n\n");
    }
}

static void show_gate_minimal_information (gate_t *gate)
{
    printf("gate type: %s\n", get_gate_name(gate->type));

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

    printf("\n+++++++++\n\n");
}

void run_debug_mode_minimal (gate_t *gate)
{
    process_gate(gate);

    if (gate->type == GATE_NOT) {
        printf("%s:\n"
                "\tInput1: %d\n\tOutput: %d\n"
                "\tVdd...: %d\n\tGround: %d\n",
                    get_gate_name(gate->type),
                    gate->input1, gate->output, gate->vdd, gate->ground);
    } else {
        printf("%s:\n"
                "\tInput1: %d\n\tInput2: %d\n\tOutput: %d\n"
                "\tVdd...: %d\n\tGround: %d\n",
                    get_gate_name(gate->type),
                    gate->input1, gate->input2, 
                    gate->output, gate->vdd, gate->ground);
    }

    printf("\n");
}


