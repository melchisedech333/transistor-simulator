
#include "headers.h"
#include "utils.h"
#include "devices.h"

int initialization (void)
{
    device_arithmetic_t *device = create_device_arithmetic();
    device_arithmetic_reset(device);

    // Configure device.
    device_arithmetic_set_data(device, ARITHMETIC_INPUT1, "101");
    device_arithmetic_set_data(device, ARITHMETIC_INPUT2, "011");
    device_arithmetic_set_operation(device, ARITHMETIC_OPERATION_SUM);

    run_device_arithmetic(device);

    printf("%s + %s = %s\n", device->input1, device->input2, device->output);
    printf("%d + %d = %d\n", bindec(device->input1), bindec(device->input2), bindec(device->output));

    return 0;
}


