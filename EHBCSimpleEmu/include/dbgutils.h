#ifndef __DBGUTILS_H__
#define __DBGUTILS_H__

#include <stdint.h>
#include <stdlib.h>

#include "types.h"

void hexdump(const void* p, size_t len, uint8_t option);

#endif  // __DBGUTILS_H__
