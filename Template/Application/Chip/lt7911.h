#ifndef __LT7911_H
#define __LT7911_H


#include "dev_conf.h"
#include "TCA9548.h"
#include "dev_iic.h"
/*
	lt7911 at 0 channel of 9548
*/
//#define LT7911_IIC_ADDR  (0x86<<1)
#define LT7911_IIC_ADDR  (0x90<<0)

#define LT7911_CHANNEL TCA9548_CHANNEL_0

#define LT7911_IIC_BUS 0

//pannel reset
//#define OLED_RSTN_RCU          RCU_GPIOB
//#define OLED_RSTN_PIN          GPIO_PIN_2
//#define OLED_RSTN_PORT         GPIOB



int lt7911_init();
int lt7911_write(unsigned char reg_addr, unsigned char send_data);
int lt7911_read(unsigned char reg_addr, unsigned char *read_data, int len);

#endif

