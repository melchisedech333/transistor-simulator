
/**
 * I Love Jesus <3
 */

#include "headers.h"
#include "transistor.h"
#include "logic-port.h"

int main (int argc, char *argv[])
{
    logic_port_t *port = create_port(PORT_XOR);

    printf("type: %d\n", port->type);

    return 0;
}



