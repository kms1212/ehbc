#include "devices/mc68901.h"

mc68901_dev_t mc68901_init(
    const void* mmiobase,
    const bqueue_t rbuf,
    const bqueue_t wbuf) {
    // Create struct
    mc68901_dev_t dev;
    dev.mmio = (struct _mc68901_mmio*)mmiobase;
    dev.isr_err = E_SUCCESS;
    dev.op_err = E_SUCCESS;
    
    // TODO: Allocate transfer buffer
    // (uint8_t*)malloc(MC68901_RBUF_SIZE);
    // (uint8_t*)malloc(MC68901_WBUF_SIZE);
    dev.rbuf = rbuf;
    dev.wbuf = wbuf;

    // Reset registers
    dev.mmio->gpdr = 0;
    dev.mmio->aer = 0;
    dev.mmio->ddr = 0;
    dev.mmio->iera.raw = 0;
    dev.mmio->ierb.raw = 0;
    dev.mmio->ipra.raw = 0;
    dev.mmio->iprb.raw = 0;
    dev.mmio->isra.raw = 0;
    dev.mmio->isrb.raw = 0;
    dev.mmio->imra.raw = 0;
    dev.mmio->imrb.raw = 0;
    dev.mmio->vr = 0;
    dev.mmio->tacr = 0;
    dev.mmio->tbcr = 0;
    dev.mmio->tcdcr = 0;
    dev.mmio->tadr = 0;
    dev.mmio->tbdr = 0;
    dev.mmio->tcdr = 0;
    dev.mmio->tddr = 0;
    dev.mmio->scr = 0;
    dev.mmio->ucr = 0;
    dev.mmio->rsr = 0;
    dev.mmio->tsr = 0;
    dev.mmio->udr = 0;

    return dev;
}

error_t mc68901_deinit(mc68901_dev_t* dev) {
    // TODO: Deallocate transfer buffer
    
    return E_SUCCESS;
}


int mc68901_usart_config(
    mc68901_dev_t* dev,
    const uint8_t baud,
    uint8_t cfg
) {
    // Timer channel D generates baud rate clock for USART.
    // MC68901 operates at 3.6864MHz.
    // Set the prescaler value and the counter value to generate baud clock.
    // TDDR / TCDCR Configuration table
    // Baud     TDDR    TCDCR                       Description
    // Rate     hex dec hex macro
    // 300      C0  192 x7  MC68901_TIMER_DELAY64   /64 prescaler, 192 counts
    // 600      60  96  x7  MC68901_TIMER_DELAY64   /64 prescaler, 96 counts
    // 1200     30  48  x7  MC68901_TIMER_DELAY64   /64 prescaler, 48 counts
    // 2400     60  96  x3  MC68901_TIMER_DELAY16   /16 prescaler, 96 counts
    // 4800     30  48  x3  MC68901_TIMER_DELAY16   /16 prescaler, 48 counts
    // 9600     60  96  x1  MC68901_TIMER_DELAY4    /4 prescaler, 96 counts
    // 14400    40  64  x1  MC68901_TIMER_DELAY4    /4 prescaler, 64 counts
    // 19200    30  48  x1  MC68901_TIMER_DELAY4    /4 prescaler, 48 counts
    // 38400    18  24  x1  MC68901_TIMER_DELAY4    /4 prescaler, 24 counts
    // 57600    10  16  x1  MC68901_TIMER_DELAY4    /4 prescaler, 16 counts
    // 115200   08  8   x1  MC68901_TIMER_DELAY4    /4 prescaler, 8 counts

    // Timer configuration
    const uint8_t prescaler = (1 << (baud & 0x03)) - 1;  // 1 ~ 0

    dev->mmio->tddr = baud & 0xFC;  // 7 ~ 2
    dev->mmio->tcdcr = (dev->mmio->tcdcr & 0xF0) | prescaler;

    // USART initialization
    dev->mmio->ucr = cfg;

    dev->op_err = E_SUCCESS;
    return 0;
}

int mc68901_usart_write(
    mc68901_dev_t* dev,
    const uint8_t ch
) {
    return bq_push(&(dev->wbuf), ch);
}

size_t mc68901_usart_write_str(
    mc68901_dev_t* dev,
    const uint8_t* str,
    const size_t size
) {
    for (size_t i = 0; i < size; i++)
        if (mc68901_usart_write(dev, str[i]))
            return i;
    dev->op_err = E_SUCCESS;
    return size;
}

int mc68901_usart_read(mc68901_dev_t* dev) {
    return bq_pop(&(dev->wbuf));
}

size_t mc68901_usart_read_until(
    mc68901_dev_t* dev,
    const uint8_t* buf,
    const uint8_t term,
    const size_t size
) {
    for (size_t i = 0; i < size; i++) {
        const int rdat = mc68901_usart_read(dev);
        if ((rdat < 0) | ((uint8_t)rdat == term))
            return i;
    }

    return size;
}


