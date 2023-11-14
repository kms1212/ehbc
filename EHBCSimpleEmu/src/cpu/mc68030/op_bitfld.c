#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

DEF_OPFUNC(bitfld_bit) {
    return IE_ERR;
}

DEF_OPFUNC(bitfld_bitfld) {
    return IE_ERR;
}
