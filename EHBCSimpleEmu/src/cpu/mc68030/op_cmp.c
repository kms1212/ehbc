#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

/**
 * @brief MC68030: Disassemble compare instructions
 * Available instructions:
 * - CMP
 * - CMP2
 * - CMPA
 * - CMPI
 * - CMPM
 * - TST
 */
DEF_OPFUNC(cmp) {
    return IE_ERR;
} 
