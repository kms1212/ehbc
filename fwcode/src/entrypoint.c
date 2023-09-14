#include "types.h"

void _start() {
    smc_init();

    

    smc_sysreset();
    while (1) {}
}