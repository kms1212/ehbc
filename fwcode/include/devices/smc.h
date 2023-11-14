#ifndef __DEVICES_SMC_H__
#define __DEVICES_SMC_H__

#include "types.h"
#include "error.h"

// SMC Registers
#define SMC_SR      0x00
#define SMC_CMDR    0x00

// SMC Commands
#define SMC_C_BEEP1     0xE0
#define SMC_C_BEEP2     0xE1
#define SMC_C_BEEP3     0xE2
#define SMC_C_BEEP4     0xE3
#define SMC_C_LBEEP2    0xE4
#define SMC_C_LBEEP3    0xE5
#define SMC_C_LBEEP4    0xE6
#define SMC_C_LBEEP5    0xE7

#define SMC_C_SYSHALT   0xF0
#define SMC_C_RSTACK    0xFF

#endif  // __DEVICES_SMC_H__
