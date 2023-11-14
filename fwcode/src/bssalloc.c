#include <stdint.h>

#define ALLOC_BEGIN 
#define ALLOC_END   

#define AREA(name, type, size) \
    type name[size / sizeof(type)] __attribute__((section(".bss")));

#define kiB         *1024
#define MiB         *1048576

#include "bssalloc.lst"

#undef ALLOC_BEGIN
#undef ALLOC_END
#undef AREA
#undef kiB
#undef MiB