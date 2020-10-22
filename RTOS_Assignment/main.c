/*
 * RTOS_Assignment.c
 *
 * Created: 10/22/2020 4:21:00 PM
 * Author : yehia
 */ 
#include "Atmega32-drivers/RTOS/FreeRTOS.h"
#include "Atmega32-drivers/RTOS/task.h"
#include "Atmega32-drivers/RTOS/queue.h"
#include "Atmega32-drivers/HAL/LCD/LCD.h"
#include "Atmega32-drivers/HAL/KeyPad/KeyPad.h"
xQueueHandle kpVal;
void kp_Send(void *p);
void Seg_Receive(void *p);
int main(void)
{
    /* Replace with your application code */ 
	kpVal = xQueueCreate(1,sizeof(uint8));
	xTaskCreate(kp_Send,"Send",200,NULL,1,NULL);
	xTaskCreate(Seg_Receive,"Receive",200,NULL,2,NULL);
	vTaskStartScheduler();
    while (1) 
    {
    }
}
void kp_Send(void *p)
{
	KP_VidInit();
	uint8 Key ;
	
	while (1)
	{
		Key = KP_u8GetKey();
		xQueueSendToBack(kpVal,&Key,portMAX_DELAY);
		vTaskDelay(250/portTICK_PERIOD_MS);
	}
	
}
void Seg_Receive(void *p)
{
	LCD_init();
	uint8 receive;
	while(1)
	{
		xQueueReceive(kpVal,&receive,portMAX_DELAY);
		LCD_SendData(receive);
		
	}
	
}

