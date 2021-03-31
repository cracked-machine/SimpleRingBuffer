/*
 * simple_ring_buffer.h
 *
 *  Created on: 26 Mar 2021
 *      Author: chris
 */

#ifndef STATIC_RING_BUFFER_H_
#define STATIC_RING_BUFFER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Definitions
 */

// Use this to adjust the size of the static pool of ring buffer objects
#define STATIC_RING_BUFFER_MEMORY_POOL_SIZE 1

// Set type here to change which signed/unsigned integer variant used by buffer
typedef uint8_t StaticRingBufferItem_Typedef;

/*
 * Static Ring Buffer Object
 */

typedef struct static_ring_buffer
{
    // population size
    uint32_t len;

    // write index
    uint32_t head;

    // read index
    uint32_t tail;

    // maximum size
    uint32_t max;

    // the buffer
    StaticRingBufferItem_Typedef *buf;

} StaticRingBuffer_Typedef;

#ifdef STATIC_RING_BUFFER_MEMORY_POOL_SIZE
	// the static memory pool
	typedef struct static_ring_buffer_pool
	{
		StaticRingBuffer_Typedef static_ring_buffer_memory_pool[STATIC_RING_BUFFER_MEMORY_POOL_SIZE];

	} StaticRingBufferPool_Typedef;
#endif

/*
 * Function prototypes
 */

void static_ring_buffer_init(	StaticRingBuffer_Typedef *buffer_obj,
								StaticRingBufferItem_Typedef static_buf[],
								uint32_t max_size);

void static_ring_buffer_write(	StaticRingBuffer_Typedef* buffer_obj,
								StaticRingBufferItem_Typedef* val);

void static_ring_buffer_read(	StaticRingBuffer_Typedef* buffer_obj,
								StaticRingBufferItem_Typedef* val);



#endif /* STATIC_RING_BUFFER_H_ */
