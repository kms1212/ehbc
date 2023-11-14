#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

typedef union {
    void*       raw;

    uint64_t*   u64;
    uint32_t*   u32;
    uint16_t*   u16;
    uint8_t*    u8;
} uviptr_t;

#endif  // __TYPES_H__
