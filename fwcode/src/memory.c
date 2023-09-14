#include "memory.h"
#include "types.h"

ptr_t memcpy(ptr_t dest, const ptr_t src, size_t sz) {
    byte* d = (byte*)dest;
    const byte* s = (const byte*)src;
    while (sz--) *d++ = *s++;
    return dest;
}
