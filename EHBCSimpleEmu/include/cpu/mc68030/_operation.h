#ifndef __CPU_MC68030_OPERATION_H__
#define __CPU_MC68030_OPERATION_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "compat.h"


////////////////////////////////////////////////////////////////////////////////
// Enums

enum indir_mode {
    INDIR_NOINDIRECT    = 0,
    INDIR_PREIDX_NULL   = 1,
    INDIR_PREIDX_WORD   = 2,
    INDIR_PREIDX_LONG   = 3,
    INDIR_POSTIDX_NULL  = 1,
    INDIR_POSTIDX_WORD  = 2,
    INDIR_POSTIDX_LONG  = 3,
    INDIR_MEM_NULL      = 1,
    INDIR_MEM_WORD      = 2,
    INDIR_MEM_LONG      = 3,
};

enum ea_mode {
    EA_M_DATA_DIRECT    = 0,
    EA_M_ADDR_DIRECT    = 1,
    EA_M_ADDR_INDIR     = 2,
    EA_M_ADDR_INDIR_PI  = 3,
    EA_M_ADDR_INDIR_PD  = 4,
    EA_M_ADDR_INDIR_DIS = 5,
    EA_M_ADDR_INDIR_IDX = 6,
    EA_M_MEM_INDIR_PRE  = 6,
    EA_M_MEM_INDIR_POST = 6,
    EA_M_PC_DIRECT      = 7,
    EA_M_ABSOLUTE       = 7,
};

enum ea_reg {
    EA_R0               = 0,
    EA_R1               = 1,
    EA_R2               = 2,
    EA_R3               = 3,
    EA_R4               = 4,
    EA_R5               = 5,
    EA_R6               = 6,
    EA_R7               = 7,
    EA_R_PC_INDIR_DIS   = 2,
    EA_R_PC_INDIR_IDX   = 3,
    EA_R_PC_INDIR_BASE  = 3,
    EA_R_MEM_INDIR_POST = 3,
    EA_R_MEM_INDIR_PRE  = 3,
    EA_R_ABSOLUTE_SHORT = 0,
    EA_R_ABSOLUTE_LONG  = 1,
    EA_R_IMMEDIATE      = 4,
};

enum cond {
    COND_T      = 0x0,
    COND_F      = 0x1,
    COND_HI     = 0x2,
    COND_LS     = 0x3,
    COND_CC     = 0x4,
    COND_CS     = 0x5,
    COND_NE     = 0x6,
    COND_EQ     = 0x7,
    COND_VC     = 0x8,
    COND_VS     = 0x9,
    COND_PL     = 0xA,
    COND_MI     = 0xB,
    COND_GE     = 0xC,
    COND_LT     = 0xD,
    COND_GT     = 0xE,
    COND_LE     = 0xF,
};

enum opgroup {
    IG_ARITH    = 0x00000000,  // Arithmetic operations

    IT_BCD      = 0x00010000,
    IT_ADD      = 0x00020000,
    IT_SUB      = 0x00030000,
    IT_MUL      = 0x00040000,
    IT_DIV      = 0x00050000,
    IT_NEG      = 0x00060000,
    IT_EXT      = 0x00070000,

    IG_LOGIC    = 0x00100000,  // Logical operations

    IT_OR       = 0x00110000,
    IT_AND      = 0x00120000,
    IT_EOR      = 0x00130000,
    IT_NOT      = 0x00140000,

    IG_MOVE     = 0x00200000,  // Move operations

    IT_MOVEP    = 0x00210000,
    IT_MOVEC    = 0x00220000,
    IT_MOVEM    = 0x00230000,
    IT_MOVEQ    = 0x00240000,

    IG_BITFLD   = 0x00300000,  // Bit/Bit-field operations

    IT_BIT      = 0x00310000,
    IT_BITFLD   = 0x00320000,

    IG_SR       = 0x00400000,  // Shift/Rotate operations

