/*!
    \file    main.c
    \brief   led spark with systick, USART print and key example

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x 
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/


#include "TCA6408.h"
#include "dev_iic.h"
#include "TCA9548.h"
#include "pannel.h"
#include "gd32f30x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "gd32f303e_eval.h"
#include "PCA9544.h"
#include "sabre9018.h"
#include "dev_key_led.h"
#include "icm42688.h"

extern int earphone_volume;
extern int earphone_volume_reg;
extern int oled_bright;
extern int oled_bright_reg;

SemaphoreHandle_t xBinarySemaphore;
QueueHandle_t xQueue;

TaskHandle_t icm42688Task_Handle;
TaskHandle_t KeyValueTask_Handle;
TaskHandle_t LogPrintTask_Handle;
TaskHandle_t USARTCMDTask_Handle;

#define KeyValue_PRIO (tskIDLE_PRIORITY + 2)
#define LogPrint_PRIO (tskIDLE_PRIORITY + 2)
#define icm42688_PRIO (tskIDLE_PRIORITY + 2)
#define UsartCmd_PRIO (tskIDLE_PRIORITY + 1)
/*!
    \brief      main init
    \param[in]  none
    \param[out] none
    \retval     none
*/

void USART_cmd_task(void * pvParameters)
{
	char receive_buf[128];
	printf("\r\n USART_cmd_task");

	while(1)
	{
		scanf("%s", receive_buf);
		if(receive_buf[0] == 0x01)
		{
			sabre9018_print(SABRE9018_REG_VOLUME_1);
			sabre9018_print(SABRE9018_REG_VOLUME_2);
			sabre9018_print(SABRE9018_REG_CHIPSTATUS);	
			sabre9018_print(SABRE9018_REG_READONLY);	
		}
		
		if(receive_buf[0] == 0x08)
				earphone_volume = receive_buf[1];
		if(receive_buf[0] == 0x0F)
				oled_bright = receive_buf[1];
		vTaskDelay(200);
	}
}

void icm42688_data_task(void * pvParameters)
{
	unsigned char acc[6];
	unsigned char gyro[6];
	unsigned char temp[2];
	int AccX,AccY,AccZ;
	int GyroX,GyroY,GyroZ;
	int Temp;

	while(1)
	{
		icm42688_get_acc(acc);
		icm42688_get_gyro(gyro);
		icm42688_get_temp(temp);
		AccX = (0x00FF & acc[0]) + ((0x00FF & acc[1]) << 8);
		AccY = (0x00FF & acc[2]) + ((0x00FF & acc[3]) << 8);
		AccZ = (0x00FF & acc[4]) + ((0x00FF & acc[5]) << 8);

		GyroX = (0x00FF & gyro[0]) + ((0x00FF & gyro[1]) << 8);
		GyroY = (0x00FF & gyro[2]) + ((0x00FF & gyro[3]) << 8);
		GyroZ = (0x00FF & gyro[4]) + ((0x00FF & gyro[5]) << 8);
		
		Temp = (0x00FF & temp[0]) + ((0x00FF & temp[1]) << 8);
		
		printf("\r\n%s, %d: [DEBUG] AccX : %d. GyroX : %d. ", __FUNCTION__, __LINE__, AccX, GyroX);
		printf("\r\n%s, %d: [DEBUG] AccY : %d. GyroY : %d. ", __FUNCTION__, __LINE__, AccY, GyroY);
		printf("\r\n%s, %d: [DEBUG] AccZ : %d. GyroZ : %d. ", __FUNCTION__, __LINE__, AccZ, GyroZ);
		printf("\r\n%s, %d: [DEBUG] Temp : %d. ", __FUNCTION__, __LINE__,Temp);

		vTaskDelay(500);
	}
}

void KeyValue_set_task(void * pvParameters)
{
	while(1)
	{
			if(earphone_volume != earphone_volume_reg)
			{	
					earphone_volume_reg = earphone_volume;
					sabre9018_volume_set(earphone_volume_reg);
					printf("\r\n earphone_volume value = %d", earphone_volume_reg);
			}
			if(oled_bright_reg != oled_bright*10)
			{	
					oled_bright_reg = oled_bright*10;
					set_bright(OLED_0, oled_bright_reg);
					set_bright(OLED_1, oled_bright_reg);
					printf("\r\n oled_bright value = %d", oled_bright_reg);
			}
			vTaskDelay(200);
	}
}

void Log_print_task(void * pvParameters)
{	
	unsigned char value = 0;
	while(1)
	{
			value = Key_GPIO_Read(0);
			if(value == 0)
			{
				earphone_volume++;
				if(earphone_volume > 100)
					earphone_volume = 100;
			}
			value = Key_GPIO_Read(1);
			if(value == 0)
			{
				earphone_volume--;
				if(earphone_volume < 0)
					earphone_volume = 0;
			}
			value = Key_GPIO_Read(2);
			if(value == 0)
			{
				oled_bright--;
				if(oled_bright < 0)
					oled_bright = 0;
			}		
			value = Key_GPIO_Read(3);
			if(value == 0)
			{
				oled_bright++;
				if(oled_bright > 100)
					oled_bright = 102;
			}
			value = Key_GPIO_Read(4);
			if(value == 0)
			{
				vTaskDelay(2);
				value = Key_GPIO_Read(4);
				if(value == 0)
				{
					GPIO_2d3d_SW_set();	
				}	
			}
			vTaskDelay(100);
	}
}


void system_init(void)
{
    gd_eval_com_init(EVAL_COM2);
		/* print out the clock frequency of system, AHB, APB1 and APB2 */
    printf("\r\nCK_SYS is %d", rcu_clock_freq_get(CK_SYS));
    printf("\r\nCK_AHB is %d", rcu_clock_freq_get(CK_AHB));
    printf("\r\nCK_APB1 is %d", rcu_clock_freq_get(CK_APB1));
    printf("\r\nCK_APB2 is %d", rcu_clock_freq_get(CK_APB2));
		GPIO_INIT();
    I2C_Init();
//	
    tca9548_i2c_init();
		tca6408_i2c_init();
    pannel_init();  
    tca9548_i2c_set(TCA9548_ALL_DISABLE);
    pca9544_i2c_init();
		sabre9018_init();
		icm42688_init();
		Key_Init();
}

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
		system_init();
		xBinarySemaphore = xSemaphoreCreateBinary();
		
		if(xBinarySemaphore != NULL)
		{
				xTaskCreate(KeyValue_set_task, "KeyValue_task", configMINIMAL_STACK_SIZE, NULL, KeyValue_PRIO,(TaskHandle_t *)KeyValueTask_Handle);
				xTaskCreate(Log_print_task, "LogPrint_task", configMINIMAL_STACK_SIZE, NULL, LogPrint_PRIO,(TaskHandle_t *)LogPrintTask_Handle);
				xTaskCreate(USART_cmd_task, "LogPrint_task", configMINIMAL_STACK_SIZE, NULL, UsartCmd_PRIO,(TaskHandle_t *)USARTCMDTask_Handle);
				xTaskCreate(icm42688_data_task, "icm42688_task", configMINIMAL_STACK_SIZE, NULL, icm42688_PRIO,(TaskHandle_t *)icm42688Task_Handle);
			
				vTaskStartScheduler();
		}
		else
		{
			
		}
    while(1)
    {

    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM2, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM2, USART_FLAG_TBE));

    return ch;
}
///重定向c库函数scanf到串口重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (usart_flag_get(EVAL_COM2, USART_FLAG_RBNE) == RESET);

		return (int)usart_data_receive(EVAL_COM2);
}

