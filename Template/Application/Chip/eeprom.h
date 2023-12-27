#ifndef __EEPROM_H
#define __EEPROM_H

#include "dev_conf.h"
#include "TCA9548.h"
#include "dev_iic.h"
/*
	oled0 at 1 channel of 9548
	oled1 at 2 channel of 9548
*/
#define EEPROM_IIC_ADDR  (0xA0<<1)

#define EEPROM_CHANNEL TCA9548_CHANNEL_3

#define EEPROM_IIC_BUS 0

int eeprom_init();
int eeprom_write(unsigned char reg_addr, unsigned char send_data);
int eeprom_read(unsigned char reg_addr, int len, unsigned char *read_data);

#endif

