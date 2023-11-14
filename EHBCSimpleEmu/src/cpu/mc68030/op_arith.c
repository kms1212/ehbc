#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"


union bcdifmt {
    uint16_t raw;

    struct {
        uint16_t ry : 3;
        uint16_t rm : 1;
        uint16_t : 5;
        uint16_t rx : 3;
        uint16_t : 4;
    } as;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t : 10;
    } neg;
};

union negfmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t osz : 2;
        uint16_t : 10;
    };
};

union extfmt {
    uint16_t raw;

    struct {
        uint16_t reg : 3;
        uint16_t : 3;
        uint16_t opmode : 3;
        uint16_t : 7;
    };
};

/**
 * @brief MC68030: Disassemble BCD instructions
 * Available instructions:
 * - ABCD
 * - SBCD
 * - NBCD
 * - PACK
 * - UNPK
 */
DEF_OPFUNC(arith_bcd) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    union bcdifmt bfmt = { .raw = iwd[0] };

    switch (ote) {
        case I_ABCD:
            if (bfmt.as.rm)
                snprintf(buf, len, "ABCD -(A%d), -(A%d)", bfmt.as.ry, bfmt.as.rx);
            else
                snprintf(buf, len, "ABCD D%d, D%d", bfmt.as.ry, bfmt.as.rx);
            break;
        case I_SBCD:
            if (bfmt.as.rm)
                snprintf(buf, len, "SBCD -(A%d), -(A%d)", bfmt.as.ry, bfmt.as.rx);
            else
                snprintf(buf, len, "SBCD D%d, D%d", bfmt.as.ry, bfmt.as.rx);
            break;
        case I_NBCD: {
            char eastr[20] = "";
            ssize_t wcur16 = 1;
            wcur16 = _mc68030_disasm_ext(
                iwd, isz16,
                0, bfmt.neg.eamode, bfmt.neg.eareg, wcur16,
                eastr, sizeof(eastr));
            snprintf(buf, len, "NBCD %s", eastr);
            break;
        }
        case I_PACK:
        case I_UNPK:
        default:
            return IE_ERR;
    }
    return 1;
}

DEF_OPFUNC(arith_neg) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    union negfmt nfmt = { .raw = iwd[0] };
    char eastr[20] = "";

    ssize_t wcur16 = 1;

    wcur16 = _mc68030_disasm_ext(
        iwd, isz16,
        0, nfmt.eamode, nfmt.eareg, wcur16,
        eastr, sizeof(eastr));
    if (wcur16 < 0) return wcur16;

    snprintf(buf, len, "NEG.%c %s", lut_szind[nfmt.osz], eastr);

    return 1;
}

DEF_OPFUNC(arith_ext) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    union extfmt efmt = { .raw = iwd[0] };
    char opstr[5] = "EXT\0\0";

    if ((efmt.opmode & 0b100) == 0b100) opstr[3] = 'B';

    snprintf(buf, len, "%s.%c D%d",
        opstr,
        lut_szind[(efmt.opmode & 0b11) - 1],
        efmt.reg);

    return 1;
}

