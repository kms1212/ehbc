/**
 * @file types.h
 * @author Minsu Kwon (kms1212g@gmail.com)
 * @brief Type definitions
 * @version r0
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024 Minsu Kwon (kms1212g@gmail.com)
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EHBC_TYPES_H__
#define _EHBC_TYPES_H__

#include <stdint.h>

typedef uint8_t             BYTE;

typedef uint16_t            WORD;

typedef uint32_t            DWORD;
typedef uint32_t            LONG;

typedef uint64_t            QWORD;

typedef void                (*vfunc_t)();

typedef void*               ptr_t;

#define PTR(ptr)            (ptr_t)(ptr)

#endif  // _EHBC_TYPES_H__
