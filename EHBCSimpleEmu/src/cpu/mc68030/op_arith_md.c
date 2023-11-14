#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union mulifmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t : 2;
        uint16_t sgn : 1;
        uint16_t reg : 3;
        uint16_t : 3;
        uint16_t osz : 1;
    } w0;

    struct {
        uint16_t dhreg : 3;
        uint16_t : 7;
        uint16_t psz : 1;
        uint16_t sgn : 1;
        uint16_t dlreg : 3;
        uint16_t : 1;
    } w1;
};

union divifmt {
    uint16_t raw;

    struct {
        uint16_t eareg : 3;
        uint16_t eamode : 3;
        uint16_t : 2;
        uint16_t sgn : 1;
        uint16_t reg : 3;
        uint16_t : 2;
        uint16_t osz : 2;
    } w0;

    struct {
        uint16_t drreg : 3;
        uint16_t : 7;
        uint16_t dsz : 1;
        uint16_t sgn : 1;
        uint16_t dqreg : 3;
        uint16_t : 1;
    } w1;
};

/**
 * @brief MC68030: Disassemble arithmetic mul instructions
 * Available instructions:
 * - MULU
 * - MULS
 */
DEF_OPFUNC(arith_mul) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    char eastr[20] = { 0, };

    union mulifmt afmt = { .raw = iwd[0] };

    ssize_t wcur16   = afmt.w0.osz ? 1 : 2;
    CHK_SZ(isz16, wcur16);

    // afmt.w0.osz == 0: word * word
    // afmt.w0.osz == 1: long * long
    wcur16 = _mc68030_disasm_ext(
        iwd, isz16,
        (uint8_t)afmt.w0.osz + 1, afmt.w0.eamode, afmt.w0.eareg, wcur16,
        eastr, sizeof(eastr));
    if (wcur16 < 0) return wcur16;

    if (afmt.w0.osz) {
        char sgnind = afmt.w0.sgn ? 'S' : 'U';
        // word operation
        // use w0.reg
        // single-word operation header
        // <ea> * Dn -> Dn
        snprintf(buf, len, "MUL%c.W %s, D%d", sgnind, eastr, afmt.w0.reg);
        return wcur16;
    } else {
        // long operation
        // use w1
        // double-word operation header
        wcur16++;
        afmt.raw = iwd[1];
        char sgnind = afmt.w1.sgn ? 'S' : 'U';

        if (afmt.w1.psz)  // 64-bit product
            snprintf(buf, len, "MUL%c.L %s, D%d, D%d", sgnind, eastr,
                afmt.w1.dhreg, afmt.w1.dlreg);
        else  // 32-bit product
            snprintf(buf, len, "MUL%c.L %s, D%d", sgnind, eastr, afmt.w1.dlreg);
        return wcur16;
    }
}


/**
 * @brief MC68030: Disassemble arithmetic mul instructions
 * Available instructions:
 * - DIVS
 * - DIVSL
 * - DIVU
 * - DIVUL
 */
DEF_OPFUNC(arith_div) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    char eastr[20] = { 0, };
    char opstr[6] = "DIV\0\0\0";

    union divifmt afmt = { .raw = iwd[0] };

    // afmt.w0.osz == 0b10: long / word (DIV?.W)
    // afmt.w0.osz == 0b01: (qword or long) / word (DIV??.L)
    uint8_t osz16 = afmt.w0.osz == 0b10 ? 1 : 0;

    ssize_t wcur16   = osz16 ? 1 : 2;
    CHK_SZ(isz16, wcur16);

    // osz = 0 -> osz + 1 = 1 -> WORD extension
    // osz = 1 -> osz + 1 = 2 -> LONG extension
    wcur16 = _mc68030_disasm_ext(
        iwd, isz16,
        osz16 + 1, afmt.w0.eamode, afmt.w0.eareg, wcur16,
        eastr, sizeof(eastr));
    if (wcur16 < 0) return wcur16;

    if (afmt.w0.osz == 0b10) {
        char sgnind = afmt.w0.sgn ? 'S' : 'U';
        // word operation
        // use w0.reg
        // single-word operation header
        // <ea> / Dn -> Dn[16r, 16q]
        snprintf(buf, len, "%s%c.W %s, D%d", opstr, sgnind, eastr, afmt.w0.reg);
        return wcur16;
    } else {
        // long operation
        // use w1
        // double-word operation header
        wcur16++;
        afmt.raw = iwd[1];
        char sgnind = afmt.w1.sgn ? 'S' : 'U';

        if (afmt.w1.dsz)  // 64-bit dividend. Save both q and r
            snprintf(buf, len, "DIV%c.L %s, D%d:D%d", sgnind, eastr,
                afmt.w1.drreg, afmt.w1.dqreg);
        else if (afmt.w1.dqreg == afmt.w1.drreg)  // 32-bit dividend. Save only q
            snprintf(buf, len, "DIV%c.L %s, D%d", sgnind, eastr, afmt.w1.dqreg);
        else  // 32-bit dividend, Save both q and r
            snprintf(buf, len, "DIV%cL.L %s, D%d:D%d", sgnind, eastr,
                afmt.w1.drreg, afmt.w1.dqreg);
        return wcur16;
    }
}

