
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"
#include "logic-port.h"

int main (int argc, char *argv[])
{
    gate_t *gate = create_gate(GATE_NOT);
    transistor_t *t;
    int a = 0;

    printf("port type: %d\n", gate->type);
    printf("transistors:\n");

    for (t=gate->transistors; t != NULL; t=t->next) {
        printf("\ttype: %s\n", !t->type ? "P-TYPE" : "N-TYPE");
    }

    return 0;
}



