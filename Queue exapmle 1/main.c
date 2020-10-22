/*
 * Rtos_Ex.c
 *
 * Created: 10/21/2020 6:32:13 AM
 * Author : yehia
 */ 
#define F_CPU 16000000
#include "Atmega32-drivers/Util/STD_types.h "
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Atmega32-drivers/HAL/7Seg/seg.h"
#include "Atmega32-drivers/MCAL/DIO/DIO.h"
#include "util/delay.h"
void Receive(void *p);
void Send(void *p);
xQueueHandle Handle1 ;
int main(void)
{
	Seg_init();
	Handle1 = xQueueCreate(1,sizeof(uint8));
	if (Handle1 != NULL)
	{
			xTaskCreate(Receive,"Read",300,NULL,2,NULL);
			xTaskCreate(Send,"send",300,NULL,2,NULL);
			vTaskStartScheduler();
	}
	else{}

    /* Replace with your application code */
    while (1) 
    {
    }
}

void Receive(void *p)
{
	uint8 read = 0; 
	while(1)
	{
		xQueueReceive(Handle1,&read,portMAX_DELAY);
		Seg_Write(read);
		
		
	}
}
void Send(void *p)
{
	
	DIO_WritePinDir('d',3,STD_IN);
	uint8 counter = 0 ; 
	
	while(1)
	{
		if ((GET_Bit(PIN_D,3)) != 0)
		{
			vTaskDelay(150/portTICK_PERIOD_MS);
			if ((GET_Bit(PIN_D,3)) != 0)
			{
				
				counter++;
			}

		}
		if (counter == 10)
		{
			counter = 0;
		}
		xQueueSendToBack(Handle1,&counter,portMAX_DELAY);
	}
}