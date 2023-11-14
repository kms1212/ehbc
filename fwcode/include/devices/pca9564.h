#ifndef __DEVICES_PCA9564_H__
#define __DEVICES_PCA9564_H__

#include "error.h"
#include "utils.h"

#define PCA9564_I2CSTA      0x00
#define PCA9564_I2CTO       0x00
#define PCA9564_I2CDAT      0x01
#define PCA9564_I2CADR      0x02
#define PCA9564_I2CCON      0x03

#define PCA9564_CLK_330kHz  0
#define PCA9564_CLK_288kHz  1
#define PCA9564_CLK_217kHz  2
#define PCA9564_CLK_146kHz  3
#define PCA9564_CLK_88kHz   4
#define PCA9564_CLK_59kHz   5
#define PCA9564_CLK_44kHz   6
#define PCA9564_CLK_36kHz   7

union u_pca9564_con {
    uint8_t raw;
    struct {
        unsigned int aa : 1;
        unsigned int ensio : 1;
        unsigned int sta : 1;
        unsigned int sto : 1;
        unsigned int si : 1;
        unsigned int cr : 3;
    };
};

union u_pca9564_to {
    uint8_t raw;
    struct {
        unsigned int te : 1;
        unsigned int to : 7;
    };
};

struct _pca9564_mmio {
    uint8_t sta_to;
    uint8_t dat;
    uint8_t adr;
    union u_pca9564_con con;
};

typedef struct {
    struct _pca9564_mmio* mmio;

    error_t op_err;
    error_t isr_err;

} pca9564_dev_t;

pca9564_dev_t pca9564_init(const void* mmiobase);
error_t pca9564_deinit(pca9564_dev_t* dev);

#endif  // __DEVICES_PCA9564_H__
