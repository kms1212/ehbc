#include "memory/memory.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "compat.h"
#include "log.h"
#include "types.h"
#include "dbgutils.h"

struct memory* init_memory(
    char* path, bool readonly, size_t blksize, size_t blkcnt, bool bigendian) {
    typedef struct memory memory;
    memory* mem = (memory*)malloc(sizeof(memory));

    if (path != NULL) {
        mem->path = (char*)malloc(strnlen(path, 256));
        strncpy(mem->path, path, 256);
        mem->file = fopen(mem->path, "rb");
        if (mem->file == NULL) {
            lprintf(LL_ERROR, "Error reading file");
        }
    } else {
        mem->path = NULL;
        mem->file = NULL;
    }

    mem->readonly = readonly;
    mem->bigendian = bigendian;
    mem->blksize = blksize;
    mem->blkcnt = blkcnt;
    mem->blkused = 0;

    mem->blkmap = (uviptr_t*)calloc(blkcnt, sizeof(uviptr_t*));

    return mem;
}

int deinit_memory(struct memory* mem) {
    if (mem == NULL) {
        return 1;
    }

    for (int i = 0; i < mem->blkcnt; i++) {
        if (mem->blkmap[i].raw != NULL)
            free(mem->blkmap[i].raw);
    }

    free(mem->blkmap);

    if (mem->path != NULL)
        free(mem->path);

    if (mem->file != NULL)
        fclose(mem->file);

    free(mem);

    return 0;
}

int _alloc_memory_block(struct memory* mem, size_t blk) {
    if (mem == NULL || mem->blkmap == NULL || mem->blkcnt <= blk) return 1;
    lprintf(LL_DEBUG, "Allocating memory block");

    if (mem->blkmap[blk].raw == NULL) {
        mem->blkmap[blk].raw = calloc(mem->blksize, sizeof(uint8_t));
        mem->blkused++;

        if (mem->file != NULL) {
            fseek(mem->file, mem->blksize * blk, SEEK_SET);
            fread(mem->blkmap[blk].raw, mem->blksize, 1, mem->file);
        }
        return 0;
    } else {
        return 1;
    }
}

int _copy_word(void* dest, void* src, int wordsize, bool bigendian, bool raw) {
    if (dest == NULL || src == NULL) return 1;
    uviptr_t d = { .raw = dest }, s = { .raw = src };

#if _HOST_BYTE_ORDER == __LITTLE_ENDIAN__
    bool flip = bigendian;
#else
    bool flip = !bigendian;
#endif
    flip = flip && !raw;

    if (!flip) {
        switch (wordsize) {
            case 1:
                *d.u8 = *s.u8;
                break;
            case 2:
                *d.u16 = *s.u16;
                break;
            case 4:
                *d.u32 = *s.u32;
                break;
            case 8:
                *d.u64 = *s.u64;
                break;
            default:
                return 1;
        }
    } else {
        switch (wordsize) {
            case 1:
                *d.u8 = *s.u8;
                break;
            case 2:
                *d.u16 =
                    (*s.u16 & 0xFF00) >> 8u |
                    (*s.u16 & 0x00FF) << 8u;
                break;
            case 4:
                *d.u32 =
                    (*s.u32 & 0xFF000000) >> 24u |
                    (*s.u32 & 0x00FF0000) >>  8u |
                    (*s.u32 & 0x0000FF00) <<  8u |
                    (*s.u32 & 0x000000FF) << 24u;
                break;
            case 8:
                *d.u64 =
                    (*s.u64 & 0xFF00000000000000) >> 56u |
                    (*s.u64 & 0x00FF000000000000) >> 40u |
                    (*s.u64 & 0x0000FF0000000000) >> 24u |
                    (*s.u64 & 0x000000FF00000000) >>  8u |
                    (*s.u64 & 0x00000000FF000000) <<  8u |
                    (*s.u64 & 0x0000000000FF0000) << 24u |
                    (*s.u64 & 0x000000000000FF00) << 40u |
                    (*s.u64 & 0x00000000000000FF) << 56u;
                break;
            default:
                return 1;
        }
    }


    return 0;
}

int _read_memory
    (struct memory* mem, size_t ptr, int wordsize, void* dest, bool raw) {
    if (mem == NULL || mem->blkmap == NULL || dest == NULL) return 1;

    size_t blk = ptr / mem->blksize;
    size_t offset = ptr % mem->blksize;

    if (mem->blkcnt <= blk) return 1;
    if (mem->blksize <= offset) return 1;

    if (mem->blkmap[blk].raw == NULL) _alloc_memory_block(mem, blk);

    return _copy_word(dest, mem->blkmap[blk].u8 + offset, wordsize,
        mem->bigendian, raw);
}

int _write_memory
    (struct memory* mem, size_t ptr, int wordsize, void* src, bool raw) {
    if (mem == NULL || mem->blkmap == NULL || src == NULL) return 1;
    if (mem->readonly) return 1;

    size_t blk = ptr / mem->blksize;
    size_t offset = ptr % mem->blksize;

    if (mem->blkcnt <= blk) return 1;
    if (mem->blksize <= offset) return 1;

    if (mem->blkmap[blk].raw == NULL) _alloc_memory_block(mem, blk);

    return _copy_word(mem->blkmap[blk].u8 + offset, src, wordsize,
        mem->bigendian, raw);
}
