
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"
#include "gate.h"

int main (int argc, char *argv[])
{
    gate_t *gate = create_gate(GATE_NOT);
    transistor_t *t;
    int a = 0;

    printf("gate type: %d\n", gate->type);
    printf("transistors:\n");

    for (t=gate->transistors; t != NULL; t=t->next) {
        printf("\tid: %d, type: %s\n", t->id, !t->type ? "P-TYPE" : "N-TYPE");
    }

    return 0;
}



