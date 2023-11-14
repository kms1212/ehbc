#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union lifmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t osz : 2;
        uint16_t dir : 1;
        uint16_t reg : 3;
        uint16_t opgrp : 4;
    };
};

/**
 * @brief MC68030: Disassemble logical or instructions
 * Available instructions:
 * - OR
 * - ORI
 * - AND
 * - ANDI
 * - EOR
 * - EORI
 * - NOT
 */
DEF_OPFUNC(logic_op) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    char eastr[20] = "";

    union lifmt lfmt = { .raw = iwd[0] };

    char szind = lut_szind[lfmt.osz];
    uint32_t ival = 0;

    ssize_t wcur16   = 1;

    if (lfmt.opgrp == 0b0000) {  // Use immediate values
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            lfmt.osz, lfmt.eamode, lfmt.eareg, wcur16,
            eastr, sizeof(eastr));
        if (wcur16 < 0) return wcur16;

        if (lfmt.osz == 2) {
            CHK_SZ(isz16, wcur16 + 2);
            ival = W2L(iwd[wcur16], iwd[wcur16 + 1]);
            wcur16 += 2;
        } else {
            CHK_SZ(isz16, wcur16 + 1);
            ival = iwd[wcur16++];
        }

        switch (ote) {
            case I_ORI:
                snprintf(buf, len, "ORI.%c #$%x, %s", szind, ival, eastr);
                break;
            case I_ANDI:
                snprintf(buf, len, "ANDI.%c #$%x, %s", szind, ival, eastr);
                break;
            case I_EORI:
                snprintf(buf, len, "EORI.%c #$%x, %s", szind, ival, eastr);
                break;
            default:
                return IE_ERR;
        }
    } else {
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            lfmt.osz, lfmt.eamode, lfmt.eareg, wcur16,
            eastr, sizeof(eastr));
        if (wcur16 < 0) return wcur16;

        switch (ote) {
            case I_OR:
                if (lfmt.dir)
                    snprintf(buf, len, "OR.%c D%d, %s", szind, lfmt.reg, eastr);
                else
                    snprintf(buf, len, "OR.%c %s, D%d", szind, eastr, lfmt.reg);
                break;
            case I_AND:
                if (lfmt.dir)
                    snprintf(buf, len, "AND.%c D%d, %s", szind, lfmt.reg, eastr);
                else
                    snprintf(buf, len, "AND.%c %s, D%d", szind, eastr, lfmt.reg);
                break;
            case I_EOR:
                snprintf(buf, len, "EOR.%c D%d, %s", szind, lfmt.reg, eastr);
                break;
            case I_NOT:
                snprintf(buf, len, "NOT.%c %s", szind, eastr);
                break;
            default:
                return IE_ERR;
        }
    }

    return wcur16;
}
