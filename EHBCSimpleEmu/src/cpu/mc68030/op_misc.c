#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union linkfmt {
    uint16_t raw;

    struct {
        uint16_t reg : 3;
        uint16_t szdetect : 1;
        uint16_t : 12;
    };
};

union clrfmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t osz : 2;
        uint16_t : 8;
    };
};

/**
 * @brief MC68030: Disassemble misc. operations
 * Available instructions:
 * - EXG
 * - SWAP
 * - CLR
 * - ILLEGAL
 * - Scc
 * - PEA
 * - LEA
 * - LINK
 * - UNLK
 */
DEF_OPFUNC(misc_cpu) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    size_t wcur16 = 1;
    CHK_SZ(isz16, wcur16);

    switch (ote) {
        case I_EXG:
        case I_SWAP:
            return IE_ERR;
        case I_CLR: {
            union clrfmt cfmt = { .raw = iwd[0] };
            char eastr[20];
            wcur16 = _mc68030_disasm_ext(
                iwd, isz16,
                cfmt.osz, cfmt.eamode, cfmt.eareg, wcur16,
                eastr, sizeof(eastr));
            if (wcur16 < 0) return wcur16;
            snprintf(buf, len, "CLR.%c %s", lut_szind[cfmt.osz], eastr);
            break;
        }
        case I_ILLEGAL:
        case I_Scc:
        case I_PEA:
        case I_LEA:
            return IE_ERR;
            break;
        case I_LINK: {
            union linkfmt lfmt = { .raw = iwd[0] };
            char oszind = lfmt.szdetect ? 'L' : 'W';
            int32_t displacement;
            if (lfmt.szdetect) {  // LONG operation
                CHK_SZ(isz16, wcur16 + 2);
                displacement = ((int32_t)iwd[wcur16] << 16) | iwd[wcur16 + 1];
                wcur16 += 2;
            } else {  // WORD operation
                CHK_SZ(isz16, wcur16 + 1);
                displacement = (int16_t)iwd[wcur16];
                wcur16++;
            }
            snprintf(buf, len, "LINK.%c A%d, #%d", oszind, lfmt.reg, displacement);
            break;
        }
        case I_UNLK: {
            union linkfmt lfmt = { .raw = iwd[0] };
            snprintf(buf, len, "UNLK A%d", lfmt.reg);
            break;
        }
        default:
            return IE_ERR;
    }

    return wcur16;
}

/**
 * @brief MC68030: Disassemble MMU operations
 * Available instructions:
 * - PFLUSH
 * - PFLUSHA
 * - PLOADR
 * - PLOADW
 * - PMOVE
 * - PMOVEFD
 * - PTESTR
 * - PTESTW
 */
DEF_OPFUNC(misc_mmu) {
    return IE_ERR;
}

/**
 * @brief MC68030: Disassemble coprocessor instructions
 * Available instructions:
 * - cpBcc
 * - cpDBcc
 * - cpScc
 * - cpTRAPcc
 * - cpGEN
 * - cpSAVE
 * - cpRESTORE
 */
DEF_OPFUNC(misc_coproc) {
    return IE_ERR;
}
