#include "icm42688.h"

#define Delay_ms(time) vTaskDelay(time)
int icm42688_print(unsigned char reg)
{
			unsigned char icm42688_status;
			DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, reg, 1,&icm42688_status, 1);
	    printf("\r\n%s, %d: [DEBUG] 0x%x : 0x%x", __FUNCTION__, __LINE__, reg, icm42688_status);
}

void icm42688_print_test(void)
{
		pca9544_i2c_set(ICM42688_CHANNEL);
		
		icm42688_print(ICM42688_DEVICE_CONFIG);
		icm42688_print(ICM42688_DRIVE_CONFIG);
		icm42688_print(ICM42688_FIFO_DATA);
		icm42688_print(ICM42688_INT_CONFIG);
		icm42688_print(ICM42688_FIFO_CONFIG);
		icm42688_print(ICM42688_FIFO_COUNTH);
		icm42688_print(ICM42688_FIFO_COUNTL);
		icm42688_print(ICM42688_INT_STATUS);

		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
}

void icm42688_init(void)
{
		unsigned char whoami, bank_select, i2c_mode_set = 0x83;
		rcu_periph_clock_enable(IMU_INT1_GPIO_RCU);
		gpio_init(IMU_INT1_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, IMU_INT1_PIN); 
		gpio_bit_reset(IMU_INT1_GPIO_PORT, IMU_INT1_PIN);
	
		rcu_periph_clock_enable(IMU_INT2_GPIO_RCU);
		gpio_init(IMU_INT2_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, IMU_INT2_PIN); 
		gpio_bit_reset(IMU_INT2_GPIO_PORT, IMU_INT2_PIN);
		
		pca9544_i2c_set(ICM42688_CHANNEL);
		bank_select = 0x00;
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_REG_BANK_SEL, 1,	&bank_select,  1); //设置为BANK0
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_DEVICE_CONFIG, 1,	&icm42688_init_cmd[0],  1); 
		icm42688_print(ICM42688_WHO_AM_I);

//	  bank_select = 0x01;
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_REG_BANK_SEL, 1,	&bank_select,  1); //设置为BANK1
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INTF_CONFIG4, 1,	&i2c_mode_set,  1); 
	
//		bank_select = 0x00;
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_REG_BANK_SEL, 1,	&bank_select,  1); //设置为BANK0
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_DRIVE_CONFIG, 1,	&icm42688_init_cmd[1],  1);
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_CONFIG, 1,	&icm42688_init_cmd[2],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_CONFIG, 1,	&icm42688_init_cmd[3],  1);
	
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TEMP_DATA1, 1,	&icm42688_init_cmd[4],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TEMP_DATA0, 1,	&icm42688_init_cmd[5],  1);
//	
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X1, 1,	&icm42688_init_cmd[6],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X0, 1,	&icm42688_init_cmd[7],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y1, 1,	&icm42688_init_cmd[8],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y0, 1,	&icm42688_init_cmd[9],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z1, 1,	&icm42688_init_cmd[10],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z0, 1,	&icm42688_init_cmd[11],  1);

//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_X1, 1,	&icm42688_init_cmd[12],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_X0, 1,	&icm42688_init_cmd[13],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_Y1, 1,	&icm42688_init_cmd[14],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_Y0, 1,	&icm42688_init_cmd[15],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_Z1, 1,	&icm42688_init_cmd[16],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_DATA_Z0, 1,	&icm42688_init_cmd[17],  1);
		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TMST_FSYNCH, 1,	&icm42688_init_cmd[18],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TMST_FSYNCL, 1,	&icm42688_init_cmd[19],  1);
