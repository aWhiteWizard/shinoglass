#ifndef __OLED_H
#define __OLED_H


#include "dev_conf.h"
#include "TCA9548.h"
#include "dev_iic.h"
/*
	oled0 at 1 channel of 9548
	oled1 at 2 channel of 9548
*/
#define OLED_IIC_ADDR  (0x4C<<1)

#define OLED_0_CHANNEL TCA9548_CHANNEL_1
#define OLED_1_CHANNEL TCA9548_CHANNEL_2

#define OLED_IIC_BUS 0

typedef enum OLED_NUM
{
	OLED_0,
	OLED_1
}OLED_NUM;


int oled_init(void);
int oled_write(enum OLED_NUM oled_num, unsigned char reg_addr, unsigned char send_data);
int oled_read(enum OLED_NUM oled_num, unsigned char reg_addr, unsigned char *read_data);

#endif

