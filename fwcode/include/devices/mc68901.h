#ifndef __DEVICES_MFP_H__
#define __DEVICES_MC68901_H__

#include <stdlib.h>

#include "types.h"
#include "error.h"
#include "utils.h"

#define MC68901_RBUF_SIZE       64
#define MC68901_WBUF_SIZE       64

// MFP Registers
#define MC68901_GPIP            0x00
#define MC68901_AER             0x01
#define MC68901_DDR             0x02
#define MC68901_IERA            0x03
#define MC68901_IERB            0x04
#define MC68901_IPRA            0x05
#define MC68901_IPRB            0x06
#define MC68901_ISRA            0x07
#define MC68901_ISRB            0x08
#define MC68901_IMRA            0x09
#define MC68901_IMRB            0x0A
#define MC68901_VR              0x0B
#define MC68901_TACR            0x0C
#define MC68901_TBCR            0x0D
#define MC68901_TCDCR           0x0E
#define MC68901_TADR            0x0F
#define MC68901_TBDR            0x10
#define MC68901_TCDR            0x11
#define MC68901_TDDR            0x12
#define MC68901_SCR             0x13
#define MC68901_UCR             0x14
#define MC68901_RSR             0x15
#define MC68901_TSR             0x16
#define MC68901_UDR             0x17

#define MC68901_BAUD_300        0xC3
#define MC68901_BAUD_600        0x63
#define MC68901_BAUD_1200       0x33
#define MC68901_BAUD_2400       0x62
#define MC68901_BAUD_4800       0x32
#define MC68901_BAUD_9600       0x61
#define MC68901_BAUD_14400      0x41
#define MC68901_BAUD_19200      0x31
#define MC68901_BAUD_38400      0x19
#define MC68901_BAUD_57600      0x11
#define MC68901_BAUD_115200     0x09

#define MC68901_USART_CHAR8     0x00
#define MC68901_USART_CHAR7     0x20
#define MC68901_USART_CHAR6     0x40
#define MC68901_USART_CHAR5     0x60
#define MC68901_USART_SYNC      0x00
#define MC68901_USART_STOP1     0x08
#define MC68901_USART_STOP1_5   0x10
#define MC68901_USART_STOP2     0x18
#define MC68901_USART_PARITY    0x04
#define MC68901_USART_NOPARITY  0x00
#define MC68901_USART_EVENPAR   0x02
#define MC68901_USART_ODDPAR    0x00
#define MC68901_USART_CLKDIV    0x80
#define MC68901_USART_NOCLKDIV  0x00

#define MC68901_USART_8N1PRESET \
    MC68901_USART_CHAR8 | \
    MC68901_USART_STOP1 | \
    MC68901_USART_NOPARITY | \
    MC68901_USART_NOCLKDIV

#define MC68901_TIMER_STOP      0x0
#define MC68901_TIMER_DELAY4    0x1
#define MC68901_TIMER_DELAY10   0x2
#define MC68901_TIMER_DELAY16   0x3
#define MC68901_TIMER_DELAY50   0x4
#define MC68901_TIMER_DELAY64   0x5
#define MC68901_TIMER_DELAY100  0x6
#define MC68901_TIMER_DELAY200  0x7
#define MC68901_TIMER_EVENTCNT  0x8
#define MC68901_TIMER_WIDTH4    0xA
#define MC68901_TIMER_WIDTH16   0xB
#define MC68901_TIMER_WIDTH50   0xC
#define MC68901_TIMER_WIDTH64   0xD
#define MC68901_TIMER_WIDTH100  0xE
#define MC68901_TIMER_WIDTH200  0xF

union u_mc68901_int_a {
    uint8_t raw;
    struct {
        unsigned int gpip7 : 1;
        unsigned int gpip6 : 1;
        unsigned int timer_a : 1;
        unsigned int usart_rx_buffull : 1;
        unsigned int usart_rx_error : 1;
        unsigned int usart_tx_bufempty : 1;
        unsigned int usart_tx_error : 1;
        unsigned int timer_b : 1;
    };
};

union u_mc68901_int_b {
    uint8_t raw;
    struct {
        unsigned int gpip5 : 1;
        unsigned int gpip4 : 1;
        unsigned int timer_c : 1;
        unsigned int timer_d : 1;
        unsigned int gpip3 : 1;
        unsigned int gpip2 : 1;
        unsigned int gpip1 : 1;
        unsigned int gpip0 : 1;
    };
};

struct _mc68901_mmio {
    uint8_t gpdr;
    uint8_t aer;
    uint8_t ddr;
    union u_mc68901_int_a iera;
    union u_mc68901_int_b ierb;
    union u_mc68901_int_a ipra;
    union u_mc68901_int_b iprb;
    union u_mc68901_int_a isra;
    union u_mc68901_int_b isrb;
    union u_mc68901_int_a imra;
    union u_mc68901_int_b imrb;
    uint8_t vr;
    uint8_t tacr;
    uint8_t tbcr;
    uint8_t tcdcr;
    uint8_t tadr;
    uint8_t tbdr;
    uint8_t tcdr;
    uint8_t tddr;
    uint8_t scr;
    uint8_t ucr;
    uint8_t rsr;
    uint8_t tsr;
    uint8_t udr;
};

typedef struct {
    struct _mc68901_mmio* mmio;

    error_t op_err;
    error_t isr_err;

    bqueue_t rbuf;
    bqueue_t wbuf;
} mc68901_dev_t;

mc68901_dev_t mc68901_init(
    const void* mmiobase,
    const bqueue_t rbuf,
    const bqueue_t wbuf);
error_t mc68901_deinit(mc68901_dev_t* dev);

int mc68901_usart_config(
    mc68901_dev_t* dev,
    const uint8_t baud,
    const uint8_t cfg);

int mc68901_usart_write(
    mc68901_dev_t* dev,
    const uint8_t ch);
size_t mc68901_usart_write_str(
    mc68901_dev_t* dev,
    const uint8_t* str,
    const size_t size);

int mc68901_usart_read(mc68901_dev_t* dev);
size_t mc68901_usart_read_until(
    mc68901_dev_t* dev,
    const uint8_t* buf,
    const uint8_t term,
    const size_t size);
size_t mc68901_usart_read_buf(
    mc68901_dev_t* dev,
    const uint8_t* buf,
    const size_t size);

int mc68901_usart_flush(mc68901_dev_t* dev);

int mc68901_timer_a_reset(mc68901_dev_t* dev);
int mc68901_timer_a_count(mc68901_dev_t* dev, const uint8_t count);
int mc68901_timer_a_mode(mc68901_dev_t* dev, uint8_t mode);

int mc68901_timer_b_reset(mc68901_dev_t* dev);
int mc68901_timer_b_count(mc68901_dev_t* dev, const uint8_t count);
int mc68901_timer_b_mode(mc68901_dev_t* dev, uint8_t mode);

int mc68901_timer_c_reset(mc68901_dev_t* dev);
int mc68901_timer_c_count(mc68901_dev_t* dev, const uint8_t count);
int mc68901_timer_c_mode(mc68901_dev_t* dev, uint8_t mode);

#endif  // __DEVICES_MC68901_H__