    IT_AS       = 0x00410000,
    IT_LS       = 0x00420000,
    IT_ROX      = 0x00430000,
    IT_RO       = 0x00440000,

    IG_CMP      = 0x00500000,  // Compare operations

    IG_FLOW     = 0x00600000,  // Flow control operations

    IT_JB       = 0x00610000,
    IT_RTN      = 0x00620000,
    IT_TRAP     = 0x00630000,
    IT_BKPT     = 0x00640000,

    IG_ATOMIC   = 0x00700000,

    IG_MISC     = 0x00F00000,  // Misc. operations

    IT_CPU      = 0x00F10000,  // CPU operations
    IT_MMU      = 0x00F20000,  // MMU operations
    IT_COPROC   = 0x00F30000,  // Coprocessor operations
};

enum operator {
    I_ABCD      = 0     | IG_ARITH  | IT_BCD    ,
    I_ADD       = 1     | IG_ARITH  | IT_ADD    ,
    I_ADDA      = 2     | IG_ARITH  | IT_ADD    ,
    I_ADDI      = 3     | IG_ARITH  | IT_ADD    ,
    I_ADDQ      = 4     | IG_ARITH  | IT_ADD    ,
    I_ADDX      = 5     | IG_ARITH  | IT_ADD    ,
    I_AND       = 6     | IG_LOGIC  | IT_AND    ,
    I_ANDI      = 7     | IG_LOGIC  | IT_AND    ,
    I_ASL       = 8     | IG_SR     | IT_AS     ,
    I_ASR       = 9     | IG_SR     | IT_AS     ,
    I_Bcc       = 10    | IG_FLOW   | IT_JB     ,
    I_BCHG      = 11    | IG_BITFLD | IT_BIT    ,
    I_BCLR      = 12    | IG_BITFLD | IT_BIT    ,
    I_BFCHG     = 13    | IG_BITFLD | IT_BITFLD ,
    I_BFCLR     = 14    | IG_BITFLD | IT_BITFLD ,
    I_BFEXTS    = 15    | IG_BITFLD | IT_BITFLD ,
    I_BFEXTU    = 16    | IG_BITFLD | IT_BITFLD ,
    I_BFFFO     = 17    | IG_BITFLD | IT_BITFLD ,
    I_BFINS     = 18    | IG_BITFLD | IT_BITFLD ,
    I_BFSET     = 19    | IG_BITFLD | IT_BITFLD ,
    I_BFTST     = 20    | IG_BITFLD | IT_BITFLD ,
    I_BKPT      = 21    | IG_FLOW   | IT_BKPT   ,
    I_BRA       = 22    | IG_FLOW   | IT_JB     ,
    I_BSET      = 23    | IG_BITFLD | IT_BIT    ,
    I_BSR       = 24    | IG_FLOW   | IT_JB     ,
    I_BTST      = 25    | IG_BITFLD | IT_BIT    ,
    I_CAS       = 26    | IG_ATOMIC             ,
    I_CAS2      = 27    | IG_ATOMIC             ,
    I_CHK       = 28    | IG_ATOMIC             ,
    I_CHK2      = 29    | IG_ATOMIC             ,
    I_CLR       = 30    | IG_MISC   | IT_CPU    ,
    I_CMP       = 31    | IG_CMP                ,
    I_CMP2      = 32    | IG_CMP                ,
    I_CMPA      = 33    | IG_CMP                ,
    I_CMPI      = 34    | IG_CMP                ,
    I_CMPM      = 35    | IG_CMP                ,
    I_DBcc      = 36    | IG_FLOW   | IT_JB     ,
    I_DIVS      = 37    | IG_ARITH  | IT_DIV    ,
    I_DIVSL     = 38    | IG_ARITH  | IT_DIV    ,
    I_DIVU      = 39    | IG_ARITH  | IT_DIV    ,
    I_DIVUL     = 40    | IG_ARITH  | IT_DIV    ,
    I_EOR       = 41    | IG_LOGIC  | IT_EOR    ,
    I_EORI      = 42    | IG_LOGIC  | IT_EOR    ,
    I_EXG       = 43    | IG_MISC   | IT_CPU    ,
    I_EXT       = 44    | IG_ARITH  | IT_EXT    ,
    I_EXTB      = 45    | IG_ARITH  | IT_EXT    ,
    I_ILLEGAL   = 46    | IG_MISC   | IT_CPU    ,
    I_JMP       = 47    | IG_FLOW   | IT_JB     ,
    I_JSR       = 48    | IG_FLOW   | IT_JB     ,
    I_LEA       = 49    | IG_MISC   | IT_CPU    ,
    I_LINK      = 50    | IG_MISC   | IT_CPU    ,
    I_LSL       = 51    | IG_SR     | IT_LS     ,
    I_LSR       = 52    | IG_SR     | IT_LS     ,
    I_MOVE      = 53    | IG_MOVE               ,
    I_MOVEA     = 54    | IG_MOVE               ,
    I_MOVEC     = 55    | IG_MOVE   | IT_MOVEC  ,
    I_MOVEM     = 56    | IG_MOVE   | IT_MOVEM  ,
    I_MOVEP     = 57    | IG_MOVE   | IT_MOVEP  ,
    I_MOVEQ     = 58    | IG_MOVE   | IT_MOVEQ  ,
    I_MOVES     = 59    | IG_MOVE               ,
    I_MULS      = 60    | IG_ARITH  | IT_MUL    ,
    I_MULU      = 61    | IG_ARITH  | IT_MUL    ,
    I_NBCD      = 62    | IG_ARITH  | IT_BCD    ,
    I_NEG       = 63    | IG_ARITH  | IT_NEG    ,
    I_NEGX      = 64    | IG_ARITH  | IT_NEG    ,
    I_NOP       = 65    | IG_FLOW               ,
    I_NOT       = 66    | IG_LOGIC  | IT_NOT    ,
    I_OR        = 67    | IG_LOGIC  | IT_OR     ,
    I_ORI       = 68    | IG_LOGIC  | IT_OR     ,
    I_PACK      = 69    | IG_ARITH  | IT_BCD    ,
    I_PEA       = 70    | IG_MISC   | IT_CPU    ,
    I_RESET     = 71    | IG_FLOW               ,
    I_ROL       = 72    | IG_SR     | IT_RO     ,
    I_ROR       = 73    | IG_SR     | IT_RO     ,
    I_ROXL      = 74    | IG_SR     | IT_ROX    ,
    I_ROXR      = 75    | IG_SR     | IT_ROX    ,
    I_RTD       = 76    | IG_FLOW   | IT_RTN    ,
    I_RTE       = 77    | IG_FLOW   | IT_RTN    ,
    I_RTR       = 78    | IG_FLOW   | IT_RTN    ,
    I_RTS       = 79    | IG_FLOW   | IT_RTN    ,
    I_SBCD      = 80    | IG_ARITH  | IT_BCD    ,
    I_Scc       = 81    | IG_MISC   | IT_CPU    ,
    I_STOP      = 82    | IG_FLOW               ,
    I_SUB       = 83    | IG_ARITH  | IT_SUB    ,
    I_SUBA      = 84    | IG_ARITH  | IT_SUB    ,
    I_SUBI      = 85    | IG_ARITH  | IT_SUB    ,
    I_SUBQ      = 86    | IG_ARITH  | IT_SUB    ,
    I_SUBX      = 87    | IG_ARITH  | IT_SUB    ,
    I_SWAP      = 88    | IG_MISC   | IT_CPU    ,
    I_TAS       = 89    | IG_ATOMIC             ,
    I_TRAP      = 90    | IG_FLOW   | IT_TRAP   ,
    I_TRAPcc    = 91    | IG_FLOW   | IT_TRAP   ,
    I_TRAPV     = 92    | IG_FLOW   | IT_TRAP   ,
    I_TST       = 93    | IG_CMP                ,
    I_UNLK      = 94    | IG_MISC   | IT_CPU    ,
    I_UNPK      = 95    | IG_ARITH  | IT_BCD    ,

