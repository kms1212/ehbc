#ifndef __COMP_BITOPS__BFINSERT_H__
#define __COMP_BITOPS__BFINSERT_H__

#include <stdbool.h>

#include "inline_asm.h"
#include "comp/types/_bittypes.h"

#define __bitfield_insert(src, dest, bfstart, bfsize) \
    __a( \
        __a_line("bfins %1, (%0){"#bfstart":"#bfsize"}"),, \
        __a_list("a"(dest), "d"(src)), \
        __a_list("memory") \
    )

#endif  // __COMP_BITOPS__BFINSERT_H__
