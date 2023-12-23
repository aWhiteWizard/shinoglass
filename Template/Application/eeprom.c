#include "eeprom.h"

/*
*	@brife eeprom init
*/
int eeprom_init()
{
		unsigned char buf[1];
		tca9548_i2c_set(EEPROM_CHANNEL);
		DEV_I2C_Read(EEPROM_IIC_BUS, (unsigned char)EEPROM_IIC_ADDR, 0x00, 1, buf, 1);
		return 0;
}

/*
*	@brife eeprom Write
* @param reg_addr Data of reg
* @param send_data Data to EEPROM
*/
int eeprom_write(unsigned char reg_addr, unsigned char send_data)
{
		int ret;
		tca9548_i2c_set(EEPROM_CHANNEL);
		ret = DEV_I2C_Write(EEPROM_IIC_BUS, (unsigned char)EEPROM_IIC_ADDR, reg_addr, 1, &send_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] Write EEPROM Error ,ret = %d,write = 0x%x", ret, send_data);
			return -1;
		}
		return 0;
}

/*
*	@brife EEPROM Read
* @param reg_addr READ Data of reg
* @param len READ length of data
* @param read_data READ Data
*/
int eeprom_read(unsigned char reg_addr, int len, unsigned char *read_data)
{
		int ret;
		tca9548_i2c_set(EEPROM_CHANNEL);

		ret = DEV_I2C_Read(EEPROM_IIC_BUS, (unsigned char)EEPROM_IIC_ADDR, reg_addr, 1, read_data, len);
		if(ret != 0)
		{
			printf("\r\n [ERROR] Read EEPROM Error ,ret = %d", ret);
			return -1;
		}
		return 0;
}

