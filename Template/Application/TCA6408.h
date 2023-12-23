#ifndef __TCA6408_H
#define __TCA6408_H

#include "TCA9548.h"
#include "dev_iic.h"


#define TCA6408_IIC_ADDR  (0x20<<1)

#define TCA6408_IIC_BUS 0

#define TCA6408_CHANNEL TCA9548_CHANNEL_4

#define TCA6408_MCU_AVDD_EN 0x01
#define TCA6408_MCU_AVEE_EN 0x02
#define TCA6408_MCU_LED0 0x04
#define TCA6408_MCU_LED1 0x08
#define TCA6408_LV7911_RST_N 0x10
#define TCA6408_LV7911_GPIO_14 0x20
#define TCA6408_LV7911_GPIO_16 0x40
#define TCA6408_DAC_CFG_RST_B 0x80

#define TCA6408_INPUT 0x00
#define TCA6408_OUTPUT 0x01
#define TCA6408_POLARITY 0x02
#define TCA6408_CONFIG 0x03

int tca6408_i2c_init(void);
int tca6408_write(unsigned char send_data, unsigned char reg_addr);
int tca6408_read(unsigned char *Read_data, unsigned char reg_addr);
int pannel_reset_gpio_ctrl(int gpio_status);
int sw_3d_gpio_ctrl(int gpio_status);
int lt7911_reset_gpio_ctrl(int gpio_status);

#endif

