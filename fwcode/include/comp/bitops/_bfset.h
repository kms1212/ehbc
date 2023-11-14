#ifndef __COMP_BITOPS__BFSET_H__
#define __COMP_BITOPS__BFSET_H__

#include <stdbool.h>

#include "inline_asm.h"
#include "comp/types/_bittypes.h"

#define __bitfield_set(dest, bfstart, bfsize) \
    __a( \
        __a_line("bfset (%0){"#bfstart":"#bfsize"}"),, \
        __a_list("a"(dest)), \
        __a_list("memory") \
    )


#endif  // __COMP_BITOPS__BFSET_H__
