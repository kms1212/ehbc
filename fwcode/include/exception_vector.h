/**
 * @file exception_vector.h
 * @author Minsu Kwon (kms1212g@gmail.com)
 * @brief Definitions about the MC68030 exception vector
 * @version r0
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024 Minsu Kwon (kms1212g@gmail.com)
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EHBC_EXCEPTION_VECTOR_H__
#define _EHBC_EXCEPTION_VECTOR_H__

#include "types.h"

struct ExceptionVector {
    ptr_t       initial_sp;
    ptr_t       initial_pc;
    ptr_t       bus_error;
    ptr_t       address_error;
    ptr_t       illegal_instruction;
    ptr_t       divide_by_zero;
    ptr_t       check_instruction;
    ptr_t       trap_instruction;
    ptr_t       privilege_violation;
    ptr_t       trace;
    ptr_t       line_1010_emu;
    ptr_t       line_1111_emu;
    uint32_t    : 32;
    ptr_t       coproc_protocol_volation;
    ptr_t       format_error;
    ptr_t       uninitialized_interrupt;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    ptr_t       spurious_interrupt;
    ptr_t       autovector[7];
    ptr_t       trap[16];
    ptr_t       fpcp_branch_or_set_condition;
    ptr_t       fpcp_inexact_result;
    ptr_t       fpcp_divde_by_zero;
    ptr_t       fpcp_underflow;
    ptr_t       fpcp_operand_error;
    ptr_t       fpcp_overflow;
    ptr_t       fpcp_nan_result;
    uint32_t    : 32;
    ptr_t       mmu_config_error;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    uint32_t    : 32;
    ptr_t       userdef[192];
};

typedef struct ExceptionVector ExceptionVector;

extern ExceptionVector default_exception_vector;

void exception_vector_default_handler();

#endif  // _EHBC_EXCEPTION_VECTOR_H__
