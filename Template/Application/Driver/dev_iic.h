/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2022-01-05 15:33:26
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-12-17 10:57:54
 * @FilePath: \Keil_projectd:\BaiduSyncdisk\workspace\glass\GD32F30x_Firmware_Library_V2.1.5\Template\Application\dev_iic.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _IIC_H_
#define _IIC_H_


#include "gd32f30x.h"
#include "dev_conf.h"

#define MCU_AVDD_EN 0x01
#define MCU_AVEE_EN 0x02
#define MCU_LED0 0x04
#define MCU_LED1 0x08
#define DAC_CFG_RST_B 0x80

/*使用软件IIC，把SOFT_IIC宏设置为1，硬件IIC则设置为0
!!使用硬件IIC时非常容易出现错误，不推荐*/
#define SOFT_IIC      1

/*设定使用的电容屏IIC设备地址*/
#define DEV_IIC_ADDRESS            0xBA

#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))



//软件IIC使用的宏
#define TCA9548_RESET_1()  gpio_bit_set(TCA9548_RESET_BIT_PORT,TCA9548_RESET_BIT)		/* SCL = 0 */
#define TCA9548_RESET_0()  gpio_bit_reset(TCA9548_RESET_BIT_PORT,TCA9548_RESET_BIT)		/* SCL = 0 */

#define I2C_PRIMARY_SCL_1()  gpio_bit_set(DEV_PRIMARY_I2C_SCL_GPIO_PORT,DEV_PRIMARY_I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_PRIMARY_SCL_0()  gpio_bit_reset(DEV_PRIMARY_I2C_SCL_GPIO_PORT,DEV_PRIMARY_I2C_SCL_PIN)		/* SCL = 0 */

#define I2C_PRIMARY_SDA_1()  gpio_bit_set(DEV_PRIMARY_I2C_SDA_GPIO_PORT,DEV_PRIMARY_I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_PRIMARY_SDA_0()  gpio_bit_reset(DEV_PRIMARY_I2C_SDA_GPIO_PORT,DEV_PRIMARY_I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_SECONDARY_SCL_1()  gpio_bit_set(DEV_SECONDARY_I2C_SCL_GPIO_PORT,DEV_SECONDARY_I2C_SCL_PIN)		/* SCL = 1 */
#define I2C_SECONDARY_SCL_0()  gpio_bit_reset(DEV_SECONDARY_I2C_SCL_GPIO_PORT,DEV_SECONDARY_I2C_SCL_PIN)		/* SCL = 0 */

#define I2C_SECONDARY_SDA_1()  gpio_bit_set(DEV_SECONDARY_I2C_SDA_GPIO_PORT,DEV_SECONDARY_I2C_SDA_PIN)		/* SDA = 1 */
#define I2C_SECONDARY_SDA_0()  gpio_bit_reset(DEV_SECONDARY_I2C_SDA_GPIO_PORT,DEV_SECONDARY_I2C_SDA_PIN)		/* SDA = 0 */

#define I2C_PRIMARY_SDA_READ()  gpio_input_bit_get(DEV_PRIMARY_I2C_SDA_GPIO_PORT, DEV_PRIMARY_I2C_SDA_PIN)	/* 读SDA口线状态 */
#define I2C_SECONDARY_SDA_READ()  gpio_input_bit_get(DEV_SECONDARY_I2C_SDA_GPIO_PORT, DEV_SECONDARY_I2C_SDA_PIN)	/* 读SDA口线状态 */


void I2C_Init(void);
int32_t DEV_I2C_Read(unsigned char i2c_bus, unsigned char client_addr,uint16_t reg_addr,unsigned char reg_len,unsigned char *buf, int32_t len);
int32_t DEV_I2C_Write(unsigned char i2c_bus, unsigned char client_addr,uint16_t reg_addr,unsigned char reg_len,unsigned char *buf,int32_t len);
void CLK_PRIMARY_In(void);
void SDA_PRIMARY_In(void);
void CLK_SECONDARY_In(void);
void SDA_SECONDARY_In(void);
void I2C_PRIMARY_GPIO_IN(void);
void I2C_SECONDARY_GPIO_IN(void);
void GPIO_INIT(void);

int32_t TCA9548_I2C_Write(unsigned char client_addr,unsigned char *buf);

/* 表示读数据 */ 
#define I2C_M_RD		0x0001	
 /*
 * 存储I2C通讯的信息
 * @addr：  从设备的I2C设备地址	
 * @flags: 控制标志
 * @len：  读写数据的长度
 * @buf：  存储读写数据的指针
 **/
struct i2c_msg {
	unsigned char addr;		/*从设备的I2C设备地址 */
	uint16_t flags;	/*控制标志*/
	uint16_t regaddr;   //寄存器数据
	unsigned char reg_len;     //寄存器地址字节个数
	uint16_t len;		/*读写数据的长度			*/
	unsigned char *buf;		/*存储读写数据的指针	*/
};



#endif
