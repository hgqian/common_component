
#ifndef __FIFO_H__
#define __FIFO_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <string.h>

#define hal_clib_memset             memset
#define hal_clib_memcpy             memcpy

struct fifo {
    uint8_t* buffer;
    uint32_t size;
    uint32_t in;
    uint32_t out;
} fifo_t;


extern void     fifo_init(struct fifo *fifo, uint8_t*buffer, uint32_t size);
extern void     fifo_reset(struct fifo *fifo);
extern int32_t  fifo_empty(struct fifo *fifo);
extern int32_t  fifo_full(struct fifo *fifo);
extern uint32_t fifo_get(struct fifo *fifo, uint8_t* buffer, uint32_t len);
extern uint32_t fifo_put(struct fifo *fifo, uint8_t* buffer, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif
