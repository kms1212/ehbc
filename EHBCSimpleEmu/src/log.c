
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "compat.h"
#include "params.h"
#include "defs.h"

void _lprintf(enum loglevel lvl, const char* iden, const char* fmt, ...) {
    struct param* param = get_param();

    if (param->p_loglvl <= lvl && param->p_logstream != NULL) {
        time_t ts_sec;
        long ts_nsec;
        struct tm ts_cvt;
        char timestr[26];
        char* lvlstr;
        char fmtstr[512];

        get_timestamp(&ts_nsec, &ts_sec);
        localtime_r(&ts_sec, &ts_cvt);
        asctime_r(&ts_cvt, timestr);
        timestr[24] = 0;

        if (param->p_color) {
            switch (lvl) {
                case LL_DEBUG:
                    lvlstr = LL_DEBUG_COLOR"debug"ANSI_COLOR_RESET;
                    break;
                case LL_VERBOSE:
                    lvlstr = LL_VERBOSE_COLOR"verbose"ANSI_COLOR_RESET;
                    break;
                case LL_INFO:
                    lvlstr = LL_INFO_COLOR"info"ANSI_COLOR_RESET;
                    break;
                case LL_WARNING:
                    lvlstr = LL_WARNING_COLOR"WARNING"ANSI_COLOR_RESET;
                    break;
                case LL_ERROR:
                    lvlstr = LL_ERROR_COLOR"ERROR"ANSI_COLOR_RESET;
                    break;
                case LL_FATAL:
                    lvlstr = LL_FATAL_COLOR"FATAL"ANSI_COLOR_RESET;
                    break;
                default:
                    break;
            }
        } else {
            switch (lvl) {
                case LL_DEBUG:
                    lvlstr = "debug";
                    break;
                case LL_VERBOSE:
                    lvlstr = "verbose";
                    break;
                case LL_INFO:
                    lvlstr = "info";
                    break;
                case LL_WARNING:
                    lvlstr = "WARNING";
                    break;
                case LL_ERROR:
                    lvlstr = "ERROR";
                    break;
                case LL_FATAL:
                    lvlstr = "FATAL";
                    break;
                default:
                    break;
            }
        }

        va_list arg_ptr;
        va_start(arg_ptr, fmt);
        vsnprintf(fmtstr, 512, fmt, arg_ptr);

        fprintf(param->p_logstream,
            "%04d-%02d-%02d %02d:%02d:%02d.%03ld [%s] %s: %s\n",
            ts_cvt.tm_year + 1900, ts_cvt.tm_mon + 1, ts_cvt.tm_mday,
            ts_cvt.tm_hour, ts_cvt.tm_min, ts_cvt.tm_sec, ts_nsec / 1000000,
            iden, lvlstr, fmtstr);
    }
}
