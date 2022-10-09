
#include "gate.h"

static gate_t *create_item (void);
static gate_t *create_not_gate (void);

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

    gate->type   = 0;
    gate->input1 = 0;
    gate->input2 = 0;
    gate->output = 0;

    return gate;
}

static gate_t *create_not_gate (void)
{
    gate_t *gate = create_item();

    gate->type        = GATE_NOT;
    gate->transistors = get_transistors(1, 1);

    return gate;
}


