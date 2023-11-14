#ifndef __COMP_BITOPS__BFEXTEND_H__
#define __COMP_BITOPS__BFEXTEND_H__

#include <stdbool.h>

#include "inline_asm.h"
#include "comp/types/_bittypes.h"

#define __bitfield_extend_signed(src, dest, bfstart, bfsize) \
    __a( \
        __a_line("bfexts (%1){"#bfstart":"#bfsize"}, %0"), \
        __a_list("=d"(dest)), \
        __a_list("a"(&src)), \
    )

#define __bitfield_extend_unsigned(src, dest, bfstart, bfsize) \
    __a( \
        __a_line("bfextu (%1){"#bfstart":"#bfsize"}, %0"), \
        __a_list("=d"(dest)), \
        __a_list("a"(&src)), \
    )

#endif  // __COMP_BITOPS__BFEXTEND_H__
