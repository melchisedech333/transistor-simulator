
#ifndef _H_DEBUG_
#define _H_DEBUG_

#include "headers.h"
#include "gate.h"

/**
 * 0 = Disabled.
 * 1 = Full debug information.
 * 2 = Minimal debug information;
 */

#define DEBUG_MODE 2

void run_debug_mode (gate_t *gate);
void run_debug_mode_minimal (gate_t *gate);

#endif


