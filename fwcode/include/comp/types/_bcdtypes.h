#ifndef __COMP_TYPES__BCDTYPES_H__
#define __COMP_TYPES__BCDTYPES_H__

#include <stdint.h>

typedef uint8_t     __bcd_t;
typedef uint8_t     __bcd_precision_t;

typedef struct {
    __bcd_t*            bcd_base;
    __bcd_precision_t   bcd_precision;
} __bcd_ap_t;

#endif  // __COMP_TYPES__BCDTYPES_H__
