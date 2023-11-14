#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "types.h"
#include "error.h"
#include "inline_asm.h"

struct exception_vector {
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

typedef uint8_t             irq_t;

extern struct exception_vector c_vector;

#define __isr__ __attribute__((interrupt_handler))

static void __isr__ __default_avec_routine();
static void __isr__ __default_nmi_routine();

static void __isr__ __default_trap_routine();

static void __isr__ __default_isr_bus_error();
static void __isr__ __default_isr_address_error();
static void __isr__ __default_isr_illegal_instruction();
static void __isr__ __default_isr_divide_by_zero();
static void __isr__ __default_isr_check_instruction();
static void __isr__ __default_isr_trap_instruction();
static void __isr__ __default_isr_privilege_violation();
static void __isr__ __default_isr_format_error();
static void __isr__ __default_isr_uninitialized_interrupt();
static void __isr__ __default_isr_spurious_interrupt();
static void __isr__ __default_isr_fpcp_branch_or_set_condition();
static void __isr__ __default_isr_fpcp_inexact_result();
static void __isr__ __default_isr_fpcp_divide_by_zero();
static void __isr__ __default_isr_fpcp_underflow();
static void __isr__ __default_isr_fpcp_operand_error();
static void __isr__ __default_isr_fpcp_overflow();
static void __isr__ __default_isr_fpcp_nan_result();
static void __isr__ __default_isr_mmu_config_error();

#define trap(trapnum) __a(__a_line("trap #"#trapnum),,,);

void init_exceptions();
void set_mask();

#endif  // __EXCEPTIONS_H__
