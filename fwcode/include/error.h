#ifndef __ERROR_H__
#define __ERROR_H__

#include "types.h"

#ifndef __ERROR_T_DEFINED__
#define __ERROR_T_DEFINED__
typedef int error_t;
#endif  // __ERROR_T_DEFINED__

// TODO: Error code list
#define E_SUCCESS       0
#define E_STUB          1
#define E_NOTIMPL       2
#define E_EXTERN        3
#define E_PARITY        4
#define E_STATUS        5
#define E_NOPERM        6
#define E_UNAVAIL       7
#define E_TIMEOUT       8
#define E_INVADDR       9
#define E_NUMERIC       10
#define E_UNDERFLOW     11
#define E_OVERFLOW      12

// TODO: Error handler struct
struct err_handler {
    vfunc_t eh_stub;
    vfunc_t eh_notimpl;
    vfunc_t eh_extern;
    vfunc_t eh_parity;
    vfunc_t eh_status;
    vfunc_t eh_noperm;
    vfunc_t eh_unavail;
    vfunc_t eh_timeout;
    vfunc_t eh_invaddr;
    vfunc_t eh_numeric;
    vfunc_t eh_underflow;
    vfunc_t eh_overflow;
};

error_t wrapper(const error_t func, const struct err_handler* eh);
error_t _stub(const char* file, const int line, const char* msg);

#define STUB(str) _stub(__FILE__, __LINE__, msg)

#endif  // __ERROR_H__
