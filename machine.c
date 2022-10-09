
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"
#include "gate.h"

int main (int argc, char *argv[])
{
    gate_t *gate = create_gate(GATE_NOT);
    
    printf("gate type: %d\n", gate->type);
    printf("transistors:\n");

    for (transistor_t *t=gate->transistors; t != NULL; t=t->next) {
        printf("\tid: %d, type: %s\n", t->id, !t->type ? "P-TYPE" : "N-TYPE");
    }

    return 0;
}



