### Simple Ring Buffer

The code below is not a complete example. It uses STM32 HAL, but the library itself does not. 

This shows how you can setup a couple of timers and use callbacks to read and write from the ring buffer. Note that the timers are set to the same period but TIM6 (used for writing to the buffer) is lower priority than TIM7 (used for reading from the buffer).

The dynamic version uses malloc. If this is too spicy, there is also static version.


```
#include <dynamic_ring_buffer.h>
#include <static_ring_buffer.h>


//#define USE_DYNAMIC_RING_BUFFER
#define USE_STATIC_RING_BUFFER

#ifdef USE_DYNAMIC_RING_BUFFER
	#define RBUF_DYNAMIC_SIZE 8
	DynamicRingBuffer_Typedef *rbuf_dynamic;
	DynamicRingBufferItem_Typedef dcount;
#endif

#ifdef USE_STATIC_RING_BUFFER
	#define RBUF_STATIC_SIZE 8
	StaticRingBuffer_Typedef rbuf_static;
	StaticRingBufferItem_Typedef rbuf_static_buf[RBUF_STATIC_SIZE];
	uint8_t scount;
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		#ifdef USE_DYNAMIC_RING_BUFFER
			dynamic_ring_buffer_write(rbuf_dynamic, &dcount);
			dcount++;
		#endif
		#ifdef USE_STATIC_RING_BUFFER
			static_ring_buffer_write(&rbuf_static, &scount);
			scount++;
		#endif
	}
	if(htim->Instance == TIM7)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		#ifdef USE_DYNAMIC_RING_BUFFER
			DynamicRingBufferItem_Typedef read_val = 0;
			dynamic_ring_buffer_read(rbuf_dynamic, &read_val);

		#endif
		#ifdef USE_STATIC_RING_BUFFER
			StaticRingBufferItem_Typedef read_val = 0;
			static_ring_buffer_read(&rbuf_static, &read_val);
			//char out[10];
			//snprintf(out, sizeof(out), "%d\n", read_val);
		#endif
		//SEGGER_RTT_WriteString(0, "TIM7\n");
	}
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();

  // create and initialise the ring buffer object
  #ifdef USE_DYNAMIC_RING_BUFFER
    dynamic_ring_buffer_init(&rbuf_dynamic, RBUF_DYNAMIC_SIZE);
  #endif

  #ifdef USE_STATIC_RING_BUFFER
    static_ring_buffer_init(&rbuf_static, rbuf_static_buf, RBUF_STATIC_SIZE);
  #endif


  // initialise the timers
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);


  while (1)
  {

  }
}

```
