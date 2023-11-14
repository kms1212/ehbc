// Bus driver

#ifndef __DRIVERS_BUS_H__
#define __DRIVERS_BUS_H__

#include <stdint.h>

#include "error.h"

enum bus_status {
    BSTAT_UNINITIALIZED,
    BSTAT_READY,
    BSTAT_BUSY,
    BSTAT_ERROR,
};

#include "drivers/macros/_busdef.h"

DEFINE_BUSOPS_BEGIN(__bus_parent)
DEFINE_BUS_END

DEFINE_BUS_BEGIN(__bus_parent)
DEFINE_BUS_END

#include "drivers/macros/_undef_busdef.h"

#endif  // __DRIVERS_BUS_H__
