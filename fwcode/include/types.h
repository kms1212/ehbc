#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

typedef uint8_t             byte;
typedef uint8_t             BYTE;

typedef uint16_t            word;
typedef uint16_t            WORD;

typedef uint32_t            dword;
typedef uint32_t            DWORD;

typedef uint64_t            qword;
typedef uint64_t            QWORD;

typedef void                (*vfunc_t)();

typedef void*               ptr_t;

#define PTR(ptr)    (ptr_t)ptr

#endif  // __TYPES_H__
