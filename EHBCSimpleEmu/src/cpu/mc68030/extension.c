#include "cpu/mc68030/_operation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu/cpu.h"

ssize_t _mc68030_disasm_ext(
    uint16_t* iwd, uint16_t isz16,
    uint8_t osz, uint8_t mode, uint8_t reg, size_t wcur16,
    char* buf, size_t len) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    size_t reqsz16 = wcur16;

    switch (mode) {
        case 0b000:  // Dn
            snprintf(buf, len, "D%d", reg);
            break;
        case 0b001:  // An
            snprintf(buf, len, "A%d", reg);
            break;
        case 0b010:  // (An)
            snprintf(buf, len, "(A%d)", reg);
            break;
        case 0b011:  // (An)+
            snprintf(buf, len, "(A%d)+", reg);
            break;
        case 0b100:  // -(An)
            snprintf(buf, len, "-(A%d)", reg);
            break;
        case 0b101:  // (d16, An)
            reqsz16++;
            CHK_SZ(isz16, reqsz16);
            snprintf(buf, len, "(%d, A%d)", (int16_t)iwd[wcur16], reg);
            break;
        case 0b110:
            reqsz16++;
            CHK_SZ(isz16, reqsz16);
            if (BITFLD(iwd[wcur16], 8, 1)) {
                // Full extension
                s_fullext* extptr = (s_fullext*)&(iwd[wcur16]);
                if (extptr->dasel) {

                } else {
                    
                }
            } else {
                // Brief extension
                s_briefext* extptr = (s_briefext*)&(iwd[wcur16]);
                snprintf(buf, len, "(%d, A%d, %c%d.%c*%d)",
                    extptr->displacement, reg, extptr->dasel ? 'A' : 'D',
                    extptr->reg, extptr->idxsz ? 'L' : 'W', 1 << extptr->scale);
            }
            break;
        case 0b111: {
            switch (reg) {
                case 0b000:  // (xxx).W
                    reqsz16++;
                    CHK_SZ(isz16, reqsz16);
                    snprintf(buf, len,
                        "($%X).W", iwd[wcur16]);
                    break;
                case 0b001:  // (xxx).L
                    reqsz16 += 2;
                    CHK_SZ(isz16, reqsz16);
                    snprintf(buf, len,
                        "($%X).L",
                        ((uint32_t)iwd[wcur16] << 16) | iwd[wcur16 + 1]);
                    break;
                case 0b100:  // #<data>
                    // osz == 2 : long
                    // osz == 1 : word
                    // osz == 0 : byte
                    if (osz == 2) {
                        reqsz16 += 2;
                        CHK_SZ(isz16, reqsz16);
                        snprintf(buf, len,
                            "#$%X",
                            ((uint32_t)iwd[wcur16] << 16) | iwd[wcur16 + 1]);
                    } else {
                        reqsz16++;
                        CHK_SZ(isz16, reqsz16);
                        snprintf(buf, len,
                            "#$%X",
                            iwd[wcur16] & (osz == 1 ? 0xFFFF : 0xFF));
                    }
                    break;
                case 0b010:  // (d16, PC)
                    reqsz16 += 1;
                    CHK_SZ(isz16, reqsz16);
                    snprintf(buf, len, "(%d, PC)", (int16_t)iwd[wcur16]);
                    break;
                case 0b011:
                    break;
                default:  // invalid
                    return IE_INVALID;
                    break;
            }
            break;
        }
    }
    return reqsz16;
}
