/**
 * @file units.h
 * @author Minsu Kwon (kms1212g@gmail.com)
 * @brief SI prefix (+ unit) definitions
 * @version r0
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024 Minsu Kwon (kms1212g@gmail.com)
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _EHBC_UNITS_H__
#define _EHBC_UNITS_H__

#include "types.h"

#define Ki 1024
#define Mi (1024 * Ki)
#define Gi (1024 * Mi)

#define KiB (Ki * sizeof(BYTE))
#define MiB (Mi * sizeof(BYTE))
#define GiB (Gi * sizeof(BYTE))

#endif  // _EHBC_UNITS_H__
