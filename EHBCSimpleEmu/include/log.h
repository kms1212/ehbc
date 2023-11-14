#ifndef __LOG_H__
#define __LOG_H__

#include "defs.h"

#define LL_DEBUG_COLOR      ""
#define LL_VERBOSE_COLOR    ""
#define LL_INFO_COLOR       ""
#define LL_WARNING_COLOR    ANSI_FORE_BYELLOW
#define LL_ERROR_COLOR      ANSI_FORE_BRED
#define LL_FATAL_COLOR      ANSI_FORE_BLACK ANSI_BACK_BRED

// Log level. Higher value, higher critical and lower verbose.
enum loglevel {
    LL_DEBUG = 10,
    LL_VERBOSE = 20,
    LL_INFO = 30,
    LL_WARNING = 40,
    LL_ERROR = 50,
    LL_FATAL = 60
};

void _lprintf(enum loglevel lvl, const char* iden, const char* fmt, ...);

#ifndef LOG_IDEN
#define lprintf(lvl, ...) _lprintf(lvl, __FILE__, __VA_ARGS__)
#else
#define lprintf(lvl, ...) _lprintf(lvl, LOG_IDEN, __VA_ARGS__)
#endif

#endif  // __LOG_H__