//		
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_STATUS, 1,	&icm42688_init_cmd[20],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_COUNTH, 1,	&icm42688_init_cmd[21],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_COUNTL, 1,	&icm42688_init_cmd[22],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_DATA, 1,	&icm42688_init_cmd[23],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA0, 1,	&icm42688_init_cmd[24],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA1, 1,	&icm42688_init_cmd[25],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA2, 1,	&icm42688_init_cmd[26],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA3, 1,	&icm42688_init_cmd[27],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA4, 1,	&icm42688_init_cmd[28],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_DATA5, 1,	&icm42688_init_cmd[29],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_STATUS2, 1,	&icm42688_init_cmd[30],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_STATUS3, 1,	&icm42688_init_cmd[31],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_SIGNAL_PATH_RESET, 1,	&icm42688_init_cmd[32],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INTF_CONFIG0, 1,	&icm42688_init_cmd[33],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INTF_CONFIG1, 1,	&icm42688_init_cmd[34],  1);
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_PWR_MGMT0, 1,	&icm42688_init_cmd[35],  1);
		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_CONFIG0, 1,	&icm42688_init_cmd[36],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_CONFIG0, 1,	&icm42688_init_cmd[37],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_CONFIG1, 1,	&icm42688_init_cmd[38],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_GYRO_ACCEL_CONFIG0, 1,	&icm42688_init_cmd[39],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_CONFIG1, 1,	&icm42688_init_cmd[40],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TMST_CONFIG, 1,	&icm42688_init_cmd[41],  1);	
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_APEX_CONFIG0, 1,	&icm42688_init_cmd[42],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_SMD_CONFIG, 1,	&icm42688_init_cmd[43],  1);
		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_CONFIG1, 1,	&icm42688_init_cmd[44],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_CONFIG2, 1,	&icm42688_init_cmd[45],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_CONFIG3, 1,	&icm42688_init_cmd[46],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FSYNC_CONFIG, 1,	&icm42688_init_cmd[47],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_CONFIG0, 1,	&icm42688_init_cmd[48],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_CONFIG1, 1,	&icm42688_init_cmd[49],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_SOURCE0, 1,	&icm42688_init_cmd[50],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_SOURCE1, 1,	&icm42688_init_cmd[51],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_SOURCE3, 1,	&icm42688_init_cmd[52],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_INT_SOURCE4, 1,	&icm42688_init_cmd[53],  1);
//		
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_LOST_PKT0, 1,	&icm42688_init_cmd[54],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_FIFO_LOST_PKT1, 1,	&icm42688_init_cmd[55],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_SELF_TEST_CONFIG, 1,	&icm42688_init_cmd[56],  1);
//		DEV_I2C_Write(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_WHO_AM_I, 1,	&icm42688_init_cmd[57],  1);
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
}

unsigned char icm42688_get_acc(unsigned char *read_acc)
{
		pca9544_i2c_set(ICM42688_CHANNEL);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X1, 1,&read_acc[1], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X0, 1,&read_acc[0], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y1, 1,&read_acc[3], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y0, 1,&read_acc[2], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z1, 1,&read_acc[5], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z0, 1,&read_acc[4], 1);
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
//		    printf("\r\n%s, %d: [DEBUG] AccX : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_acc[0], read_acc[1]);
//				printf("\r\n%s, %d: [DEBUG] AccY : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_acc[2], read_acc[3]);
//				printf("\r\n%s, %d: [DEBUG] AccZ : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_acc[4], read_acc[5]);
		return 0;
}

unsigned char icm42688_get_gyro(unsigned char *read_gyro)
{
		pca9544_i2c_set(ICM42688_CHANNEL);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X1, 1,&read_gyro[1], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_X0, 1,&read_gyro[0], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y1, 1,&read_gyro[3], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Y0, 1,&read_gyro[2], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z1, 1,&read_gyro[5], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_ACCEL_DATA_Z0, 1,&read_gyro[4], 1);
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);

//		    printf("\r\n%s, %d: [DEBUG] GyroX : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_gyro[0], read_gyro[1]);
//				printf("\r\n%s, %d: [DEBUG] GyroY : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_gyro[2], read_gyro[3]);
//				printf("\r\n%s, %d: [DEBUG] GyroZ : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_gyro[4], read_gyro[5]);
		return 0;
}

unsigned char icm42688_get_temp(unsigned char *read_temp)
{
		pca9544_i2c_set(ICM42688_CHANNEL);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TEMP_DATA0, 1,&read_temp[0], 1);
		DEV_I2C_Read(ICM42688_IIC_BUS, (unsigned char)ICM42688_IIC_ADDR, ICM42688_TEMP_DATA1, 1,&read_temp[1], 1);
		pca9544_i2c_set(PCA9544_CHANNEL_DISABLED);
//			printf("\r\n%s, %d: [DEBUG] temp : 0x%x, 0x%x. ", __FUNCTION__, __LINE__, read_temp[0], read_temp[1]);
		return 0;
}
