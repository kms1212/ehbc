#ifndef __MEMORY_MEMSPACE_H__
#define __MEMORY_MEMSPACE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct mem_space_elem {
    size_t base;
    size_t size;
};

int add_mem_space();

#endif  // __MEMORY_MEMSPACE_H__
