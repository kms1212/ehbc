#ifndef __SYSTEM_SYSTEM_H__
#define __SYSTEM_SYSTEM_H__

#include "cpu/cpu.h"
#include "memory/memory.h"

struct node {

};

struct system {
    struct generic_cpu* cpu;
    size_t cpucnt;

    struct memory* mem;
    size_t memcnt;

    struct node* node;
    size_t nodecnt;
};



#endif  // __SYSTEM_SYSTEM_H__
