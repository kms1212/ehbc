#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu/cpu.h"

union movefmt {
    uint16_t raw;

    struct {
        uint16_t srcreg : 3;
        uint16_t srcmode : 3;
        uint16_t destmode : 3;
        uint16_t destreg : 3;
        uint16_t osz : 2;
        uint16_t : 2;
    };
};

DEF_OPFUNC(move_move) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    if (!BITFLD(iwd[0], 14, 2)) {
        char srcstr[20] = { 0, };
        char deststr[20] = { 0, };

        union movefmt mfmt;
        mfmt.raw = iwd[0];

        ssize_t wcur16   = 1;

        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            mfmt.osz, mfmt.srcmode, mfmt.srcreg, wcur16,
            srcstr, sizeof(srcstr));
        if (wcur16 < 0) return wcur16;

        wcur16 = _mc68030_disasm_ext(
            iwd, isz16,
            mfmt.osz, mfmt.destmode, mfmt.destreg, wcur16,
            deststr, sizeof(deststr));
        if (wcur16 < 0) return wcur16;

        mfmt.osz = mfmt.osz == 0b01 ? 0 : (mfmt.osz == 0b11 ? 1 : 2);

        char opstr[6] = "MOVE\0\0";
        if (mfmt.destmode == 0b001) opstr[4] = 'A';

        snprintf(buf, len, "%s.%c %s, %s", opstr, lut_szind[mfmt.osz], srcstr, deststr);

        return wcur16;
    }
    return 0;
}

DEF_OPFUNC(move_movep){
    return IE_ERR;
}

DEF_OPFUNC(move_movec){
    if (iwd == NULL || buf == NULL) return IE_ERR;
    CHK_SZ(isz16, 2);

    char adsel = BITFLD(iwd[1], 15, 1) ? 'A' : 'D';
    uint8_t reg = BITFLD(iwd[1], 12, 3);
    uint16_t cr = BITFLD(iwd[1], 0, 12);

    if ((cr > 0x002 && cr < 0x800) || cr > 0x804) return IE_ERR;
    if (cr > 3) cr -= 0x800 - 3;

    if (iwd[1] & 0b1)
        snprintf(buf, len, "MOVEC %c%d, %s", adsel, reg, lut_cr[cr]);
    else
        snprintf(buf, len, "MOVEC %s, %c%d", lut_cr[cr], adsel, reg);

    return 2;
}

DEF_OPFUNC(move_movem){
    return IE_ERR;
}

DEF_OPFUNC(move_moveq){
    if (iwd == NULL || buf == NULL) return IE_ERR;

    snprintf(buf, len, "MOVEQ #%d, D%d", (uint8_t)iwd[0], BITFLD(iwd[0], 9, 3));

    return 1;
}
