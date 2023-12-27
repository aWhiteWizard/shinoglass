/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2022-01-05 15:33:26
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-12-17 10:57:54
 * @FilePath: \Keil_projectd:\BaiduSyncdisk\workspace\glass\GD32F30x_Firmware_Library_V2.1.5\Template\Application\dev_iic.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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

/*ʹ�����IIC����SOFT_IIC������Ϊ1��Ӳ��IIC������Ϊ0
!!ʹ��Ӳ��IICʱ�ǳ����׳��ִ��󣬲��Ƽ�*/
#define SOFT_IIC      1

/*�趨ʹ�õĵ�����IIC�豸��ַ*/
#define DEV_IIC_ADDRESS            0xBA

#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))



//���IICʹ�õĺ�
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

#define I2C_PRIMARY_SDA_READ()  gpio_input_bit_get(DEV_PRIMARY_I2C_SDA_GPIO_PORT, DEV_PRIMARY_I2C_SDA_PIN)	/* ��SDA����״̬ */
#define I2C_SECONDARY_SDA_READ()  gpio_input_bit_get(DEV_SECONDARY_I2C_SDA_GPIO_PORT, DEV_SECONDARY_I2C_SDA_PIN)	/* ��SDA����״̬ */


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

/* ��ʾ������ */ 
#define I2C_M_RD		0x0001	
 /*
 * �洢I2CͨѶ����Ϣ
 * @addr��  ���豸��I2C�豸��ַ	
 * @flags: ���Ʊ�־
 * @len��  ��д���ݵĳ���
 * @buf��  �洢��д���ݵ�ָ��
 **/
struct i2c_msg {
	unsigned char addr;		/*���豸��I2C�豸��ַ */
	uint16_t flags;	/*���Ʊ�־*/
	uint16_t regaddr;   //�Ĵ�������
	unsigned char reg_len;     //�Ĵ�����ַ�ֽڸ���
	uint16_t len;		/*��д���ݵĳ���			*/
	unsigned char *buf;		/*�洢��д���ݵ�ָ��	*/
};



#endif
