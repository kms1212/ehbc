#ifndef __CPU_MC68030_MC68030_H__
#define __CPU_MC68030_MC68030_H__

#include "cpu/mc68030/register.h"
#include "cpu/mc68030/opcode.h"

#define __EMU_MC68030_ENABLED__

struct system;
struct memory;

struct mc68030_cpu {
    struct mc68030_register reg;

    struct memory* udef;
    struct memory* udata;
    struct memory* uprog;
    struct memory* sdata;
    struct memory* sprog;
};


int mc68030_exec(struct mc68030_cpu* cpu, struct system* system);

ssize_t mc68030_disasm(uint16_t* iwd, size_t isz16, char* buf, size_t len);

char* mc68030_strstatus(struct mc68030_cpu* cpu, char* str, size_t len);
char* mc68030_strreg(struct mc68030_cpu* cpu, char* str, size_t len);

#endif  // __CPU_MC68030_MC68030_H__
