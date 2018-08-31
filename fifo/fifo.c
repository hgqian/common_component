
#include "fifo.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif


void fifo_init(struct fifo *fifo, uint8_t*buffer, uint32_t size)
{
    fifo->in = fifo->out = 0;
    fifo->buffer = buffer;
    fifo->size = size;
}

void fifo_reset(struct fifo *fifo)
{
    fifo->in = fifo->out = 0;
}

int32_t fifo_empty(struct fifo *fifo)
{
    return fifo->in == fifo->out;
}

int32_t fifo_full(struct fifo *fifo)
{
    return fifo->size == (fifo->in - fifo->out);
}

uint32_t fifo_get(struct fifo *fifo, uint8_t* buffer, uint32_t len)
{
    uint32_t l;

    len = min(len, fifo->in - fifo->out);
    l = min(len, fifo->size - (fifo->out % fifo->size));
    hal_clib_memcpy(buffer, fifo->buffer + (fifo->out % fifo->size), l);
    hal_clib_memcpy(buffer + l, fifo->buffer, len - l);
    fifo->out += len;

    if (fifo->in == fifo->out)
        fifo->in = fifo->out = 0;

    return len;
}

uint32_t fifo_put(struct fifo *fifo, uint8_t* buffer, uint32_t len)
{
    uint32_t l;

    len = min(len, fifo->size - fifo->in + fifo->out);
    l = min(len, fifo->size - (fifo->in % fifo->size));
    hal_clib_memcpy(fifo->buffer + (fifo->in % fifo->size), buffer, l);
    hal_clib_memcpy(fifo->buffer, buffer + l, len - l);
    fifo->in += len;
    
    return len;
}

