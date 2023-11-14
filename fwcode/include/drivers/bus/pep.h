#ifndef __DRIVERS_BUS_PEP_H__
#define __DRIVERS_BUS_PEP_H__

#include "_default.h"

#undef bus_read
#undef bus_write

// #define bus_init(...)       ;
// #define bus_deinit(...)     ;
#define bus_read(method, addr, var)     pep_read(method, addr);
#define bus_write(method, addr, data)   *(addr) = data
// #define bus_config(...)     ;
// #define bus_deinit(...)     ;

#define PEP_RMEM        0x0
#define PEP_WMEM        0x0
#define PEP_RMEM_SEQ    0x0
#define PEP_WMEM_SEQ    0x0
#define PEP_RIO         0x0
#define PEP_WIO         0x0
#define PEP_RIO_SEQ     0x0
#define PEP_WIO_SEQ     0x0

#define BUS_PEP     1

#endif  // __DRIVERS_BUS_PEP_H__