    I_PFLUSH    = 96    | IG_MISC   | IT_MMU    ,
    I_PFLUSHA   = 97    | IG_MISC   | IT_MMU    ,
    I_PLOADR    = 98    | IG_MISC   | IT_MMU    ,
    I_PLOADW    = 99    | IG_MISC   | IT_MMU    ,
    I_PMOVE     = 100   | IG_MISC   | IT_MMU    ,
    I_PMOVEFD   = 101   | IG_MISC   | IT_MMU    ,
    I_PTESTR    = 102   | IG_MISC   | IT_MMU    ,
    I_PTESTW    = 103   | IG_MISC   | IT_MMU    ,

    I_cpBcc     = 104   | IG_MISC   | IT_COPROC ,
    I_cpDBcc    = 105   | IG_MISC   | IT_COPROC ,
    I_cpScc     = 106   | IG_MISC   | IT_COPROC ,
    I_cpTRAPcc  = 107   | IG_MISC   | IT_COPROC ,
    I_cpGEN     = 108   | IG_MISC   | IT_COPROC ,
    I_cpSAVE    = 109   | IG_MISC   | IT_COPROC ,
    I_cpRESTORE = 110   | IG_MISC   | IT_COPROC ,
};

enum ctrlreg {
    CR_SFC  = 0x000,
    CR_DFC  = 0x001,
    CR_USP  = 0x800,
    CR_VBR  = 0x801,
    CR_CACR = 0x002,
    CR_CAAR = 0x802,
    CR_MSP  = 0x803,
    CR_ISP  = 0x804,
};


