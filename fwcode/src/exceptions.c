#include "exceptions.h"

#include <stdlib.h>

struct exception_vector c_vector = {
        .initial_sp                     = NULL,
        .initial_pc                     = NULL,

        .bus_error                      = __default_isr_bus_error,
        .address_error                  = __default_isr_address_error,
        .illegal_instruction            = __default_isr_illegal_instruction,
        .divide_by_zero                 = __default_isr_divide_by_zero,
        .check_instruction              = __default_isr_check_instruction,
        .trap_instruction               = __default_isr_trap_instruction,
        .privilege_violation            = __default_isr_privilege_violation,
        .format_error                   = __default_isr_format_error,
        .uninitialized_interrupt        = __default_isr_uninitialized_interrupt,
        .spurious_interrupt             = __default_isr_spurious_interrupt,
        .fpcp_branch_or_set_condition   = __default_isr_fpcp_branch_or_set_condition,
        .fpcp_inexact_result            = __default_isr_fpcp_inexact_result,
        .fpcp_divde_by_zero             = __default_isr_fpcp_divide_by_zero,
        .fpcp_underflow                 = __default_isr_fpcp_underflow,
        .fpcp_operand_error             = __default_isr_fpcp_operand_error,
        .fpcp_overflow                  = __default_isr_fpcp_overflow,
        .fpcp_nan_result                = __default_isr_fpcp_nan_result,
        .mmu_config_error               = __default_isr_mmu_config_error,

        .trap                           = { __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine,
                                            __default_trap_routine },

        .autovector                     = { __default_avec_routine,
                                            __default_avec_routine,
                                            __default_avec_routine,
                                            __default_avec_routine,
                                            __default_avec_routine,
                                            __default_avec_routine,
                                            __default_nmi_routine },
    };

static void __isr__ __default_avec_routine() {}

static void __isr__ __default_nmi_routine() {}

static void __isr__ __default_trap_routine() {}

static void __isr__ __default_isr_bus_error() {}
static void __isr__ __default_isr_address_error() {}
static void __isr__ __default_isr_illegal_instruction() {}
static void __isr__ __default_isr_divide_by_zero() {}
static void __isr__ __default_isr_check_instruction() {}
static void __isr__ __default_isr_trap_instruction() {}
static void __isr__ __default_isr_privilege_violation() {}
static void __isr__ __default_isr_format_error() {}
static void __isr__ __default_isr_uninitialized_interrupt() {}
static void __isr__ __default_isr_spurious_interrupt() {}
static void __isr__ __default_isr_fpcp_branch_or_set_condition() {}
static void __isr__ __default_isr_fpcp_inexact_result() {}
static void __isr__ __default_isr_fpcp_divide_by_zero() {}
static void __isr__ __default_isr_fpcp_underflow() {}
static void __isr__ __default_isr_fpcp_operand_error() {}
static void __isr__ __default_isr_fpcp_overflow() {}
static void __isr__ __default_isr_fpcp_nan_result() {}
static void __isr__ __default_isr_mmu_config_error() {}

