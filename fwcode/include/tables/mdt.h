// Machine Descriptor Table

#ifndef __TABLES_MDT_H__
#define __TABLES_MDT_H__

#include <stdint.h>

#define MDT_MAGIC   0xD328
#define MDT_VERSION 1

#define MDT_ISA_MC68030   0x5978

#define MDT_FLAG_FPU        0x01

struct MDT {
    uint16_t        mdt_magic;
    uint8_t         mdt_version;
    uint8_t         mdt_length;
    uint16_t        mdt_isa;
    uint16_t        mdt_flags;
    uint32_t        mdt_clock_khz;
    uint8_t         mdt_machine_name[16];
    uint8_t         mdt_cpu_name[16];
};

#endif  // __TABLES_MDT_H__