////////////////////////////////////////////////////////////////////////////////
// Structs

struct briefext {
#ifdef __LITTLE_ENDIAN__
    uint16_t displacement : 8;
#endif  // __LITTLE_ENDIAN__

    uint16_t dasel : 1;
    uint16_t reg : 3;
    uint16_t idxsz : 1;
    uint16_t scale : 2;
    uint16_t etype : 1;

#ifdef __BIG_ENDIAN__
    uint16_t displacement : 8;
#endif  // __BIG_ENDIAN__
};

struct fullext {
#ifdef __LITTLE_ENDIAN__
    uint16_t bsup : 1;
    uint16_t isup : 1;
    uint16_t bdsz : 2;
    uint16_t mode : 3;
#endif  // __LITTLE_ENDIAN__

    uint16_t dasel : 1;
    uint16_t reg : 3;
    uint16_t idxsz : 1;
    uint16_t scale : 2;
    uint16_t etype : 1;

#ifdef __BIG_ENDIAN__
    uint16_t bsup : 1;
    uint16_t isup : 1;
    uint16_t bdsz : 2;
    uint16_t mode : 3;
#endif  // __BIG_ENDIAN__
};


////////////////////////////////////////////////////////////////////////////////
// Typedefs

typedef enum indir_mode     e_imode;
typedef enum ea_mode        e_eamode;
typedef enum reg_ea         e_eareg;
typedef enum cond           e_cond;

typedef int32_t             e_operator;  // enum operator

typedef struct briefext     s_briefext;
typedef struct fullext      s_fullext;


////////////////////////////////////////////////////////////////////////////////
// Lookup tables

