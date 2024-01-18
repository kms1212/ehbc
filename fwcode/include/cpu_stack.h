/**
 * @file cpu_stack.h
 * @author Minsu Kwon (kms1212g@gmail.com)
 * @brief Definition of the informations of the initial CPU stack.
 * @version r0
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024 Minsu Kwon (kms1212g@gmail.com)
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EHBC_CPU_STACK_H__
#define _EHBC_CPU_STACK_H__

#include "units.h"

/* Size of initial CPU stack */
#define INITIAL_CPU_STACK_SIZE  64 * KiB

/* Top address of initial CPU stack */
#define INITIAL_CPU_STACK_TOP   INITIAL_CPU_STACK_SIZE + 1 * MiB

#endif  // _EHBC_CPU_STACK_H__
