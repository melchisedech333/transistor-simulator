
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

    printf("\nOperation: %s\n", get_operation_name(device->operation));
    printf("\n\t %s\n\t %s\n", device->input1, device->input2);
    printf("\t----------\n\t%s\n\n", device->output);
    printf("Decimal: %d %c %d = %d\n\n", 
        bindec(device->input1), get_operation_op(device->operation), 
        bindec(device->input2), bindec(device->output));

    return 0;
}


