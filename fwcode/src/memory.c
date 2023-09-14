#include "memory.h"
#include "types.h"

ptr_t memcpy(ptr_t dest, const ptr_t src, size_t sz) {
    BYTE* d = (BYTE*)dest;
    const BYTE* s = (const BYTE*)src;
    while (sz--) *d++ = *s++;
    return dest;
}
