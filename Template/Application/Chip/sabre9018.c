#include "sabre9018.h"
/*
*	@brife sabre9018 init
*/

#define Delay_ms(time) vTaskDelay(time)
int sabre9018_print(unsigned char reg)
{
			unsigned char sabre_status;
		DEV_I2C_Read(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, reg, 1,&sabre_status, 1);
	    printf("\r\n%s, %d: [DEBUG] 0x%x : 0x%x", __FUNCTION__, __LINE__, reg, sabre_status);
}

int sabre9018_init(void)
{

		
		pca9544_i2c_set(SABRE9018_CHANNEL);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SYSTEMSET, 1,				   																	&sabre9018_init_reg[0],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_INPUTCONFIG, 1, 		   																	&sabre9018_init_reg[1],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SOFTVOLUMECTRL_1, 1,   																	&sabre9018_init_reg[2],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SOFTVOLUMECTRL_2, 1,   																	&sabre9018_init_reg[3],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SOFTVOLUMECTRL_3, 1,   																	&sabre9018_init_reg[4],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_GENERALSETTING, 1, 	   																	&sabre9018_init_reg[5],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_GPIOCONFIG, 1, 			   																	&sabre9018_init_reg[6],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_MASTERMODECTRL, 1, 	   																	&sabre9018_init_reg[7],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_CHANNELMAPPING, 1,     																	&sabre9018_init_reg[8],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_DPLL_ASRC_SETTING, 1, 																	&sabre9018_init_reg[9],  1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_THDCOMPENSATION, 1,  																		&sabre9018_init_reg[10], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SOFTSTARTSETTING, 1, 																		&sabre9018_init_reg[11], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_VOLUME_1, 1, 				 																		&sabre9018_init_reg[12], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_VOLUME_2, 1, 			   																		&sabre9018_init_reg[13], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_MASTERTRIM_0, 1,     																		&sabre9018_init_reg[14], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_MASTERTRIM_1, 1,     																		&sabre9018_init_reg[15], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_MASTERTRIM_2, 1,     																		&sabre9018_init_reg[16], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_MASTERTRIM_3, 1,     																		&sabre9018_init_reg[17], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_GPIOINPUTSELECTION_OSFBYPASS, 1, 												&sabre9018_init_reg[18], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HARMONICCOMPENSATIONCOFFIENTS_2ND_0, 1, 								&sabre9018_init_reg[19], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HARMONICCOMPENSATIONCOFFIENTS_2ND_1, 1, 								&sabre9018_init_reg[20], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HARMONICCOMPENSATIONCOFFIENTS_3RD_0, 1, 								&sabre9018_init_reg[21], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HARMONICCOMPENSATIONCOFFIENTS_3RD_1, 1, 								&sabre9018_init_reg[22], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_PROGRAMMABLE_FILTER_ADDRESS, 1, 												&sabre9018_init_reg[23], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_PROGRAMMABLE_FILTER_COEFFICIENT_0, 1, 									&sabre9018_init_reg[24], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_PROGRAMMABLE_FILTER_COEFFICIENT_1, 1, 									&sabre9018_init_reg[25], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_PROGRAMMABLE_FILTER_COEFFICIENT_2, 1, 									&sabre9018_init_reg[26], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_PROGRAMMABLE_FILTER_CTRL, 1, 														&sabre9018_init_reg[27], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_RIGHTCHANNEL_2ND_HARMONICCOMPENSATIONCOEFFICIENTS_0, 1, &sabre9018_init_reg[28], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_RIGHTCHANNEL_2ND_HARMONICCOMPENSATIONCOEFFICIENTS_1, 1, &sabre9018_init_reg[29], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_RIGHTCHANNEL_3RD_HARMONICCOMPENSATIONCOEFFICIENTS_0, 1, &sabre9018_init_reg[30], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_RIGHTCHANNEL_3RD_HARMONICCOMPENSATIONCOEFFICIENTS_1, 1, &sabre9018_init_reg[31], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SEPARATETHDCOMPENSATION, 1, 														&sabre9018_init_reg[32], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_FSYNCCTRL_0, 1, 																				&sabre9018_init_reg[33], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_FSYNCCTRL_1, 1, 																				&sabre9018_init_reg[34], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HEADPHONEAMPLIFERBIASCTRL, 1, 													&sabre9018_init_reg[35], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_HEADPHONEAMPLIFERCTRL, 1, 															&sabre9018_init_reg[36], 1);
		DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_SLIMBUSCTRL, 1, 																				&sabre9018_init_reg[37], 1);
		delay_1ms(5);
		sabre9018_print(SABRE9018_REG_SYSTEMSET);
		sabre9018_print(SABRE9018_REG_INPUTCONFIG);
		sabre9018_print(SABRE9018_REG_SOFTVOLUMECTRL_1);
		sabre9018_print(SABRE9018_REG_SOFTVOLUMECTRL_2);
		sabre9018_print(SABRE9018_REG_SOFTVOLUMECTRL_3);
		sabre9018_print(SABRE9018_REG_MASTERMODECTRL);
		sabre9018_print(SABRE9018_REG_CHANNELMAPPING);
		sabre9018_print(SABRE9018_REG_VOLUME_1);
		sabre9018_print(SABRE9018_REG_VOLUME_2);
		sabre9018_print(SABRE9018_REG_CHIPSTATUS);	
		sabre9018_print(SABRE9018_REG_READONLY);	
		sabre9018_print(SABRE9018_REG_RIGHTCHANNEL_2ND_HARMONICCOMPENSATIONCOEFFICIENTS_0);
		sabre9018_print(SABRE9018_REG_RIGHTCHANNEL_2ND_HARMONICCOMPENSATIONCOEFFICIENTS_1);
		sabre9018_print(SABRE9018_REG_RIGHTCHANNEL_3RD_HARMONICCOMPENSATIONCOEFFICIENTS_0);
		sabre9018_print(SABRE9018_REG_RIGHTCHANNEL_3RD_HARMONICCOMPENSATIONCOEFFICIENTS_1);
		sabre9018_print(SABRE9018_REG_SEPARATETHDCOMPENSATION);
		
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
    printf("\r\n%s, %d: [DEBUG] SABRE9018 Set done", __FUNCTION__, __LINE__);
		return 0;
}

/*
*	@brife sabre9018 Write
* @param reg_addr Data of reg
* @param send_data write to sabre9018
*/
int sabre9018_volume_set(unsigned char send_data)
{
		int ret;
		pca9544_i2c_set(SABRE9018_CHANNEL);
		ret = DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_VOLUME_1, 1, &send_data, 1);
		ret = DEV_I2C_Write(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, SABRE9018_REG_VOLUME_2, 1, &send_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] sabre9018 Write Error ,ret = %d,write = 0x%x", ret, send_data);
			return -1;
		}
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
		return 0;
}

/*
*	@brife sabre9018 Read
* @param reg_addr Data of reg
* @param read_data Read Data
* @param len length of Read Data
*/
int sabre9018_read(unsigned char reg_addr, unsigned char *read_data, int len)
{
		int ret;
		pca9544_i2c_set(SABRE9018_CHANNEL);

		ret = DEV_I2C_Read(SABRE9018_IIC_BUS, (unsigned char)SABRE9018_IIC_ADDR, reg_addr, 1, read_data, 1);
		if(ret != 0)
		{
			printf("\r\n [ERROR] sabre9018 Read Error ,ret = %d", ret);
			return -1;
		}
		return 0;
}

