/*
 * RingBuffer.c
 *
 *  Created on: 26 Mar 2021
 *      Author: chris
 */

#include <static_ring_buffer.h>





void static_ring_buffer_init(	StaticRingBuffer_Typedef *buffer_obj,
								StaticRingBufferItem_Typedef static_buf[],
								uint32_t max_size)
{

	assert(( max_size > 0 ));

	// init object members
	buffer_obj->len = 0;

	buffer_obj->head = 0;

	buffer_obj->tail = 0;

	buffer_obj->max = max_size;

	buffer_obj->buf = static_buf;

	for(size_t i = 0; i < max_size; i++)
	 static_buf[i] = 0;

}


void static_ring_buffer_write(StaticRingBuffer_Typedef* buffer_obj, StaticRingBufferItem_Typedef* val)
{


	// set the write val and increment the write index
	buffer_obj->buf[(buffer_obj->head++) & (buffer_obj->max - 1U)] = *val;

	// increment the buffer length
	if(buffer_obj->len < buffer_obj->max)
		buffer_obj->len++;

	// don't let write index overtake read index
	if(buffer_obj->len == buffer_obj->max)
		buffer_obj->tail = buffer_obj->head;

	// wrap around to the start of buffer if at the end
	if(buffer_obj->tail == buffer_obj->max)
		buffer_obj->tail = 0;

	// wrap around to the start of buffer if at the end
	if(buffer_obj->head == buffer_obj->max)
		buffer_obj->head = 0;


}

void static_ring_buffer_read(StaticRingBuffer_Typedef* buffer_obj, StaticRingBufferItem_Typedef* val)
{
	// get the read val
	val = &buffer_obj->buf[ (buffer_obj->tail) & (buffer_obj->max - 1U) ];

	// delete the read val
	buffer_obj->buf[buffer_obj->tail] = 0;

	// increment the read index
	buffer_obj->tail++;

	// decrement the buffer length
	if(buffer_obj->buf > 0)
		buffer_obj->len--;

	// wrap around to the start of buffer if at the end
	if(buffer_obj->tail == buffer_obj->max)
		buffer_obj->tail = 0;


}


/*
char* simple_ring_buffer_tostring(SimpleRingBuffer_Typedef* buf)
{
	char out[(SIMPLE_RING_BUFFER_SIZE*4)+1];

	//snprintf(out, sizeof(out), "\n", buf[0])

	return out;
}
*/





