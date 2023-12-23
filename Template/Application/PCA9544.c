#include "gd32f30x.h"
#include "systick.h"
#include "dev_iic.h"
#include "PCA9544.h"

#define PCA9544_CHANNEL_0_ENABLE 0x04
#define PCA9544_CHANNEL_1_ENABLE 0x05
#define PCA9544_CHANNEL_2_ENABLE 0x06
#define PCA9544_CHANNEL_3_ENABLE 0x07
#define PCA9544_CHANNEL_ALL_DISABLE 0x00

//#define AW_ENP_1()  gpio_bit_set(DEV_ENP_GPIO_PORT,DEV_ENP_GPIO_PIN)	
//#define AW_ENP_0()  gpio_bit_reset(DEV_ENP_GPIO_PORT,DEV_ENP_GPIO_PIN)	

//#define AW_ENN_1()  gpio_bit_set(DEV_ENN_GPIO_PORT,DEV_ENN_GPIO_PIN)	
//#define AW_ENN_0()  gpio_bit_reset(DEV_ENN_GPIO_PORT,DEV_ENN_GPIO_PIN)	

#define PCA9544_IIC_ADDR  (0x70<<1)
#define PCA9544_IIC_BUS 0

int pca9544_i2c_set(enum PCA9544Channel channel)
{
		unsigned char buf[1],get_buf[1];
		int ret;
		switch (channel)
		{
			case PCA9544_CHANNEL_0: buf[0] = PCA9544_CHANNEL_0_ENABLE; break;
			case PCA9544_CHANNEL_1: buf[0] = PCA9544_CHANNEL_1_ENABLE; break;
			case PCA9544_CHANNEL_2: buf[0] = PCA9544_CHANNEL_2_ENABLE; break;
			case PCA9544_CHANNEL_3: buf[0] = PCA9544_CHANNEL_3_ENABLE; break;
			case PCA9544_CHANNEL_DISABLED: buf[0] = PCA9544_CHANNEL_ALL_DISABLE; break;
			case PCA9544_test: buf[0] = 0xFF; break;
			default : 		printf("\r\n [ERROR] Channel is 0~3");
		}
    ret = DEV_I2C_Read(PCA9544_IIC_BUS, (unsigned char)PCA9544_IIC_ADDR ,buf[0] , 1, get_buf, 1);
		if(ret != 0)
		{
			printf("\r\n %s, %d: [ERROR] Write PCA9544 Failed ret = %d", __FUNCTION__, __LINE__, ret);
			return -1;
		}
    printf("\r\n%s, %d: [DEBUG] get Read PCA9544 ret = %d,get buf = 0x%x", __FUNCTION__, __LINE__ , ret, get_buf[0]);
		return ret;
}
int pca9544_i2c_init(void)
{
		unsigned char send_buf = 0x00;

    int32_t ret;
    ret = DEV_I2C_Read(PCA9544_IIC_BUS, (unsigned char)PCA9544_IIC_ADDR ,PCA9544_CHANNEL_ALL_DISABLE , 1,&send_buf, 1);
		if(ret != 0)
		{
			printf("\r\n %s, %d: [ERROR] Write TCA9548 Failed ret = %d", __FUNCTION__, __LINE__, ret);
			return -1;
		}
	printf("\r\n %s, %d: [DEBUG] get Write TCA9548 ret = %d,write buf = 0x%x", __FUNCTION__, __LINE__, ret, send_buf);
}