static const char lut_condstr[][3] = {
    "T" , "F" , "HI", "LS", "CC", "CS", "NE", "EQ",
    "VC", "VS", "PL", "MI", "GE", "LT", "GT", "LE",
};
static const char lut_szind[] = { 'B', 'W', 'L' };
static const char lut_cr[][5] = {
    "SFC",      // 0x000
    "DFC",      // 0x001
    "CACR",     // 0x002

    "USP",      // 0x800
    "VBR",      // 0x801
    "CAAR",     // 0x802
    "MSP",      // 0x803
    "ISP",      // 0x804
};


////////////////////////////////////////////////////////////////////////////////
// Macro functions

#define BITFLD(v, bo, bs) ((v & (((1 << bs) - 1) << bo)) >> bo)
#define CHK_SZ(szin, sz) if (szin < sz) { return IE_NELEN; }
#define WSWAP(in) (((in) & 0xFF) << 8) | (((in) & 0xFF00) >> 8)
#define W2L(hi, lo) ((uint32_t)(hi) << 16 | (uint32_t)(lo))


////////////////////////////////////////////////////////////////////////////////
// Internal functions

e_operator _mc68030_getoperator(uint16_t* iwd, size_t isz16);

/**
 * @brief Disassemble extension word(s)
 * 
 * @param iwd    Instruction buffer pointer. Its data follows system endianness.
 * @param isz16  Instruction buffer size in 2-byte unit.
 * @param osz    Operation size. Used only when EA mode is immediate.
 * @param mode   Effective address mode
 * @param reg    Effective address register
 * @param wcur16 Cursor position in current instruction buffer in 2-byte unit.
 * @param buf    Assembly string output buffer.
 * @param len    Length of the string buffer.
 * @return ssize_t 
 */
ssize_t _mc68030_disasm_ext(
    uint16_t* iwd, uint16_t isz16,
    uint8_t osz, uint8_t mode, uint8_t reg, size_t wcur16,
    char* buf, size_t len);

/**
 * @brief Disassembler function pointer
 * 
 * @param iwd   Instruction buffer pointer. Its data follows system endianness.
 * @param isz16 Instruction buffer size in 2-byte unit.
 * @param buf   Assembly string output buffer.
 * @param len   Length of the string buffer.
 * @return ssize_t
 * Instruction size in 2-byte unit if it is positive integer. Else, error code.
 */
typedef ssize_t (*disasm_func)
    (e_operator ote, uint16_t* iwd, size_t isz16, char* buf, size_t len);

/**
 * @brief Operation function definition macro
 * Defines function which conforms type "disasm_func" from given name with prefix "_mc68030_disasm_".
 */
#define DEF_OPFUNC(func) \
    ssize_t _mc68030_disasm_##func \
    (e_operator ote, uint16_t* iwd, size_t isz16, char* buf, size_t len)


////////////////////////////////////////////////////////////////////////////////
// Operation function definitions

DEF_OPFUNC(arith_bcd);
DEF_OPFUNC(arith_add);
DEF_OPFUNC(arith_sub);
DEF_OPFUNC(arith_mul);
DEF_OPFUNC(arith_div);
DEF_OPFUNC(arith_neg);
DEF_OPFUNC(arith_ext);

DEF_OPFUNC(logic_op);

DEF_OPFUNC(move_move);
DEF_OPFUNC(move_movep);
DEF_OPFUNC(move_movec);
DEF_OPFUNC(move_movem);
DEF_OPFUNC(move_moveq);

DEF_OPFUNC(bitfld_bit);
DEF_OPFUNC(bitfld_bitfld);

DEF_OPFUNC(shiftrotate);

DEF_OPFUNC(cmp);

DEF_OPFUNC(flow_other);
DEF_OPFUNC(flow_jb);
DEF_OPFUNC(flow_rtn);
DEF_OPFUNC(flow_trap);
DEF_OPFUNC(flow_bkpt);

DEF_OPFUNC(atomic);

DEF_OPFUNC(misc_cpu);
DEF_OPFUNC(misc_mmu);
DEF_OPFUNC(misc_coproc);

#endif  // __CPU_MC68030_OPERATION_H__
