// When you include a header of a device driver, you have to request the inform-
// ation of the driver by defining the macro "__DRIVER_INFO". After the "includ-
// e" directive, macros that contains some information of the driver will be de-
// fined.
// Possible macros list:
// - __MMIO_SUPPORT
// - __DMA_SUPPORT
// - __ISR_FUNCTION
// - __TYPE_BUSCONTROLLER
// - __TYPE_PERIPHERAL
// - __BUS_NAME
// - __BUS_OPS_STRUCT
// - __BUS_
// When the device you want to control works as a bus controller, You have to
// notify some additional information to the source which included this header.
// 
// - __BUS_OPS_STRUCT
// - __BUS_OPS

// Return device driver informations
#ifdef  __DRIVER_INFO
#undef  __DRIVER_INFO

#include "drivers/_init_drv_info.h"

#define __MMIO_SUPPORT
#define __DMA_SUPPORT
#define __ISR_FUNCTION  __isr_pca9564
#define __DEV_BUS

/*
    Preprocessor macro inputs:
        __DRIVER_INFO
    Preprocessor macro outputs:
        __MMIO_SUPPORT
        __DMA_SUPPORT
        __ISR_FUNCTION
        __DEV_BUS
*/

#else  // __DRIVER_INFO

#ifndef __DRIVERS_DEVICES___EXAMPLE___H__
#define __DRIVERS_DEVICES___EXAMPLE___H__

#include "drivers/bus.h"
#include "drivers/bus/i2c.h"
// includes..

#ifdef USE_MMIO  // Device operations using MMIO bus

// code..

void __isr_pca9564() {

}

#else  // Device operations using other bus

// code..

void __isr_pca9564() {
    
}   

#endif  // USE_MMIO

// Bus operation struct
extern struct i2c_bus_operations busops;

#endif  // __DRIVERS_DEVICES___EXAMPLE___H__

/*
    Preprocessor macro inputs:
        __BUS
    Preprocessor macro outputs:
        __MMIO_SUPPORT
        __DMA_SUPPORT
        __ISR_FUNCTION
        __DEV_BUS
*/

#endif  // __DRIVER_INFO
