#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "types.h"

#define DEVICE_STRUCT_START(keyword) \
struct device { \
    dev_t                       id;
    uint8_t                     type;
    struct device_operations*   ops;
     

#define DEVICE_STRUCT_END }



#endif  // __DEVICE_H__
