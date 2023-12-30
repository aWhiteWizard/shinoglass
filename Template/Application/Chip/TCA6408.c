#include "tca6408.h"
#include "dev_conf.h"

/*
	6408 at 4 channel of 9548
*/
/*
	@brife tca6408 init
*/
int tca6408_i2c_init(void)
{
		int ret;
		unsigned char set_param[2]= {0x00, 0xff};
		unsigned char buf[1];
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
			printf("\r\n%s, %d: [ERROR] init TCA6408 ret = %d,write buf = 0x%x", __FUNCTION__, __LINE__, ret, buf[0]);
		DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR, TCA6408_POLARITY, 1, &set_param[0], 1);
		ret = DEV_I2C_Read(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,TCA6408_POLARITY , 1,buf, 1);
		if(buf[0] != 0x00)
		{
				printf("\r\n%s, %d [ERROR] init TCA6408 POLARITY is not 0x00 please check! get polarity is 0x%x.", __FUNCTION__, __LINE__ ,buf[0]);
		}
		printf("\r\n %s, %d [DEBUG] get Read TCA6408 ret = %d,get buf = 0x%x", __FUNCTION__, __LINE__, ret, buf[0]);
		DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR, TCA6408_CONFIG, 1, &set_param[1], 1);
		ret = DEV_I2C_Read(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,TCA6408_CONFIG , 1,buf, 1);
		if(buf[0] != 0xFF)
		{
				printf("\r\n%s, %d [ERROR] init TCA6408 CONFIG is not 0xFF please check! get config is 0x%x.", __FUNCTION__, __LINE__ ,buf[0]);
		}
		printf("\r\n%s, %d: [DEBUG] get Read TCA6408 ret = %d,get buf = 0x%x", __FUNCTION__, __LINE__ , ret, buf[0]);
		return 0;
}
/*
*	@brife tca6408 Write
*	@param send_data Data to 6408
* @param reg_addr Data of reg
*/
int tca6408_write(unsigned char send_data, unsigned char reg_addr)
{
		int ret;
		unsigned char set_param[1]= {send_data};
		unsigned char buf[1];
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
				printf("\r\n%s, %d [ERROR] init TCA6408 ret = %d,write buf = 0x%x", __FUNCTION__, __LINE__, ret, buf[0]);

		DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR, reg_addr, 1, set_param, 1);
		ret = DEV_I2C_Read(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,reg_addr , 1,buf, 1);
		if(buf[0] != send_data)
		{
				printf("\r\n%s, %d [ERROR] Write TCA6408 data is Failed! get callback is 0x%x.", __FUNCTION__, __LINE__ ,buf[0]);
				return -1;
		}
//		printf("\r\n%s %d: [DEBUG] get Read TCA6408 ret = %d,get buf = 0x%x" , __FUNCTION__ , __LINE__, ret, buf[0]);
		return 0;
}

/*
*	@brife tca6408 Read
*	@param Read_data Data to 6408
* @param reg_addr Data of reg
*/
int tca6408_read(unsigned char *Read_data, unsigned char reg_addr)
{
		int ret;
		unsigned char buf[1];
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
				printf("\r\n [ERROR] init TCA6408 ret = %d,write buf = 0x%x", ret, buf[0]);
		ret = DEV_I2C_Read(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,reg_addr , 1,Read_data, 1);
		return 0;
}

/*
*	@brife pannel reset gpio ctrl
*	@param gpio_status set pannel ctrl gpio
*/
int pannel_reset_gpio_ctrl(int gpio_status)
{
		int ret;
		unsigned char buf[1] = {LT7911_GPIO_16 & (gpio_status << 6)};
	
		if(gpio_status >= 2)
		{
				printf("\r\n [ERROR] gpio is Only 0 to off , 1 to on");
				return -1;
		}
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
				printf("\r\n [ERROR] set TCA6408 channel Error ret = %d", ret);
		ret = DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,LT7911_GPIO_16 , 1, buf, 1);
		if(ret != 0)
				printf("\r\n [ERROR] Write TCA6408 GPIO 16 Error ret = %d", ret);
		return 0;
}

/*
*	@brife 3d switch gpio ctrl
*	@param gpio_status set pannel ctrl gpio
*/
int sw_3d_gpio_ctrl(int gpio_status)
{
		int ret;
		unsigned char buf[1] = {LT7911_GPIO_14 & (gpio_status << 5)};
		if(gpio_status >= 2)
		{
				printf("\r\n [ERROR] gpio is Only 0 to off , 1 to on");
				return -1;
		}
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
				printf("\r\n [ERROR] set TCA6408 channel Error ret = %d", ret);
		ret = DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,TCA6408_OUTPUT , 1,buf, 1);
		if(ret != 0)
				printf("\r\n [ERROR] Write TCA6408 GPIO 14 Error ret = %d", ret);
		return 0;
}

/*
*	@brife lt7911 reset gpio ctrl
*	@param gpio_status set pannel ctrl gpio
*/
int lt7911_reset_gpio_ctrl(int gpio_status)
{
		int ret;
		unsigned char buf[1] = {LT7911_RST & (gpio_status << 4)};
		if(gpio_status >= 2)
		{
				printf("\r\n [ERROR] gpio is Only 0 to off , 1 to on");
				return -1;
		}
		ret = tca9548_i2c_set(TCA6408_CHANNEL);
		if(ret != 0)
				printf("\r\n [ERROR] set TCA6408 channel Error ret = %d", ret);
		ret = DEV_I2C_Write(TCA6408_IIC_BUS, (unsigned char)TCA6408_IIC_ADDR ,TCA6408_OUTPUT , 1,buf, 1);
		if(ret != 0)
				printf("\r\n [ERROR] Write TCA6408 LT7911 RST Error ret = %d", ret);
		return 0;
}


