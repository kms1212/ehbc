#ifndef __COMPAT_H__
#define __COMPAT_H__

// Check if POSIX is implemented
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))

#include <unistd.h>

#if defined(_POSIX_VERSION)  // TODO: Check POSIX version

#define __USE_POSIX__
#include "posix/posix.h"

#endif

// TODO: Add support for Windows API

#else

#error "POSIX is not implemented for this target."

#endif


#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || \
    defined(__BIG_ENDIAN__) || defined(__BIG_ENDIAN) || defined(_BIG_ENDIAN)

#define _HOST_BYTE_ORDER    __BIG_ENDIAN__

#else

#define _HOST_BYTE_ORDER    __LITTLE_ENDIAN__

#endif

#endif  // __COMPAT_H__
