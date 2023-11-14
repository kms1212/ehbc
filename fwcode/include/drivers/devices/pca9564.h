

// Return device driver informations
#ifdef  __DRIVER_INFO
#undef  __DRIVER_INFO

#include "drivers/_init_drv_info.h"

#define MMIO_SUPPORT
#define DEV_BUS

#else  // __DRIVER_INFO

#ifndef __DRIVERS_DEVICES_PCA9564_H__
#define __DRIVERS_DEVICES_PCA9564_H__

// Header Body
#ifdef USE_MMIO  // Device operations using MMIO bus

// code..

#else  // Device operations using other bus

// code..

#endif  // USE_MMIO

#endif  // __DRIVERS_DEVICES_PCA9564_H__
#endif  // __DRIVER_INFO
