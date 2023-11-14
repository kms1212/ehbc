#include "cpu/mc68030/opcode.h"

#include <stdint.h>

#include "cpu/mc68030/_operation.h"
#include "cpu/cpu.h"

static disasm_func _mc68030_disasm_ftbl[16][8] = {
    // Arithmetic operations
    {
        NULL,
        _mc68030_disasm_arith_bcd,
        _mc68030_disasm_arith_add,
        _mc68030_disasm_arith_sub,
        _mc68030_disasm_arith_mul,
        _mc68030_disasm_arith_div,
        _mc68030_disasm_arith_neg,
        _mc68030_disasm_arith_ext,
    },
    // Logical operations
    {
        NULL,
        _mc68030_disasm_logic_op,
        _mc68030_disasm_logic_op,
        _mc68030_disasm_logic_op,
        _mc68030_disasm_logic_op,
        NULL,
        NULL,
        NULL,
    },
    // Move operations
    {
        _mc68030_disasm_move_move,
        _mc68030_disasm_move_movep,
        _mc68030_disasm_move_movec,
        _mc68030_disasm_move_movem,
        _mc68030_disasm_move_moveq,
        NULL,
        NULL,
        NULL,
    },
    // Bit/Bit-field operations
    {
        NULL,
        _mc68030_disasm_bitfld_bit,
        _mc68030_disasm_bitfld_bitfld,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    // Shift/Rotate operations
    {
        NULL,
        _mc68030_disasm_shiftrotate,
        _mc68030_disasm_shiftrotate,
        _mc68030_disasm_shiftrotate,
        _mc68030_disasm_shiftrotate,
        NULL,
        NULL,
        NULL,
    },
    // Compare operations
    {
        _mc68030_disasm_cmp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    // Flow control operations
    {
        _mc68030_disasm_flow_other,
        _mc68030_disasm_flow_jb,
        _mc68030_disasm_flow_rtn,
        _mc68030_disasm_flow_trap,
        _mc68030_disasm_flow_bkpt,
        NULL,
        NULL,
        NULL,
    },
    // Atomic operations
    {
        _mc68030_disasm_atomic,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    // Misc. operations
    {
        NULL,
        _mc68030_disasm_misc_cpu,
        _mc68030_disasm_misc_mmu,
        _mc68030_disasm_misc_coproc,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

ssize_t mc68030_disasm(uint16_t* iwd, size_t isz16, char* buf, size_t len) {
    if (iwd == NULL || buf == NULL) return IE_ERR;

    e_operator operator = _mc68030_getoperator(iwd, isz16);
    if (operator <= 0) return operator;

    uint8_t group = BITFLD(operator, 20, 8);
    uint8_t type = BITFLD(operator, 16, 4);

    if (group > 16) return IE_ERR;

    if (_mc68030_disasm_ftbl[group][type] != NULL)
        return _mc68030_disasm_ftbl[group][type]
            (operator, iwd, isz16, buf, len);
    else
        return IE_ERR;

    return 0;
}
