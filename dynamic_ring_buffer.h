/*
 * dynamic_ring_buffer.h
 *
 *  Created on: 26 Mar 2021
 *      Author: chris
 */

#ifndef _DYNAMIC_RING_BUFFER_H_
#define _DYNAMIC_RING_BUFFER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Definitions
 */

// Use this to adjust the size of the static pool of ring buffer objects
#define DYNAMIC_RING_BUFFER_MEMORY_POOL_SIZE 10

// Set type here to change which signed/unsigned integer variant used by buffer
typedef uint8_t DynamicRingBufferItem_Typedef;

/*
 * Dynamic Ring Buffer Object
 */

typedef struct dynamic_ring_buffer
{
    // population size
    uint32_t len;

    // write index
    uint32_t head;

    // read index
    uint32_t tail;

    // maximum size
    uint32_t max;

    // the buffer - FAM!
    DynamicRingBufferItem_Typedef buf[];

} DynamicRingBuffer_Typedef;

// the static memory pool
typedef struct dynamic_ring_buffer_pool
{
	DynamicRingBuffer_Typedef dynamic_ring_buffer_memory_pool[DYNAMIC_RING_BUFFER_MEMORY_POOL_SIZE];

} DynamicRingBufferPool_Typedef;



/*
 * Function prototypes
 */

void dynamic_ring_buffer_init(DynamicRingBuffer_Typedef **buffer_obj, size_t max_size);
void dynamic_ring_buffer_write(DynamicRingBuffer_Typedef* buffer_obj, DynamicRingBufferItem_Typedef* val);
void dynamic_ring_buffer_read(DynamicRingBuffer_Typedef* buffer_obj, DynamicRingBufferItem_Typedef* val);
void dynamic_ring_buffer_destroy(DynamicRingBuffer_Typedef* buffer_obj);
//char* dynamic_ring_buffer_tostring(SimpleRingBuffer_Typedef* buffer_obj);

#endif /* _DYNAMIC_RING_BUFFER_H_ */
