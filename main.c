
#include "headers.h"
#include "utils.h"
#include "devices.h"
#include "gate-construction.h"

int initialization (void)
{
    device_arithmetic_t *device = create_device_arithmetic();
    device_arithmetic_reset(device);

    // Configure device.
    device_arithmetic_set_data(device, ARITHMETIC_INPUT1, "101");
    device_arithmetic_set_data(device, ARITHMETIC_INPUT2, "011");
    device_arithmetic_set_operation(device, ARITHMETIC_OPERATION_SUM);

    // Process device.
    run_device_arithmetic(device);

    // Show information.
    printf("\nOperation: %s\n\n", get_operation_name(device->operation));
    
    printf("\t BINARY     | DEC\n");
    printf("\t ----------------\n");
    printf("\t            |\n");

    printf("\t %s", device->input1);
    printf(" | %d\n", bindec(device->input1));
    printf("\t %s", device->input2);
    printf(" | %d\n", bindec(device->input2));

    printf("\t ----------------\n");
    printf("\t %s", device->output);
    printf(" | %d\n\n", bindec(device->output));

    return 0;
}


