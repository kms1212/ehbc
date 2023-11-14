#ifndef __BSSALLOC_H__
#define __BSSALLOC_H__

#include <stdint.h>

#define ALLOC_BEGIN 
#define ALLOC_END   

#define AREA(name, type, size) \
    extern type name[size / sizeof(type)];

#define kiB         *1024
#define MiB         *1048576

#include "bssalloc.lst"

#undef ALLOC_BEGIN
#undef ALLOC_END
#undef AREA
#undef kiB
#undef MiB

#endif  // __BSSALLOC_H__
