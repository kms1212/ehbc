#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union asifmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t opmode : 3;
        uint16_t reg : 3;
        uint16_t : 4;
    };
};

// TODO: Unify ..._disasm_arith_add and ..._disasm_arith_sub function.

/**
 * @brief MC68030: Disassemble arithmetic add instructions
 * Available instructions:
 * - ADD
 * - ADDA
 * - ADDI
 * - ADDQ
 * - ~~ADDX~~
 */
DEF_OPFUNC(arith_add) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    char eastr[20] = "";
    char opstr[5] = "ADD\0\0";
    char szind = 0;
    uint32_t ival = 0;

    union asifmt afmt = { .raw = iwd[0] };

    ssize_t wcur16   = 1;

    if (ote == I_ADDA) {
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            0b10 | ~BITFLD(afmt.opmode, 2, 1), afmt.eamode, afmt.eareg, wcur16,
            eastr, sizeof(eastr));
    } else {
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            afmt.opmode & 0b011, afmt.eamode, afmt.eareg, wcur16,
            eastr, sizeof(eastr));
    }
    if (wcur16 < 0) return wcur16;

    szind = lut_szind[afmt.opmode & 0b11];
    switch (ote) {
        case I_ADD:
            if (afmt.opmode >> 2)
                snprintf(buf, len, "%s.%c %s, D%d", opstr, szind, eastr, afmt.reg);
            else
                snprintf(buf, len, "%s.%c D%d, %s", opstr, szind, afmt.reg, eastr);
            break;
        case I_ADDA:
            opstr[3] = 'A';
            szind = (afmt.opmode >> 2) ? 'L' : 'W';
            snprintf(buf, len, "%s.%c %s, A%d", opstr, szind, eastr, afmt.reg);
            break;
        case I_ADDI:
            opstr[3] = 'I';
            CHK_SZ(isz16, ++wcur16);
            if (afmt.opmode == 2) {
                CHK_SZ(isz16, ++wcur16);
                ival = W2L(iwd[wcur16], iwd[wcur16 + 1]);
            } else {
                ival = iwd[wcur16];
            }
            snprintf(buf, len, "%s.%c #%d, %s", opstr, szind, ival, eastr);
            break;
        case I_ADDQ:
            opstr[3] = 'Q';
            ival = afmt.reg;
            snprintf(buf, len, "%s.%c #%d, %s", opstr, szind, ival, eastr);
            break;
        case I_ADDX:
            opstr[3] = 'X';
            // TODO: Implement _mc68030_disasm_arith_add(I_SUBX, ...) behavior
        default:
            return IE_ERR;
    }

    return wcur16;
}

/**
 * @brief MC68030: Disassemble arithmetic sub instructions
 * Available instructions:
 * - SUB
 * - SUBA
 * - SUBI
 * - SUBQ
 * - ~~SUBX~~
 */
DEF_OPFUNC(arith_sub) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    char eastr[20] = "";
    char opstr[5] = "SUB\0\0";
    char szind = 0;
    uint32_t ival = 0;

    union asifmt afmt = { .raw = iwd[0] };

    ssize_t wcur16   = 1;

    if (ote == I_SUBA) {
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            0b10 | ~BITFLD(afmt.opmode, 2, 1), afmt.eamode, afmt.eareg, wcur16,
            eastr, sizeof(eastr));
    } else {
        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            afmt.opmode & 0b011, afmt.eamode, afmt.eareg, wcur16,
            eastr, sizeof(eastr));
    }
    if (wcur16 < 0) return wcur16;

    szind = lut_szind[afmt.opmode & 0b11];
    switch (ote) {
        case I_SUB:
            if (afmt.opmode >> 2)
                snprintf(buf, len, "%s.%c %s, D%d", opstr, szind, eastr, afmt.reg);
            else
                snprintf(buf, len, "%s.%c D%d, %s", opstr, szind, afmt.reg, eastr);
            break;
        case I_SUBA:
            opstr[3] = 'A';
            szind = (afmt.opmode >> 2) ? 'L' : 'W';
            snprintf(buf, len, "%s.%c %s, A%d", opstr, szind, eastr, afmt.reg);
            break;
        case I_SUBI:
            opstr[3] = 'I';
            CHK_SZ(isz16, ++wcur16);
            if (afmt.opmode == 2) {
                CHK_SZ(isz16, ++wcur16);
                ival = W2L(iwd[wcur16], iwd[wcur16 + 1]);
            } else {
                ival = iwd[wcur16];
            }
            snprintf(buf, len, "%s.%c #%d, %s", opstr, szind, ival, eastr);
            break;
        case I_SUBQ:
            opstr[3] = 'Q';
            ival = afmt.reg;
            snprintf(buf, len, "%s.%c #%d, %s", opstr, szind, ival, eastr);
            break;
        case I_SUBX:
            opstr[3] = 'X';
            // TODO: Implement _mc68030_disasm_arith_sub(I_SUBX, ...) behavior
        default:
            return IE_ERR;
    }

    return wcur16;
}
