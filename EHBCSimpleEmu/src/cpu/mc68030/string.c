#include "cpu/mc68030/mc68030.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "cpu/cpu.h"


char* mc68030_strstatus(struct mc68030_cpu* cpu, char* str, size_t len) {
    if (cpu == NULL || str == NULL) return NULL;

    mc68030_strreg(cpu, str, len);

    return str;
}

char* mc68030_strreg(struct mc68030_cpu* cpu, char* str, size_t len) {
    if (cpu == NULL || str == NULL) return NULL;

    snprintf(str, len,
        "D0=%08X D1=%08X D2=%08X D3=%08X\n"
        "D4=%08X D5=%08X D6=%08X D7=%08X\n"
        "A0=%08X A1=%08X A2=%08X A3=%08X\n"
        "A4=%08X A5=%08X A6=%08X A7(SP)=%08X\n"
        "CCR: X=%d N=%d Z=%d V=%d C=%d\n"
        "SR: T=%d S=%d M=%d I=%d\n"
        "PC: %08X VBR: %08X SFC: %X DFC: %X\n"
        "USP=%08X MSP=%08X ISP=%08X"
        "CAAR=%08X CACR=%08X\n"
        "MMUSR=%08X TC=%08X TT0=%08X TT1=%08X\n"
        "CRP=%016"PRIX64" SRP=%016"PRIX64"\n",
        cpu->reg.d[0], cpu->reg.d[1], cpu->reg.d[2], cpu->reg.d[3],
        cpu->reg.d[4], cpu->reg.d[5], cpu->reg.d[6], cpu->reg.d[7],
        cpu->reg.a[0], cpu->reg.a[1], cpu->reg.a[2], cpu->reg.a[3],
        cpu->reg.a[4], cpu->reg.a[5], cpu->reg.a[6], cpu->reg.a[7],
        cpu->reg.sr.ccr.x, cpu->reg.sr.ccr.n, cpu->reg.sr.ccr.z,
        cpu->reg.sr.ccr.v, cpu->reg.sr.ccr.c,
        cpu->reg.sr.t, cpu->reg.sr.s, cpu->reg.sr.m, cpu->reg.sr.i,
        cpu->reg.pc, cpu->reg.vbr, cpu->reg.sfc, cpu->reg.dfc,
        cpu->reg.usp, cpu->reg.msp, cpu->reg.isp,
        cpu->reg.caar.raw, cpu->reg.cacr.raw,
        cpu->reg.mmusr.raw, cpu->reg.tc.raw,
        cpu->reg.tt[0].raw, cpu->reg.tt[1].raw,
        cpu->reg.crp.raw, cpu->reg.srp.raw);

    return str;
}
