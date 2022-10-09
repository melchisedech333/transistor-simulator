
#include "wire.h"

static wire_t *create_wire (void);
static void insert_wire (wire_t *wires, wire_t *n_wire);

wire_t *get_wires (int total)
{
    wire_t *wires = NULL, *wire = NULL;
    int index = 1;
    
    if (!total) {
        printf("Enter a valid number of wires.\n");
        exit(0);
    }

    if (total) {
        wires = create_wire();
        total--;
    }

    for (int a=0; a<total; a++) {
        wire = create_wire();
        insert_wire(wires, wire);
    }

    return wires;
}

static wire_t *create_wire (void)
{
    wire_t *wire = (wire_t *) malloc (sizeof(wire_t));

    if (!wire) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(wire, 0, sizeof(wire_t));

    wire->input_id   = 0;
    wire->input_pin  = 0;
    wire->output_id  = 0;
    wire->output_pin = 0;
    wire->next   = NULL;

    return wire;
}

static void insert_wire (wire_t *wires, wire_t *n_wire)
{
    wire_t *wire = wires;

    if (!wires || !n_wire) {
        printf("Invalid wire input.\n");
        exit(0);
    }

    while (1) {
        if (!wire->next) {
            wire->next = n_wire;
            break;
        }

        wire = wire->next;
    }
}





