#include "gd32f30x.h"
#include "systick.h"
#include "dev_iic.h"
#include "TCA9548.h"


//#define AW_ENP_1()  gpio_bit_set(DEV_ENP_GPIO_PORT,DEV_ENP_GPIO_PIN)	
//#define AW_ENP_0()  gpio_bit_reset(DEV_ENP_GPIO_PORT,DEV_ENP_GPIO_PIN)	

//#define AW_ENN_1()  gpio_bit_set(DEV_ENN_GPIO_PORT,DEV_ENN_GPIO_PIN)	
//#define AW_ENN_0()  gpio_bit_reset(DEV_ENN_GPIO_PORT,DEV_ENN_GPIO_PIN)	

#define TCA9548_IIC_ADDR  (0x70<<1)
#define TCA9548_IIC_BUS 0

int tca9548_i2c_set(enum Tca9548Channel channel)
{
		unsigned char buf[1],get_buf[1];
		int ret;
		switch (channel)
		{
			case TCA9548_CHANNEL_0: buf[0] = TCA9548_CHANNEL_0_ENABLE; break;
			case TCA9548_CHANNEL_1: buf[0] = TCA9548_CHANNEL_1_ENABLE; break;
			case TCA9548_CHANNEL_2: buf[0] = TCA9548_CHANNEL_2_ENABLE; break;
			case TCA9548_CHANNEL_3: buf[0] = TCA9548_CHANNEL_3_ENABLE; break;
			case TCA9548_CHANNEL_4: buf[0] = TCA9548_CHANNEL_4_ENABLE; break;
			case TCA9548_CHANNEL_5: buf[0] = TCA9548_CHANNEL_5_ENABLE; break;
			case TCA9548_CHANNEL_6: buf[0] = TCA9548_CHANNEL_6_ENABLE; break;
			case TCA9548_CHANNEL_7: buf[0] = TCA9548_CHANNEL_7_ENABLE; break;
			case TCA9548_ALL_DISABLE: buf[0] = TCA9548_ALL_CHANNEL_DISABLE; break;
			default : 		printf("\r\n [ERROR] Channel is 0~7");
		}
    ret = DEV_I2C_Read(TCA9548_IIC_BUS, (unsigned char)TCA9548_IIC_ADDR ,buf[0] , 1, get_buf, 1);
		if(ret != 0)
		{
			printf("\r\n %s, %d: [ERROR] Write TCA9548 Failed ret = %d", __FUNCTION__, __LINE__, ret);
			return -1;
		}
    printf("\r\n%s, %d: [DEBUG] get Read TCA9548 ret = %d,get buf = 0x%x", __FUNCTION__, __LINE__ , ret, get_buf[0]);
		return ret;
}
int tca9548_i2c_init(void)
{
		unsigned char send_buf = 0x00;

    int32_t ret;
    ret = DEV_I2C_Read(TCA9548_IIC_BUS, (unsigned char)TCA9548_IIC_ADDR ,0x00 , 1,&send_buf, 1);
		if(ret != 0)
		{
			printf("\r\n %s, %d: [ERROR] Write TCA9548 Failed ret = %d", __FUNCTION__, __LINE__, ret);
			return -1;
		}
	printf("\r\n %s, %d: [DEBUG] get Write TCA9548 ret = %d,write buf = 0x%x", __FUNCTION__, __LINE__, ret, send_buf);
}













