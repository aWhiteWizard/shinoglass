#include "lt7911.h"
/*
*	@brife lt7911 init
*/
int lt7911_init()
{
		unsigned char buf[1];
		tca9548_i2c_set(LT7911_CHANNEL);
		DEV_I2C_Read(LT7911_IIC_BUS, (unsigned char)LT7911_IIC_ADDR, 0x00, 1, buf, 1);

		return 0;
}

/*
*	@brife lt7911 Write
* @param reg_addr Data of reg
* @param send_data write to lt7911
*/
int lt7911_write(unsigned char reg_addr, unsigned char send_data)
{
		int ret;
		tca9548_i2c_set(LT7911_CHANNEL);
		ret = DEV_I2C_Write(LT7911_IIC_BUS, (unsigned char)LT7911_IIC_ADDR, reg_addr, 1, &send_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] LT7911 Write Error ,ret = %d,write = 0x%x", ret, send_data);
			return -1;
		}
		return 0;
}

/*
*	@brife lt7911 Read
* @param reg_addr Data of reg
* @param read_data Read Data
* @param len length of Read Data
*/
int lt7911_read(unsigned char reg_addr, unsigned char *read_data, int len)
{
		int ret;
		tca9548_i2c_set(LT7911_CHANNEL);

		ret = DEV_I2C_Read(LT7911_IIC_BUS, (unsigned char)LT7911_IIC_ADDR, reg_addr, 1, read_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] LT7911 Read Error ,ret = %d", ret);
			return -1;
		}
		return 0;
}

