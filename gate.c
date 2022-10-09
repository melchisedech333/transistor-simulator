
#include "gate.h"

static gate_t *create_item (void);
static gate_t *create_not_gate (void);
static gate_t *create_nand_gate (void);
static gate_t *create_xor_gate (void);

gate_t *create_gate(int type)
{
    switch (type) {
        case GATE_NOT:
            return create_not_gate();
            break;

        case GATE_NAND:
            return create_nand_gate();
            break;

        case GATE_XOR:
            return create_xor_gate();
            break;
    }

    printf("Error creating gate.\n");
    exit(0);
}

void reset_gate (gate_t *gate)
{
    if (!gate)
        return;
        
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

    if (gate->subgate) {
        for (int a=0; a<gate->subcount; a++) {
            switch (a) {
                case 0: reset_gate(gate->sub1); break;
                case 1: reset_gate(gate->sub2); break;
                case 2: reset_gate(gate->sub3); break;
                case 3: reset_gate(gate->sub4); break;
            }
        }
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
    gate->subgate       = 0;
    gate->subcount      = 0;
    gate->vdd           = 0;
    gate->ground        = 0;
    gate->transistors   = NULL;
    gate->wires         = NULL;
    gate->sub1          = NULL;
    gate->sub2          = NULL;
    gate->sub3          = NULL;
    gate->sub4          = NULL;

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

static gate_t *create_xor_gate (void)
{
    gate_t *gate = create_item();

    gate->type        = GATE_XOR;
    gate->transistors = NULL;
    gate->wires       = create_wire();
    gate->subgate     = 1;
    gate->subcount    = 4;

    gate->sub1 = create_nand_gate();
    gate->sub2 = create_nand_gate();
    gate->sub3 = create_nand_gate();
    gate->sub4 = create_nand_gate();

    // Control of VDD/Volts.
    add_wire(GATE_PIN_VDD, 0, GATE_SUB1_VDD, 0);
    add_wire(GATE_PIN_VDD, 0, GATE_SUB2_VDD, 0);
    add_wire(GATE_PIN_VDD, 0, GATE_SUB3_VDD, 0);
    add_wire(GATE_PIN_VDD, 0, GATE_SUB4_VDD, 0);

    // Gates connections.
    add_wire(GATE_PIN_INPUT1, 0, GATE_SUB1_INPUT1, 0);
    add_wire(GATE_PIN_INPUT2, 0, GATE_SUB1_INPUT2, 0);
    add_wire(GATE_PIN_INPUT1, 0, GATE_SUB2_INPUT1, 0);
    add_wire(GATE_PIN_INPUT2, 0, GATE_SUB3_INPUT2, 0);

    add_wire(GATE_SUB1_OUTPUT, 0, GATE_SUB2_INPUT2, 0);
    add_wire(GATE_SUB1_OUTPUT, 0, GATE_SUB3_INPUT1, 0);

    add_wire(GATE_SUB2_OUTPUT, 0, GATE_SUB4_INPUT1, 0);
    add_wire(GATE_SUB3_OUTPUT, 0, GATE_SUB4_INPUT2, 0);

    add_wire(GATE_SUB4_OUTPUT, 0, GATE_PIN_OUTPUT, 0);

    // Get Ground value.
    add_wire(GATE_PIN_GROUND, 0, GATE_SUB1_GROUND, 0);
    add_wire(GATE_PIN_GROUND, 0, GATE_SUB2_GROUND, 0);
    add_wire(GATE_PIN_GROUND, 0, GATE_SUB3_GROUND, 0);
    add_wire(GATE_PIN_GROUND, 0, GATE_SUB4_GROUND, 0);

    remove_first_wire();
    return gate;
}

char *get_gate_name (int type)
{
    char *strs []= {
        "Iesus Hominum Salvator <3",
        "NOT-GATE",
        "NAND-GATE",
        "XOR-GATE",
        NULL
    };

    return strs[type];
}


