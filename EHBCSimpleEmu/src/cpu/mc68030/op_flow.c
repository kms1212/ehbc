#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"


union jbifmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t : 10;
    } j;

    struct {
        uint16_t dis : 8;
        uint16_t cond : 4;
        uint16_t : 4;
    } b;
};

/**
 * @brief MC68030: Disassemble jump/branch instructions
 * Available instructions:
 * - JMP
 * - JSR
 * - BRA
 * - BSR
 * - Bcc
 * - DBcc
 */
DEF_OPFUNC(flow_jb) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    union jbifmt jbfmt = { .raw = iwd[0] };

    ssize_t wcur16   = 1;
    
    char bostr[4] = "B\0\0\0";

    switch (ote) {
        case I_JMP:
        case I_JSR: {
            char eastr[20] = "";
            wcur16 = _mc68030_disasm_ext(
                iwd, isz16,
                0, jbfmt.j.eamode, jbfmt.j.eareg, wcur16,
                eastr, sizeof(eastr));

            snprintf(buf, len, ote == I_JMP ? "JMP %s" : "JSR %s", eastr);
            break;
        }
        case I_BRA:
            bostr[1] = 'R';
            bostr[2] = 'A';
            goto print;
        case I_BSR:
            bostr[1] = 'S';
            bostr[2] = 'R';
            goto print;
        case I_Bcc: {
            bostr[1] = lut_condstr[jbfmt.b.cond][0];
            bostr[2] = lut_condstr[jbfmt.b.cond][1];
print: {};
            int32_t dis = (int8_t)jbfmt.b.dis;  // 8-bit displacement
            if (dis == 0x00) {  // 16-bit displacement
                CHK_SZ(isz16, wcur16 + 1);
                dis = (int16_t)iwd[wcur16];
            } else if (dis == 0xFF) {  // 32-bit displacement
                CHK_SZ(isz16, wcur16 + 2);
                dis = (int32_t)W2L(iwd[wcur16], iwd[wcur16 + 1]);
            }
            snprintf(buf, len, "%s %d", bostr, dis);
            break;
        }
        case I_DBcc:
        default:
            return IE_ERR;
    }

    return wcur16;
}

/**
 * @brief MC68030: Disassemble return instructions
 * Available instructions:
 * - RTE
 * - RTD
 * - RTS
 * - RTR
 */
DEF_OPFUNC(flow_rtn) {
    if (iwd == NULL || buf == NULL) return IE_ERR;
    size_t wcur16 = 1;

    switch (ote) {
        case I_RTE:
            snprintf(buf, len, "RTE");
            break;
        case I_RTD:
            CHK_SZ(isz16, wcur16 + 1);
            snprintf(buf, len, "RTD #%d", (int16_t)iwd[wcur16]);
            break;
        case I_RTS:
            snprintf(buf, len, "RTS");
            break;
        case I_RTR:
            snprintf(buf, len, "RTR");
            break;
        default:
            return IE_ERR;
    }
    return wcur16;
}

/**
 * @brief MC68030: Disassemble trap instructions
 * Available instructions:
 * - TRAP
 * - TRAPcc
 * - TRAPV
 */
DEF_OPFUNC(flow_trap) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    size_t wcur16 = 1;

    switch (ote) {
        case I_TRAP:
            snprintf(buf, len, "TRAP #%d", BITFLD(iwd[0], 0, 4));
            break;
        case I_TRAPcc: {
            uint8_t cond = BITFLD(iwd[0], 8, 4);
            if (BITFLD(iwd[0], 2, 1)) {  // No operand
                snprintf(buf, len, "TRAP%s", lut_condstr[cond]);
            } else if ((iwd[0] & 0b11) == 0b11) {  // Long operand
                CHK_SZ(isz16, wcur16 + 2);
                snprintf(buf, len, "TRAP%s #%d", lut_condstr[cond], W2L(iwd[wcur16], iwd[wcur16 + 1]));
            } else {  // Word operand
                CHK_SZ(isz16, wcur16 + 1);
                snprintf(buf, len, "TRAP%s #%d", lut_condstr[cond], iwd[wcur16]);
            }
            break;
        }
        case I_TRAPV:
            snprintf(buf, len, "TRAPV");
            break;
        default:
            return IE_ERR;
    }
    return wcur16;
}

/**
 * @brief MC68030: Disassemble breakpoint instructions
 * Available instructions:
 * - BKPT
 */
DEF_OPFUNC(flow_bkpt) {
    if (iwd == NULL || buf == NULL) return IE_ERR;
    snprintf(buf, len, "BKPT #%d", iwd[0] & 0b111);
    return 1;
}

/**
 * @brief MC68030: Disassemble other flow control instructions
 * Available instructions:
 * - NOP
 * - RESET
 * - STOP
 */
DEF_OPFUNC(flow_other) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    switch (ote) {
        case I_NOP:
            snprintf(buf, len, "NOP");
            return 1;
        case I_RESET:
            snprintf(buf, len, "RESET");
            return 1;
        case I_STOP:
            CHK_SZ(isz16, 2);
            snprintf(buf, len, "STOP #$%X", iwd[1]);
            return 2;
        default:
            return IE_ERR;
    }
}
