#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

/**
 * @brief MC68030: Disassemble atomic instructions
 * Available instructions:
 * - CAS
 * - CAS2
 * - CHK
 * - CHK2
 * - TAS
 */
DEF_OPFUNC(atomic) {
    return IE_ERR;
} 
