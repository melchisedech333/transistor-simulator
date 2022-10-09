
#include "gate.h"

static gate_t *create_item (void);
static gate_t *create_not_gate (void);
static void prepare_gate_wires (gate_t *gate);

gate_t *create_gate(int type)
{
    switch (type) {
        case GATE_NOT:
            return create_not_gate();
            break;
    }

    printf("Error creating gate.\n");
    exit(0);
}

static gate_t *create_item (void)
{
    gate_t *gate = (gate_t *) malloc (sizeof(gate_t));

    if (!gate) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(gate, 0, sizeof(gate_t));

    gate->type          = 0;
    gate->input1        = 0;
    gate->input2        = 0;
    gate->output        = 0;
    gate->transistors   = NULL;
    gate->wires         = NULL;

    return gate;
}

static gate_t *create_not_gate (void)
{
    gate_t *gate = create_item();

    gate->type        = GATE_NOT;
    gate->transistors = get_transistors(1, 1);
    gate->wires       = create_wire();

    add_wire(GATE_PIN_VDD, 0, first_p(), PIN_TRANSISTOR_SOURCE);
    add_wire(GATE_PIN_INPUT1, 0, first_p(), PIN_TRANSISTOR_GATE);
    add_wire(first_p(), PIN_TRANSISTOR_DRAIN, GATE_PIN_OUTPUT, 0);
    add_wire(GATE_PIN_INPUT1, 0, first_n(), PIN_TRANSISTOR_GATE);
    add_wire(first_n(), PIN_TRANSISTOR_DRAIN, GATE_PIN_OUTPUT, 0);
    add_wire(first_n(), PIN_TRANSISTOR_SOURCE, GATE_PIN_GROUND, 0);
    
    // Remote first item.
    wire_t *w = gate->wires;
    gate->wires = w->next;
    free(w);

    return gate;
}


