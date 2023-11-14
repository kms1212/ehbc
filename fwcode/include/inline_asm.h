#ifndef __INLINE_ASM_H__
#define __INLINE_ASM_H__

#include <stdarg.h>

#define __a(asm, out, in, clob) __asm__ __volatile__ (asm : out : in : clob)
#define __a_line(asm)           asm"\n\t"
#define __a_list(...)           __VA_ARGS__

#endif  // __INLINE_ASMH__
