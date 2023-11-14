#ifndef __MEMORY_MEMORY_H__
#define __MEMORY_MEMORY_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "types.h"

struct memory {
    char* path;
    FILE* file;

    uviptr_t* blkmap;
    size_t blksize;
    size_t blkcnt;
    size_t blkused;

    bool readonly;
    bool bigendian;
};

struct memory* init_memory
    (char* path, bool readonly, size_t blksize, size_t blkcnt, bool bigendian);
int deinit_memory(struct memory* mem);

int _read_memory
    (struct memory* mem, size_t ptr, int wordsize, void* dest, bool raw);
int _write_memory
    (struct memory* mem, size_t ptr, int wordsize, void* src, bool raw);

#define read8_memory(mem, ptr, dest)  _read_memory(mem, ptr, 1, dest, false);
#define read16_memory(mem, ptr, dest) _read_memory(mem, ptr, 2, dest, false);
#define read32_memory(mem, ptr, dest) _read_memory(mem, ptr, 4, dest, false);
#define read64_memory(mem, ptr, dest) _read_memory(mem, ptr, 8, dest, false);

#define write8_memory(mem, ptr, dest)  _write_memory(mem, ptr, 1, dest, false);
#define write16_memory(mem, ptr, dest) _write_memory(mem, ptr, 2, dest, false);
#define write32_memory(mem, ptr, dest) _write_memory(mem, ptr, 4, dest, false);
#define write64_memory(mem, ptr, dest) _write_memory(mem, ptr, 8, dest, false);

#define read8r_memory(mem, ptr, dest)  _read_memory(mem, ptr, 1, dest, true);
#define read16r_memory(mem, ptr, dest) _read_memory(mem, ptr, 2, dest, true);
#define read32r_memory(mem, ptr, dest) _read_memory(mem, ptr, 4, dest, true);
#define read64r_memory(mem, ptr, dest) _read_memory(mem, ptr, 8, dest, true);

#define write8r_memory(mem, ptr, dest)  _write_memory(mem, ptr, 1, dest, true);
#define write16r_memory(mem, ptr, dest) _write_memory(mem, ptr, 2, dest, true);
#define write32r_memory(mem, ptr, dest) _write_memory(mem, ptr, 4, dest, true);
#define write64r_memory(mem, ptr, dest) _write_memory(mem, ptr, 8, dest, true);

#endif  // __MEMORY_MEMORY_H__
