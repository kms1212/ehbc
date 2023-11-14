#include "cpu/mc68030/_operation.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "cpu/cpu.h"

e_operator _mc68030_getoperator(uint16_t* iwd, size_t isz16) {
    if (iwd == NULL) return IE_ERR;
    CHK_SZ(isz16, 1);

    switch (BITFLD(iwd[0], 12, 4)) {
        case 0b0000: {
            // Immediate and MOVES intrustions
            if ((BITFLD(iwd[0], 8, 1) ^ BITFLD(iwd[0], 9, 3)) == 0b100) {
                if (BITFLD(iwd[0], 9, 3) == 0b100)
                    CHK_SZ(isz16, 2);

                switch (BITFLD(iwd[0], 6, 2)) {
                    case 0b00:
                        return I_BTST;
                    case 0b01:
                        return I_BCHG;
                    case 0b10:
                        return I_BCLR;
                    case 0b11:
                        return I_BSET;
                    default:
                        return IE_UNKNOWN;
                }
            } else if (BITFLD(iwd[0], 6, 2) == 0b11) {
                if (BITFLD(iwd[0], 11, 1)) {
                    if (BITFLD(iwd[0], 3, 3) == 0b111) {
                        CHK_SZ(isz16, 3);
                        return I_CAS2;
                    } else {
                        CHK_SZ(isz16, 2);
                        return I_CAS;
                    }

                } else {
                    CHK_SZ(isz16, 2);
                    if (BITFLD(iwd[0], 9, 2) > 2) {
                        return IE_INVALID;
                    } else {
                        if (BITFLD(iwd[1], 11, 1)) {
                            return I_CMP2;
                        } else {
                            return I_CHK2;
                        }
                    }
                }
            } else {
                uint8_t extsz = BITFLD(iwd[0], 6, 2);
                if (extsz > 2) {
                    return IE_INVALID;
                }
                switch (BITFLD(iwd[0], 9, 3)) {
                    case 0b000:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_ORI;
                    case 0b001:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_ANDI;
                    case 0b010:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_SUBI;
                    case 0b011:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_ADDI;
                    case 0b101:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_EORI;
                    case 0b110:
                        CHK_SZ(isz16, (extsz == 0 ? 1 : extsz) + 1);
                        return I_CMPI;
                    case 0b111:
                        CHK_SZ(isz16, 2);
                        return I_MOVES;
                    default:
                        return IE_UNKNOWN;
                }
            }
            break;
        }
        case 0b0001:
        case 0b0010:
        case 0b0011: {
            // MOVE and MOVEA instructions
            if (BITFLD(iwd[0], 6, 3) == 0b001) {
                return I_MOVEA;
            } else {
                return I_MOVE;
            }
            break;
        }
        case 0b0100: {
            // MOVE, BCD, Arithmetic, Flow control, and misc. instructions
            // 0100?xx?xxxxxxxx
            if (BITFLD(iwd[0], 8, 1)) {
                // 0100xxx1??xxxxxx
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    // 0100xxx111???xxx
                    if (!BITFLD(iwd[0], 3, 3)) {
                        return I_EXTB;
                    } else {
                        return I_LEA;
                    }
                } else if (!BITFLD(iwd[0], 6, 1)) {
                    return I_CHK;
                } else {
                    return IE_UNKNOWN;
                }
            } else if (BITFLD(iwd[0], 11, 1)) {
                // 01001x?0xxxxxxxx
                if (BITFLD(iwd[0], 9, 1)) {
                    // 01001?10xxxxxxxx
                    if (BITFLD(iwd[0], 10, 1)) {
                        // 01001110??xxxxxx
                        switch (BITFLD(iwd[0], 6, 2)) {
                            case 0b01: {
                                // 0100111001??xxxx
                                switch (BITFLD(iwd[0], 4, 2)) {
                                    case 0b00:
                                        return I_TRAP;
                                    case 0b01:
                                        // 010011100101?xxx
                                        if (BITFLD(iwd[0], 3, 1)) {
                                            return I_UNLK;
                                        } else {
                                            CHK_SZ(isz16, 2);
                                            return I_LINK;
                                        }
                                    case 0b10:
                                        return I_MOVE;
                                    case 0b11: {
                                        // 010011100111?xxx
                                        if (BITFLD(iwd[0], 3, 1)) {
                                            // 0100111001011???
                                            if (BITFLD(iwd[0], 1, 2) == 0b01) {
                                                CHK_SZ(isz16, 2);
                                                return I_MOVEC;
                                            } else {
                                                return IE_UNKNOWN;
                                            }
                                        } else {
                                            // 0100111001110??x
                                            switch (BITFLD(iwd[0], 0, 3)) {
                                                case 0b000:
                                                    return I_RESET;
                                                case 0b001:
                                                    return I_NOP;
                                                case 0b010:
                                                    CHK_SZ(isz16, 2);
                                                    return I_STOP;
                                                case 0b011:
                                                    return I_RTE;
                                                case 0b100:
                                                    CHK_SZ(isz16, 2);
                                                    return I_RTD;
                                                case 0b101:
                                                    return I_RTS;
                                                default:
                                                    return IE_UNKNOWN;
                                            }
                                        }
                                    }
                                    default:
                                        return IE_UNKNOWN;
                                }
                                break;
                            }
                            case 0b10: {
                                return I_JSR;
                            }
                            case 0b11: {
                                return I_JMP;
                            }
                            default:
                                return IE_UNKNOWN;
                        }
                    } else {
                        // 01001010??xxxxxx
                        if (BITFLD(iwd[0], 6, 2) == 0b11) {
                            if (BITFLD(iwd[0], 0, 6) == 0b111100) {
                                return I_ILLEGAL;
                            } else {
                                return I_TAS;
                            }
                        } else {
                            return I_TST;
                        }
                    }
                } else {
                    // 01001x00?xxxxxxx
                    if (BITFLD(iwd[0], 7, 1)) {
                        // 01001?001x???xxx
                        if (BITFLD(iwd[0], 3, 3) == 0b000) {
                            return I_EXT;
                        } else {
                            CHK_SZ(isz16, 2);
                            return I_MOVEM;
                        }
                    } else {
                        // 01001?000xxxxxxx
                        if (BITFLD(iwd[0], 10, 1)) {
                            // 010011000?xxxxxx
                            CHK_SZ(isz16, 2);
                            if (BITFLD(iwd[1], 11, 1)) {
                                if (BITFLD(iwd[0], 6, 1)) {
                                    return I_DIVS;  // DIVSL?
                                } else {
                                    return I_MULS;
                                }
                            } else {
                                if (BITFLD(iwd[0], 6, 1)) {
                                    return I_DIVU;  // DIVUL?
                                } else {
                                    return I_MULU;
                                }
                            }
                        } else {
                            // 010010000?xxxxxx
                            if (BITFLD(iwd[0], 6, 1)) {
                                // 0100100001???xxx
                                switch (BITFLD(iwd[0], 3, 3)) {
                                    case 0b000:
                                        return I_SWAP;
                                    case 0b001:
                                        return I_BKPT;
                                    default:
                                        return I_PEA;
                                }
                            } else {
                                // 0100100000???xxx
                                if (BITFLD(iwd[0], 3, 3) == 0b001) {
                                    CHK_SZ(isz16, 3);
                                    return I_LINK;
                                } else {
                                    return I_NBCD;
                                }
                            }
                        }
                    }
                }
            } else {
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    return I_MOVE;
                } else {
                    switch (BITFLD(iwd[0], 9, 2)) {
                        case 0b00:
                            return I_NEGX;
                        case 0b01:
                            return I_CLR;
                        case 0b10:
                            return I_NEG;
                        case 0b11:
                            return I_NOT;
                        default:
                            return IE_UNKNOWN;
                    }
                }
            }
            break;
        }
        case 0b0101: {
            // DBcc, TRAPcc, Scc, and Quick Arithmetic instructions
            if (BITFLD(iwd[0], 6, 2) == 0b11) {
                switch (BITFLD(iwd[0], 3, 3)) {
                    case 0b001:
                        CHK_SZ(isz16, 2);
                        return I_DBcc;
                    case 0b111: {
                        switch (BITFLD(iwd[0], 0, 3)) {
                            case 0b010:
                                CHK_SZ(isz16, 2);
                                break;
                            case 0b011:
                                CHK_SZ(isz16, 3);
                                break;
                            case 0b100:
                                break;
                            default:
                                return IE_UNKNOWN;
                        }
                        return I_TRAPcc;
                        break;
                    }
                    default:
                        return I_Scc;
                }
            } else {
                if (BITFLD(iwd[0], 8, 1)) {
                    return I_SUBQ;
                } else {
                    return I_ADDQ;
                }
            }
            break;
        }
        case 0b0110: {
            // Branch, TRAPV instructions
            switch (BITFLD(iwd[0], 8, 4)) {
                case 0b0000: {
                    switch (BITFLD(iwd[0], 0, 8)) {
                        case 0x00:
                            CHK_SZ(isz16, 2);
                            break;
                        case 0xFF:
                            CHK_SZ(isz16, 3);
                            break;
                        default:
                            break;
                    }
                    return I_BRA;
                    break;
                }
                case 0b0001:
                    switch (BITFLD(iwd[0], 0, 8)) {
                        case 0x00:
                            CHK_SZ(isz16, 2);
                            break;
                        case 0xFF:
                            CHK_SZ(isz16, 3);
                            break;
                        default:
                            break;
                    }
                    return I_BSR;
                case 0b1110:
                    switch (BITFLD(iwd[0], 0, 8)) {
                        case 0x76:
                            return I_TRAPV;
                        case 0x77:
                            return I_RTR;
                        default:
                            return IE_UNKNOWN;
                    }
                default:
                    switch (BITFLD(iwd[0], 0, 8)) {
                        case 0x00:
                            CHK_SZ(isz16, 2);
                            break;
                        case 0xFF:
                            CHK_SZ(isz16, 3);
                            break;
                        default:
                            break;
                    }
                    return I_Bcc;
            }
            break;
        }
        case 0b0111: {
            // MOVEQ instruction
            if (BITFLD(iwd[0], 8, 1)) {
                return IE_UNKNOWN;
            } else {
                return I_MOVEQ;
            }
            break;
        }
        case 0b1000:
        case 0b1100: {
            // Word-sized MUL/DIV, BCD, PACK/UNPK, OR, AND, and EXG instructions
            if (BITFLD(iwd[0], 6, 2) == 0b11) {
                if (BITFLD(iwd[0], 8, 1)) {
                    if (BITFLD(iwd[0], 14, 1)) {
                        return I_MULS;
                    } else {
                        return I_DIVS;  // DIVSL?
                    }
                } else {
                    if (BITFLD(iwd[0], 14, 1)) {
                        return I_MULU;
                    } else {
                        return I_DIVU;  // DIVUL?
                    }
                }
            } else if (BITFLD(iwd[0], 10, 1) && BITFLD(iwd[0], 4, 2) == 0b00) {
                if (BITFLD(iwd[0], 6, 3) == 0b100) {
                    if (BITFLD(iwd[0], 14, 1)) {
                        return I_ABCD;
                    } else {
                        return I_SBCD;
                    }
                } else if (BITFLD(iwd[0], 14, 1)) {
                    if (BITFLD(iwd[0], 8, 1)) {
                        return I_EXG;
                    } else {
                        return IE_UNKNOWN;
                    }
                } else {
                    switch (BITFLD(iwd[0], 6, 3)) {
                    case 0b101:
                        // Fix length
                        CHK_SZ(isz16, 2);
                        return I_PACK;
                    case 0b110:
                        // Fix length
                        CHK_SZ(isz16, 2);
                        return I_UNPK;
                    default:
                        return IE_UNKNOWN;
                    }
                }
            } else {
                if (BITFLD(iwd[0], 14, 1)) {
                    return I_AND;
                } else {
                    return I_OR;
                }
            }
            break;
        }
        case 0b1001:
        case 0b1101: {
            // SUB and ADD instructions
            if (BITFLD(iwd[0], 14, 1)) {
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    return I_ADDA;
                } else if (!BITFLD(iwd[0], 4, 2) && BITFLD(iwd[0], 8, 1)) {
                    if (BITFLD(iwd[0], 8, 1)) {
                        return I_ADDX;
                    } else {
                        return IE_UNKNOWN;
                    }
                } else {
                    return I_ADD;
                }
            } else {
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    return I_SUBA;
                } else if (!BITFLD(iwd[0], 4, 2) && BITFLD(iwd[0], 8, 1)) {
                    if (BITFLD(iwd[0], 8, 1)) {
                        return I_SUBX;
                    } else {
                        return IE_UNKNOWN;
                    }
                } else {
                    return I_SUB;
                }
            }
            break;
        }
        case 0b1011: {
            // CMP and EOR instructions
            if (BITFLD(iwd[0], 6, 2) == 0b11) {
                return I_CMPA;
            } else if (BITFLD(iwd[0], 8, 1)) {
                if (BITFLD(iwd[0], 3, 3) == 0b001) {
                    return I_CMPM;
                } else {
                    return I_EOR;
                }
            } else {
                return I_CMP;
            }
            break;
        }
        case 0b1110: {
            // Bit field, Shift, and Rotate instructions
            if (BITFLD(iwd[0], 8, 1)) {
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    if (BITFLD(iwd[0], 11, 1)) {
                        CHK_SZ(isz16, 2);
                        switch (BITFLD(iwd[0], 9, 2)) {
                            case 0b00:
                                return I_BFEXTU;
                            case 0b01:
                                return I_BFEXTS;
                            case 0b10:
                                return I_BFFFO;
                            case 0b11:
                                return I_BFINS;
                            default:
                                return IE_UNKNOWN;
                        }
                    } else {
                        switch (BITFLD(iwd[0], 9, 2)) {
                            case 0b00:
                                return I_ASL;
                            case 0b01:
                                return I_LSL;
                            case 0b10:
                                return I_ROXL;
                            case 0b11:
                                return I_ROL;
                            default:
                                return IE_UNKNOWN;
                        }
                    }
                } else {
                    switch (BITFLD(iwd[0], 3, 2)) {
                        case 0b00:
                            return I_ASL;
                        case 0b01:
                            return I_LSL;
                        case 0b10:
                            return I_ROXL;
                        case 0b11:
                            return I_ROL;
                        default:
                            return IE_UNKNOWN;
                    }
                }
            } else {
                if (BITFLD(iwd[0], 6, 2) == 0b11) {
                    if (BITFLD(iwd[0], 11, 1)) {
                        CHK_SZ(isz16, 2);
                        switch (BITFLD(iwd[0], 9, 2)) {
                            case 0b00:
                                return I_BFTST;
                            case 0b01:
                                return I_BFCHG;
                            case 0b10:
                                return I_BFCLR;
                            case 0b11:
                                return I_BFSET;
                            default:
                                return IE_UNKNOWN;
                        }
                    } else {
                        switch (BITFLD(iwd[0], 9, 2)) {
                            case 0b00:
                                return I_ASR;
                            case 0b01:
                                return I_LSR;
                            case 0b10:
                                return I_ROXR;
                            case 0b11:
                                return I_ROR;
                            default:
                                return IE_UNKNOWN;
                        }
                    }
                } else {
                    switch (BITFLD(iwd[0], 3, 2)) {
                        case 0b00:
                            return I_ASR;
                        case 0b01:
                            return I_LSR;
                        case 0b10:
                            return I_ROXR;
                        case 0b11:
                            return I_ROR;
                        default:
                            return IE_UNKNOWN;
                    }
                }
            }
            break;
        }
        case 0b1111: {
            // MMU and Coprocessor instructions
            if (!BITFLD(iwd[0], 9, 3)) {
                CHK_SZ(isz16, 2);
                if (!!BITFLD(iwd[0], 6, 3)) return IE_UNKNOWN;
                switch (BITFLD(iwd[1], 13, 3)) {
                    case 0b001:
                        if (!BITFLD(iwd[1], 10, 3)) {
                            if (BITFLD(iwd[1], 9, 1)) {
                                return I_PLOADR;
                            } else {
                                return I_PLOADW;
                            }
                        } else if (BITFLD(iwd[1], 5, 3) == 0b001) {
                            return I_PFLUSHA;
                        } else {
                            return I_PFLUSH;
                        }
                        break;
                    case 0b010:
                        if (BITFLD(iwd[1], 8, 1)) {
                            return I_PMOVEFD;
                        } else {
                            return I_PMOVE;
                        }
                        break;
                    case 0b100:
                        if (BITFLD(iwd[1], 9, 1)) {
                            return I_PTESTR;
                        } else {
                            return I_PTESTW;
                        }
                        break;
                    default:
                        return IE_UNKNOWN;
                }
            } else {
                switch (BITFLD(iwd[0], 6, 3)) {
                    case 0b000:
                        return I_cpGEN;
                    case 0b001: {
                        CHK_SZ(isz16, 2);
                        switch (BITFLD(iwd[0], 3, 3)) {
                            case 0b001:
                                return I_cpDBcc;
                            case 0b111:
                                return I_cpTRAPcc;
                            default:
                                return I_cpScc;
                        }
                        break;
                    }
                    case 0b010:
                    case 0b011:
                        return I_cpBcc;
                    case 0b100:
                        return I_cpSAVE;
                    case 0b101:
                        return I_cpRESTORE;
                    default:
                        return IE_UNKNOWN;
                }
            }
            break;
        }
        default: {
            return IE_UNKNOWN;
            break;
        }
    }
    return IE_UNKNOWN;
}
