/**
 * @file exception_vector.c
 * @author Minsu Kwon (kms1212g@gmail.com)
 * @brief Default exception vector declarations
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "exception_vector.h"
#include "cpu_stack.h"

extern void _start(void);

__attribute__((section(".exception_vector")))
ExceptionVector default_exception_vector = {
    .initial_sp                     = PTR(INITIAL_CPU_STACK_TOP),
    .initial_pc                     = _start,

    .bus_error                      = exception_vector_default_handler,
    .address_error                  = exception_vector_default_handler,
    .illegal_instruction            = exception_vector_default_handler,
    .divide_by_zero                 = exception_vector_default_handler,
    .check_instruction              = exception_vector_default_handler,
    .trap_instruction               = exception_vector_default_handler,
    .privilege_violation            = exception_vector_default_handler,
    .format_error                   = exception_vector_default_handler,
    .uninitialized_interrupt        = exception_vector_default_handler,
    .spurious_interrupt             = exception_vector_default_handler,
    .fpcp_branch_or_set_condition   = exception_vector_default_handler,
    .fpcp_inexact_result            = exception_vector_default_handler,
    .fpcp_divde_by_zero             = exception_vector_default_handler,
    .fpcp_underflow                 = exception_vector_default_handler,
    .fpcp_operand_error             = exception_vector_default_handler,
    .fpcp_overflow                  = exception_vector_default_handler,
    .fpcp_nan_result                = exception_vector_default_handler,
    .mmu_config_error               = exception_vector_default_handler,

    .trap                           = { exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler },

    .autovector                     = { exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler,
                                        exception_vector_default_handler },
};

__attribute__((interrupt_handler))
void exception_vector_default_handler() {}
