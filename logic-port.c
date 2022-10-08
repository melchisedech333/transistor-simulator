
#include "logic-port.h"

static logic_port_t *create_item (void);

logic_port_t *create_port (int type)
{
    logic_port_t *port = create_item();

    port->type = type;

    return port;
}

static logic_port_t *create_item (void)
{
    logic_port_t *port = (logic_port_t *) malloc (sizeof(logic_port_t));

    if (!port) {
        printf("Error alloc memory.\n");
        exit(-1);
    }

    memset(port, 0, sizeof(logic_port_t));

    port->type   = 0;
    port->input1 = 0;
    port->input2 = 0;
    port->output = 0;

    return port;
}


