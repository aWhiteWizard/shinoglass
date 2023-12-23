#include "oled.h"

int oled_init(void)
{
		unsigned char buf[1];
		tca9548_i2c_set(OLED_0_CHANNEL);
		DEV_I2C_Read(OLED_IIC_BUS, (unsigned char)OLED_IIC_ADDR, 0x00, 1, buf, 1);

		tca9548_i2c_set(OLED_1_CHANNEL);
		DEV_I2C_Read(OLED_IIC_BUS, (unsigned char)OLED_IIC_ADDR, 0x00, 1, buf, 1);
		return 0;
}

/*
*	@brife oled Write
*	@param oled_num select oled num, only 0 and 1
* @param reg_addr Data of reg
* @param send_data Data of reg
*/
int oled_write(enum OLED_NUM oled_num, unsigned char reg_addr, unsigned char send_data)
{
		int ret;
		switch (oled_num)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL); break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}
		ret = DEV_I2C_Write(OLED_IIC_BUS, (unsigned char)OLED_IIC_ADDR, reg_addr, 1, &send_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] Write Oled %d Error ,ret = %d,write = 0x%x", ret, oled_num, send_data);
			return -1;
		}
		return 0;
}

/*
*	@brife oled Read
*	@param oled_num select oled num, only 0 and 1
* @param reg_addr Data of reg
* @param send_data Data of reg
*/
int oled_read(enum OLED_NUM oled_num, unsigned char reg_addr, unsigned char *read_data)
{
		int ret;
		switch (oled_num)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL);	break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}
		ret = DEV_I2C_Read(OLED_IIC_BUS, (unsigned char)OLED_IIC_ADDR, reg_addr, 1, read_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] Read Oled %d Error ,ret = %d", ret, oled_num);
			return -1;
		}
		return 0;
}

