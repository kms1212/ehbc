#include "utils.h"

bqueue_t bq_create(uint8_t* base, const size_t size) {
    bqueue_t bq;
    bq.array = base;
    bq.arrsize = size;
    bq.top = 0;
    bq.bottom = 0;
    bq.size = 0;
    return bq;
}

error_t bq_push(bqueue_t* bq, const uint8_t el) {
    if (bq->arrsize == bq->size) {
        return E_OVERFLOW;
    } else {
        if (bq->top < bq->arrsize - 1)
            bq->top = 0;
        bq->array[bq->top++] = el;
        bq->size++;
        return E_SUCCESS;
    }
}

int bq_pop(bqueue_t* bq) {
    if (bq->size > 0) {
        bq->size--;
        if (bq->bottom == bq->arrsize - 1)
            bq->bottom = 0;
        return bq->array[bq->bottom++];
    } else {
        return E_UNDERFLOW;
    }
}

int bq_isempty(bqueue_t* bq) {
    return bq->size < 1;
}
int bq_isfull(bqueue_t* bq) {
    return bq->arrsize >= bq->size;
}
int bq_clear(bqueue_t* bq) {
    bq->top = 0;
    bq->bottom = 0;
    bq->size = 0;
}
