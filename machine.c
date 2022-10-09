
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"
#include "gate.h"

int main (int argc, char *argv[])
{
    gate_t *gate = create_gate(GATE_NOT);
    
    printf("gate type: %s\n", get_gate_name(gate->type));
    printf("\ntransistors:\n");

    for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
        printf("\tid: %d, type: %s\n", t->id, !t->type ? "P-TYPE" : "N-TYPE");
    }

    printf("\nwires:\n");
    
    for (wire_t *w=gate->wires; w != NULL; w=w->next) {
        printf("\tinput id: %d, input pin: %d -> output id: %d, output pin: %d\n",
            w->input_id, w->input_pin, w->output_id, w->output_pin);
    }

    return 0;
}



