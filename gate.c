
#include "gate.h"

static gate_t *create_item (void);
static gate_t *create_not_gate (void);
static gate_t *create_nand_gate (void);
static void prepare_gate_wires (gate_t *gate);

gate_t *create_gate(int type)
{
    switch (type) {
        case GATE_NOT:
            return create_not_gate();
        case GATE_NAND:
            return create_nand_gate();
            break;
    }

    printf("Error creating gate.\n");
    exit(0);
}

void reset_gate (gate_t *gate)
{
    gate->input1 = 0;
    gate->input2 = 0;
    gate->output = 0;
    gate->vdd    = 0;
    gate->ground = 0;

    for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
        t->gate   = 0;
        t->drain  = 0;
        t->source = 0;
    }
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
    
    remove_first_wire();
    return gate;
}

static gate_t *create_nand_gate (void)
{
    gate_t *gate = create_item();

    gate->type        = GATE_NAND;
    gate->transistors = get_transistors(2, 2);
    gate->wires       = create_wire();

    // Transistor P-TYPE 1.
    add_wire(GATE_PIN_VDD,    0, 1, PIN_TRANSISTOR_SOURCE);
    add_wire(GATE_PIN_INPUT1, 0, 1, PIN_TRANSISTOR_GATE);
    add_wire(1, PIN_TRANSISTOR_DRAIN, GATE_PIN_OUTPUT, 0);
    
    // Transistor P-TYPE 2.
    add_wire(GATE_PIN_VDD,    0, 2, PIN_TRANSISTOR_SOURCE);
    add_wire(GATE_PIN_INPUT2, 0, 2, PIN_TRANSISTOR_GATE);
    add_wire(2, PIN_TRANSISTOR_DRAIN, GATE_PIN_OUTPUT, 0);
    
    // Transistor N-TYPE 1.
    add_wire(GATE_PIN_INPUT1, 0, 3, PIN_TRANSISTOR_GATE);
    add_wire(3, PIN_TRANSISTOR_DRAIN, GATE_PIN_OUTPUT, 0);
    add_wire(3, PIN_TRANSISTOR_SOURCE, 4, PIN_TRANSISTOR_DRAIN);

    // Transistor N-TYPE 2.
    add_wire(GATE_PIN_INPUT2, 0, 4, PIN_TRANSISTOR_GATE);
    add_wire(4, PIN_TRANSISTOR_SOURCE, GATE_PIN_GROUND, 0);

    remove_first_wire();
    return gate;
}

char *get_gate_name (int type)
{
    char *strs []= {
        "Iesus Hominum Salvator <3",
        "NOT-GATE",
        "NAND-GATE",
        NULL
    };

    return strs[type];
}


