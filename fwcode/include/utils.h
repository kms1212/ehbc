#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>

#include "error.h"

#define iceil(x, y, type) (type)((x + y) / y)
#define ifloor(x, y, type) (type)(x / y)


typedef struct {
    size_t top, bottom, size;
    uint8_t* array;
    size_t arrsize;
} bqueue_t;

bqueue_t bq_create(uint8_t* base, const size_t size);

error_t bq_push(bqueue_t* bq, const uint8_t el);
int bq_pop(bqueue_t* bq);

int bq_isempty(bqueue_t* bq);
int bq_isfull(bqueue_t* bq);
int bq_clear(bqueue_t* bq);


#endif  // __UTILS_H__
