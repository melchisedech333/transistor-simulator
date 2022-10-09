
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
    gate->wires       = get_wires(6);

    prepare_gate_wires(gate);

    return gate;
}

static void prepare_gate_wires (gate_t *gate)
{
    wire_t *w = gate->wires;

    for (int item=0; w != NULL; w=w->next, item++) {
        switch (item) {
            case 0:
                w->input_id   = GATE_PIN_VDD;
                w->output_id  = get_first_transistor_id(gate->transistors, TYPE_P);
                w->output_pin = PIN_TRANSISTOR_SOURCE;
                break;

            case 1:
                w->input_id   = GATE_PIN_INPUT1;
                w->output_id  = get_first_transistor_id(gate->transistors, TYPE_P);
                w->output_pin = PIN_TRANSISTOR_GATE;
                break;

            case 2:
                w->input_id  = get_first_transistor_id(gate->transistors, TYPE_P);
                w->input_pin = PIN_TRANSISTOR_DRAIN;
                w->output_id = GATE_PIN_OUTPUT;
                break;

            case 3:
                w->input_id   = GATE_PIN_INPUT1;
                w->output_id  = get_first_transistor_id(gate->transistors, TYPE_N);
                w->output_pin = PIN_TRANSISTOR_GATE;
                break;

            case 4:
                w->input_id  = get_first_transistor_id(gate->transistors, TYPE_N);
                w->input_pin = PIN_TRANSISTOR_DRAIN;
                w->output_id = GATE_PIN_OUTPUT;
                break;
            
            case 5:
                w->input_id  = get_first_transistor_id(gate->transistors, TYPE_N);
                w->input_pin = PIN_TRANSISTOR_SOURCE;
                w->output_id = GATE_PIN_GROUND;
                break;
        }
    }
}


