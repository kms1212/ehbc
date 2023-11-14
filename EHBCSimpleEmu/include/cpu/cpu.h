#ifndef __CPU_CPU_H__
#define __CPU_CPU_H__

#include "cpu/mc68030/mc68030.h"

enum cpu_type {
    CPU_MC68030,
};

enum instr_error {
    IE_ERR = -1,
    IE_UNKNOWN = -2,
    IE_INVALID = -3,
    IE_NELEN = -4,
};

struct generic_cpu {
    enum cpu_type type;

    union {
        struct mc68030_cpu mc68030;
    };
};

#endif  // __CPU_CPU_H__
