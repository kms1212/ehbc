// Fixed (non-PnP) Peripheral Descriptor Table

#ifndef __TABLES_FPDT_H__
#define __TABLES_FPDT_H__

#include <stdint.h>

#include "types.h"

#define FPDT_MAGIC      0x2782
#define FPDT_VERSION    1

#define FPDT_MMIO       0

#define FPDT_VID_SYS    0x00
#define FPDT_PID_SMC    0x00
#define FPDT_PID_CDC    0x01
#define FPDT_PID_SBC    0x02

#define FPDT_ATTR_MMIO_BOT      1
#define FPDT_ATTR_MMIO_TOP      2

#define FPDT_BUS_CONTROLLER     1

typedef uint8_t bus_t;
typedef uint16_t dev_t;

struct FPDT_bus;

struct FPDT_dev {
    dev_t               dev_id;
    uint16_t            :16;

    uint16_t            dev_vid;
    uint16_t            dev_pid;
    uint8_t             dev_name[10];

    uint16_t            dev_flag;
    uint16_t            :16;

    struct FPDT_bus*    dev_bus;

    uint8_t             dev_attr_cnt;
};

struct FPDT_bus {
    bus_t               bus_id;
    uint32_t            :24;

    struct FPDT_dev*    bus_controller;

    uint8_t             bus_name[8];

    uint8_t             bus_dev_cnt;
};

struct FPDT_header {
    uint16_t            fpdt_magic;
    uint8_t             fpdt_version;
    uint8_t             :8;
    
    uint16_t            dev_cnt;
    uint8_t             bus_cnt;
    uint8_t             :8;

    uint32_t            devtbl_base;
    uint32_t            bustbl_base;
};

extern struct FPDT root_fpdt;

#endif  // __TABLES_FPDT_H__
