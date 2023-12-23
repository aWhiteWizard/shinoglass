#include "dev_iic.h"
#include "gd32f30x.h"                   // Device header
/* STM32 I2C 快速模式 */
#define I2C_Speed              400000

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2C_OWN_ADDRESS7      0x0A

#define NULL 0
#define SOFT_IIC 1

void GPIO_INIT(void)
{
		rcu_periph_clock_enable(TCA9548_RESET_BIT_RCU);
		gpio_init(TCA9548_RESET_BIT_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, TCA9548_RESET_BIT); 
		TCA9548_RESET_1();
}

/**
  * @brief  触摸屏 I/O配置
  * @param  无
  * @retval 无
  */
void I2C_PRIMARY_GPIO_OUT(void)
{
    
    /* enable I2C clock */
    rcu_periph_clock_enable(DEV_PRIMARY_I2C_SCL_GPIO_RCU);
		rcu_periph_clock_enable(DEV_PRIMARY_I2C_SDA_GPIO_RCU);
#if !(SOFT_IIC)  //使用硬件IIC
    /* enable GPIO clock */
    rcu_periph_clock_enable(DEV_PRIMARY_I2C);
    /*配置SCL引脚 */   
    gpio_init(DEV_PRIMARY_I2C_SCL_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN);

    /*配置SDA引脚 */
    gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
#else  //使用软件IIC
    /*配置SCL引脚 */   
    gpio_init(DEV_PRIMARY_I2C_SCL_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN); 
    I2C_PRIMARY_SCL_1();
    /*配置SDA引脚 */
    gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
    I2C_PRIMARY_SDA_1();
		
#endif
}
/**
  * @brief  触摸屏 I/O配置
  * @param  无
  * @retval 无
  */
void I2C_SECONDARY_GPIO_OUT(void)
{
    /* enable I2C clock */
		rcu_periph_clock_enable(DEV_SECONDARY_I2C_SCL_GPIO_RCU);
		rcu_periph_clock_enable(DEV_SECONDARY_I2C_SDA_GPIO_RCU);

#if !(SOFT_IIC)  //使用硬件IIC
    /* enable GPIO clock */
    rcu_periph_clock_enable(DEV_SECONDARY_I2C);
    /*配置SCL引脚 */   
    gpio_init(DEV_SECONDARY_I2C_SCL_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN);

    /*配置SDA引脚 */
    gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
#else  //使用软件IIC

		/*配置SCL引脚 */   
    gpio_init(DEV_SECONDARY_I2C_SCL_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN); 
    I2C_SECONDARY_SCL_1();
    /*配置SDA引脚 */
    gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
    I2C_SECONDARY_SDA_1();
#endif
}

void I2C_PRIMARY_GPIO_IN(void)
{
    CLK_PRIMARY_In();
		SDA_PRIMARY_In();
}

void I2C_SECONDARY_GPIO_IN(void)
{
    CLK_SECONDARY_In();
		SDA_SECONDARY_In();
}


///**
//  * @brief  I2C0 工作模式配置
//  * @param  无
//  * @retval 无
//  */
static void I2C_PRIMARY_Mode_Config(void)
{
  /* I2C clock configure */
    i2c_clock_config(DEV_PRIMARY_I2C, 100000, I2C_DTCY_2);
    /* I2C address configure */
    i2c_mode_addr_config(DEV_PRIMARY_I2C, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, DEV_IIC_ADDRESS);
    /* enable I2C0 */
    i2c_enable(DEV_PRIMARY_I2C);
    /* enable acknowledge */
    i2c_ack_config(DEV_PRIMARY_I2C, I2C_ACK_ENABLE);
}

///**
//  * @brief  I2C1 工作模式配置
//  * @param  无
//  * @retval 无
//  */
static void I2C_SECONDARY_Mode_Config(void)
{
  /* I2C clock configure */
    i2c_clock_config(DEV_SECONDARY_I2C, 100000, I2C_DTCY_2);
    /* I2C address configure */
    i2c_mode_addr_config(DEV_SECONDARY_I2C, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, DEV_IIC_ADDRESS);
    /* enable I2C1 */
    i2c_enable(DEV_SECONDARY_I2C);
    /* enable acknowledge */
    i2c_ack_config(DEV_SECONDARY_I2C, I2C_ACK_ENABLE);
}

void CLK_PRIMARY_In(void)
{
   gpio_init(DEV_PRIMARY_I2C_SCL_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN); 
}

void SDA_PRIMARY_In(void)
{//浮空输入
	gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
}

void CKL_PRIMARY_Out(void)
{
	gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN);
}

void SDA_PRIMARY_Out(void)
{
	gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
}

void CLK_SECONDARY_In(void)
{
   gpio_init(DEV_SECONDARY_I2C_SCL_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN); 
}

void CKL_SECONDARY_Out(void)
{
	gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN);
}

void SDA_SECONDARY_In(void)
{//浮空输入
	gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
}

void SDA_SECONDARY_Out(void)
{
	gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
}

/**
  * @brief  I2C 外设(GT1xx)初始化
  * @param  无
  * @retval 无
  */
void I2C_Init(void)
{				
    I2C_PRIMARY_GPIO_OUT(); 
    I2C_SECONDARY_GPIO_OUT(); 
 
#if !(SOFT_IIC) //硬件IIC模式 
		I2C_PRIMARY_Mode_Config();
		I2C_SECONDARY_Mode_Config();
#endif

		I2C_PRIMARY_Mode_Config();
		I2C_SECONDARY_Mode_Config();
}


#if !(SOFT_IIC)   //使用硬件IIC     


__IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;

/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_Primary_ReadBytes(unsigned char ClientAddr,unsigned char* pBuffer, uint16_t NumByteToRead)
{  
    /* wait until I2C bus is idle */
    while(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY));
    /* send a start condition to I2C bus */
    i2c_start_on_bus(I2C0);
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(I2C0, I2C0_SLAVE_ADDRESS7, I2C_RECEIVER);

    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND));
    /* clear ADDSEND bit */
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
    
    while(NumByteToRead--){
        if(NumByteToRead == 1)
        {
          /* wait until the second last data byte is received into the shift register */
            while(!i2c_flag_get(I2C0, I2C_FLAG_BTC));
            /* disable acknowledge */
            i2c_ack_config(I2C0, I2C_ACK_DISABLE);
        }
        /* wait until the RBNE bit is set */
        while(!i2c_flag_get(I2C0, I2C_FLAG_RBNE));
        /* read a data from I2C_DATA */
        *pBuffer = i2c_data_receive(I2C0);
        pBuffer++;
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(I2C0);
    /* wait until stop condition generate */ 
    while(I2C_CTL0(I2C0)&0x0200);
    /* enable acknowledge */
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
  
  return 0;
}

/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_Secondary_ReadBytes(unsigned char ClientAddr,unsigned char* pBuffer, uint16_t NumByteToRead)
{  
    /* wait until I2C bus is idle */
    while(i2c_flag_get(I2C1, I2C_FLAG_I2CBSY));
    /* send a start condition to I2C bus */
    i2c_start_on_bus(I2C1);
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(I2C1, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */

    i2c_master_addressing(I2C1, I2C1_SLAVE_ADDRESS7, I2C_RECEIVER);

    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(I2C1, I2C_FLAG_ADDSEND));
    /* clear ADDSEND bit */
    i2c_flag_clear(I2C1, I2C_FLAG_ADDSEND);
    
    while(NumByteToRead--){
        if(NumByteToRead == 1)
        {
          /* wait until the second last data byte is received into the shift register */
            while(!i2c_flag_get(I2C1, I2C_FLAG_BTC));
            /* disable acknowledge */
            i2c_ack_config(I2C1, I2C_ACK_DISABLE);
        }
        /* wait until the RBNE bit is set */
        while(!i2c_flag_get(I2C1, I2C_FLAG_RBNE));
        /* read a data from I2C_DATA */
        *pBuffer = i2c_data_receive(I2C1);
        pBuffer++;
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(I2C1);
    /* wait until stop condition generate */ 
    while(I2C_CTL0(I2C1)&0x0200);
    /* enable acknowledge */
    i2c_ack_config(I2C1, I2C_ACK_ENABLE);
  
  return 0;
}


/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_Primary_WriteBytes(unsigned char ClientAddr,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
  
  /* wait until I2C bus is idle */
    while(i2c_flag_get(DEV_PRIMARY_I2C, I2C_FLAG_I2CBSY));
    /* send a start condition to I2C bus */
    i2c_start_on_bus(DEV_PRIMARY_I2C);
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(DEV_PRIMARY_I2C, I2C_FLAG_SBSEND));
    /* send slave address to I2C bus */
    i2c_master_addressing(DEV_PRIMARY_I2C, I2C0_SLAVE_ADDRESS7, I2C_TRANSMITTER);
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(DEV_PRIMARY_I2C, I2C_FLAG_ADDSEND));
    /* clear ADDSEND bit */
    i2c_flag_clear(DEV_PRIMARY_I2C, I2C_FLAG_ADDSEND);
    /* wait until the transmit data buffer is empty */
    while(!i2c_flag_get(DEV_PRIMARY_I2C, I2C_FLAG_TBE));

    while(NumByteToWrite--){
        /* data transmission */
        i2c_data_transmit(DEV_PRIMARY_I2C, *pBuffer);
        /* Point to the next byte to be written */
        pBuffer++; 
        /* wait until the TBE bit is set */
        while(!i2c_flag_get(DEV_PRIMARY_I2C, I2C_FLAG_TBE));
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(DEV_PRIMARY_I2C);
    while(I2C_CTL0(DEV_PRIMARY_I2C)&0x0200);
  
    return 0;  

}

/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_Secondary_WriteBytes(unsigned char ClientAddr,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
  
  /* wait until I2C bus is idle */
    while(i2c_flag_get(DEV_SECONDARY_I2C, I2C_FLAG_I2CBSY));
    /* send a start condition to I2C bus */
    i2c_start_on_bus(DEV_SECONDARY_I2C);
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(DEV_SECONDARY_I2C, I2C_FLAG_SBSEND));
    /* send slave address to I2C bus */
    i2c_master_addressing(DEV_SECONDARY_I2C, I2C1_SLAVE_ADDRESS7, I2C_TRANSMITTER);
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(DEV_SECONDARY_I2C, I2C_FLAG_ADDSEND));
    /* clear ADDSEND bit */
    i2c_flag_clear(DEV_SECONDARY_I2C, I2C_FLAG_ADDSEND);
    /* wait until the transmit data buffer is empty */
    while(!i2c_flag_get(DEV_SECONDARY_I2C, I2C_FLAG_TBE));

    while(NumByteToWrite--){
        /* data transmission */
        i2c_data_transmit(DEV_SECONDARY_I2C, *pBuffer);
        /* Point to the next byte to be written */
        pBuffer++; 
        /* wait until the TBE bit is set */
        while(!i2c_flag_get(DEV_SECONDARY_I2C, I2C_FLAG_TBE));
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(DEV_SECONDARY_I2C);
    while(I2C_CTL0(DEV_SECONDARY_I2C)&0x0200);
  
    return 0;  

}

/**
  * @brief  IIC等待超时调用本函数输出调试信息
  * @param  None.
  * @retval 返回0xff，表示IIC读取数据失败
  */
static  uint32_t I2C_TIMEOUT_UserCallback(unsigned char errorCode)
{
  /* Block communication and all processes */
  printf("I2C 等待超时!errorCode = %d",errorCode);
  
  return 0xFF;
}

#else //使用软件IIC

/*
*********************************************************************************************************
*	函 数 名: i2c_Delay
*	功能说明: I2C总线位延迟，最快400KHz
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	unsigned char i;

	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
      
		循环次数为5时，约延时5.3us 
		循环次数为10时，约延时8.6~8.8 us ，  
		循环次数为100时，约延时71.6~71.8 us ，  
  */
	for (i = 0; i < 140; i++);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Primary_Start(void)
{
	SDA_PRIMARY_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_PRIMARY_SDA_1();
  i2c_Delay();
	I2C_PRIMARY_SCL_1();
	i2c_Delay();
	I2C_PRIMARY_SDA_0();
	i2c_Delay();
	I2C_PRIMARY_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_Stop
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Primary_Stop(void)
{
	SDA_PRIMARY_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */\
	I2C_PRIMARY_SCL_0();
  i2c_Delay();
	I2C_PRIMARY_SDA_0();
  i2c_Delay();
	I2C_PRIMARY_SCL_1();
	i2c_Delay();
	I2C_PRIMARY_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Secondary_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Secondary_Start(void)
{
	SDA_SECONDARY_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_SECONDARY_SDA_1();
  i2c_Delay();
	I2C_SECONDARY_SCL_1();
	i2c_Delay();
	I2C_SECONDARY_SDA_0();
	i2c_Delay();
	I2C_SECONDARY_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Secondary_Stop
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Secondary_Stop(void)
{
	SDA_SECONDARY_Out();    //设置成推挽输出
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */\
	I2C_SECONDARY_SCL_0();
  i2c_Delay();
	I2C_SECONDARY_SDA_0();
  i2c_Delay();
	I2C_SECONDARY_SCL_1();
	i2c_Delay();
	I2C_SECONDARY_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：_ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
  void i2c_Primary_SendByte(unsigned char _ucByte)
{
	unsigned char i;

	SDA_PRIMARY_Out();    //设置成推挽输出
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			I2C_PRIMARY_SDA_1();
		}
		else
		{
			I2C_PRIMARY_SDA_0();
		}
		i2c_Delay();
		_ucByte <<= 1;	/* 左移一个bit */
		I2C_PRIMARY_SCL_1();
		i2c_Delay();	
		I2C_PRIMARY_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // 释放总线
			//SDA_In();	/* SDA设置为上拉输入 */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Secondary_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参：_ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
  void i2c_Secondary_SendByte(unsigned char _ucByte)
{
	unsigned char i;

	SDA_SECONDARY_Out();    //设置成推挽输出
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			I2C_SECONDARY_SDA_1();
		}
		else
		{
			I2C_SECONDARY_SDA_0();
		}
		i2c_Delay();
		_ucByte <<= 1;	/* 左移一个bit */
		I2C_SECONDARY_SCL_1();
		i2c_Delay();	
		I2C_SECONDARY_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // 释放总线
			//SDA_In();	/* SDA设置为上拉输入 */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
unsigned char i2c_Primary_ReadByte(void)
{
	unsigned char i;
	unsigned char value;

	SDA_PRIMARY_In();	/* SDA设置为上拉输入 */
	
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
	    
		I2C_PRIMARY_SCL_1();
		i2c_Delay();
		value <<= 1;
		if (I2C_PRIMARY_SDA_READ())
		{
			value |= 0x01; 
		}
		I2C_PRIMARY_SCL_0();
		i2c_Delay();
	}
	return value;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Secondary_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
unsigned char i2c_Secondary_ReadByte(void)
{
	unsigned char i;
	unsigned char value;

	SDA_SECONDARY_In();	/* SDA设置为上拉输入 */
	
	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
	    
		I2C_SECONDARY_SCL_1();
		i2c_Delay();
		value <<= 1;
		if (I2C_SECONDARY_SDA_READ())
		{
			value |= 0x01; 
		}
		I2C_SECONDARY_SCL_0();
		i2c_Delay();
	}
	return value;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
unsigned char i2c_Primary_WaitAck(void)
{
	unsigned char time = 0;
	unsigned char re=0;
	I2C_PRIMARY_SDA_1();
	SDA_PRIMARY_In();	/* SDA设置为上拉输入 */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
#if 1
	while (I2C_PRIMARY_SDA_READ() != 0)	/* CPU读取SDA口线状态 */
	{
	    time++;
	    if(time>250){
			re=1;
			break;
	    }
	}
#else
	if (I2C_PRIMARY_SDA_READ())
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
#endif
	I2C_PRIMARY_SCL_0();
	i2c_Delay();
	return re;
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
unsigned char i2c_Secondary_WaitAck(void)
{
  unsigned char time = 0;
	unsigned char re=0;
  I2C_SECONDARY_SDA_1();
	SDA_SECONDARY_In();	/* SDA设置为上拉输入 */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
#if 1
	while (I2C_SECONDARY_SDA_READ() != 0)	/* CPU读取SDA口线状态 */
	{
	    time++;
	    if(time>250){
			re=1;
			break;
	    }
	}
#else
	if (I2C_SECONDARY_SDA_READ())
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
#endif
	I2C_SECONDARY_SCL_0();
	i2c_Delay();
	return re;
}


/*
*********************************************************************************************************
*	函 数 名: i2c_Primary_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Primary_Ack(void)
{
	SDA_PRIMARY_Out();    //设置成推挽输出
	
	I2C_PRIMARY_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_PRIMARY_SCL_0();
	i2c_Delay();
	I2C_PRIMARY_SDA_1();	/* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Secondary_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Secondary_Ack(void)
{
	SDA_SECONDARY_Out();    //设置成推挽输出
	
	I2C_SECONDARY_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SECONDARY_SCL_0();
	i2c_Delay();
	I2C_SECONDARY_SDA_1();	/* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Primary_NAck(void)
{
	SDA_PRIMARY_Out();    //设置成推挽输出
	I2C_PRIMARY_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_PRIMARY_SCL_0();
	i2c_Delay();	
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Secondary_NAck(void)
{
	SDA_SECONDARY_Out();    //设置成推挽输出
	I2C_SECONDARY_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SECONDARY_SCL_0();
	i2c_Delay();	
}

#define I2C_DIR_WR	0		/* 写控制bit */
#define I2C_DIR_RD	1		/* 读控制bit */

/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_Primary_ReadBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	/* 第1步：发起I2C总线启动信号 */
	i2c_Primary_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_Primary_SendByte(ClientAddr | I2C_DIR_RD);	/* 此处是读指令 */
	
	/* 第3步：等待ACK */
	if (i2c_Primary_WaitAck() != 0)
	{
		goto cmd_fail;	/* 器件无应答 */
	}
    //发送寄存器地址
    while(reg_len--)
    {
       i2c_Primary_SendByte(RegAddr>>(8*(reg_len)));
       if (i2c_Primary_WaitAck() != 0)
       {
           goto cmd_fail;  /* 器件无应答 */
       }   
    }

	while(NumByteToRead) 
    {
        *pBuffer = i2c_Primary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Primary_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
            break;
        }
        /* 读指针自增 */
        pBuffer++; 
          
        /*计数器自减 */
        NumByteToRead--;
    
        i2c_Primary_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */  
    }

    /* 发送I2C总线停止信号 */
    i2c_Primary_Stop();
    return 0;	/* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 1;
}

uint32_t I2C_Tca9548_ReadBytes(unsigned char ClientAddr,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	/* 第1步：发起I2C总线启动信号 */
	i2c_Primary_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_Primary_SendByte(ClientAddr | I2C_DIR_RD);	/* 此处是读指令 */
	
	/* 第3步：等待ACK */
	if (i2c_Primary_WaitAck() != 0)
	{
		goto cmd_fail;	/* 器件无应答 */
	}
	while(NumByteToRead) 
    {
        *pBuffer = i2c_Primary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Primary_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
            break;
        }
        /* 读指针自增 */
        pBuffer++; 
          
        /*计数器自减 */
        NumByteToRead--;
    
        i2c_Primary_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */  
    }

    /* 发送I2C总线停止信号 */
    i2c_Primary_Stop();
    return 0;	/* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 1;
}

/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_Primary_WriteBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*　第0步：发停止信号，启动内部写操作　*/
   // i2c_Stop();

    /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
    CLK频率为200KHz时，查询次数为30次左右
    */
    for (m = 0; m < 100; m++)
    {				
        /* 第1步：发起I2C总线启动信号 */
        i2c_Primary_Start();

        /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
        i2c_Primary_SendByte(ClientAddr | I2C_DIR_WR);	/* 此处是写指令 */

        /* 第3步：发送一个时钟，判断器件是否正确应答 */
        if (i2c_Primary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM器件写超时 */
    }	
    //发送寄存器地址
    while(reg_len--)
    {
        i2c_Primary_SendByte(RegAddr>>(8*(reg_len)));
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;  /* 器件无应答 */
        }   
    }

    while(NumByteToWrite--)
    {
        /* 第4步：开始写入数据 */
        i2c_Primary_SendByte(*pBuffer);

        /* 第5步：检查ACK */
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;	/* 器件无应答 */
        }

        pBuffer++;	/* 地址增1 */		
    }
	
	/* 命令执行成功，发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 0;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 1;
}


/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_Tca9548_WriteBytes(unsigned char ClientAddr,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*　第0步：发停止信号，启动内部写操作　*/
   // i2c_Stop();

    /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
    CLK频率为200KHz时，查询次数为30次左右
    */
    for (m = 0; m < 100; m++)
    {				
        /* 第1步：发起I2C总线启动信号 */
        i2c_Primary_Start();

        /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
        i2c_Primary_SendByte(ClientAddr | I2C_DIR_WR);	/* 此处是写指令 */

        /* 第3步：发送一个时钟，判断器件是否正确应答 */
        if (i2c_Primary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM器件写超时 */
    }	
    while(NumByteToWrite--)
    {
        /* 第4步：开始写入数据 */
        i2c_Primary_SendByte(*pBuffer);

        /* 第5步：检查ACK */
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;	/* 器件无应答 */
        }

        pBuffer++;	/* 地址增1 */		
    }
	
	/* 命令执行成功，发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 0;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Primary_Stop();
	return 1;
}

/**
  * @brief   使用IIC读取数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:存放由从机读取的数据的缓冲区指针
  *		@arg NumByteToRead:读取的数据长度
  * @retval  无
  */
uint32_t I2C_Secondary_ReadBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	
	/* 第1步：发起I2C总线启动信号 */
	i2c_Secondary_Start();
	
	/* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
	i2c_Secondary_SendByte(ClientAddr | I2C_DIR_RD);	/* 此处是读指令 */
	
	/* 第3步：等待ACK */
	if (i2c_Secondary_WaitAck() != 0)
	{
		goto cmd_fail;	/* 器件无应答 */
	}
    //发送寄存器地址
    while(reg_len--)
    {
       i2c_Secondary_SendByte(RegAddr>>(8*(reg_len)));
       if (i2c_Secondary_WaitAck() != 0)
       {
           goto cmd_fail;  /* 器件无应答 */
       }   
    }

	while(NumByteToRead) 
    {
        *pBuffer = i2c_Secondary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Secondary_NAck();	/* 最后1个字节读完后，CPU产生NACK信号(驱动SDA = 1) */
            break;
        }
        /* 读指针自增 */
        pBuffer++; 
          
        /*计数器自减 */
        NumByteToRead--;
    
        i2c_Secondary_Ack();	/* 中间字节读完后，CPU产生ACK信号(驱动SDA = 0) */  
    }

    /* 发送I2C总线停止信号 */
    i2c_Secondary_Stop();
    return 0;	/* 执行成功 */

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Secondary_Stop();
	return 1;
}

/**
  * @brief   使用IIC写入数据
  * @param   
  * 	@arg ClientAddr:从设备地址
  *		@arg pBuffer:缓冲区指针
  *     @arg NumByteToWrite:写的字节数
  * @retval  无
  */
uint32_t I2C_Secondary_WriteBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*　第0步：发停止信号，启动内部写操作　*/
   // i2c_Stop();

    /* 通过检查器件应答的方式，判断内部写操作是否完成, 一般小于 10ms 			
    CLK频率为200KHz时，查询次数为30次左右
    */
    for (m = 0; m < 100; m++)
    {				
        /* 第1步：发起I2C总线启动信号 */
        i2c_Secondary_Start();

        /* 第2步：发起控制字节，高7bit是地址，bit0是读写控制位，0表示写，1表示读 */
        i2c_Secondary_SendByte(ClientAddr | I2C_DIR_WR);	/* 此处是写指令 */

        /* 第3步：发送一个时钟，判断器件是否正确应答 */
        if (i2c_Secondary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM器件写超时 */
    }	
    //发送寄存器地址
    while(reg_len--)
    {
        i2c_Secondary_SendByte(RegAddr>>(8*(reg_len)));
        if (i2c_Secondary_WaitAck() != 0)
        {
            goto cmd_fail;  /* 器件无应答 */
        }   
    }

    while(NumByteToWrite--)
    {
        /* 第4步：开始写入数据 */
        i2c_Secondary_SendByte(*pBuffer);

        /* 第5步：检查ACK */
        if (i2c_Secondary_WaitAck() != 0)
        {
            goto cmd_fail;	/* 器件无应答 */
        }

        pBuffer++;	/* 地址增1 */		
    }
	
	/* 命令执行成功，发送I2C总线停止信号 */
	i2c_Secondary_Stop();
	return 0;

cmd_fail: /* 命令执行失败后，切记发送停止信号，避免影响I2C总线上其他设备 */
	/* 发送I2C总线停止信号 */
	i2c_Secondary_Stop();
	return 1;
}
#endif

/**
  * @brief   使用IIC进行数据传输
  * @param
  *		@arg i2c_msg:数据传输结构体
  *		@arg num:数据传输结构体的个数
  * @retval  正常完成的传输结构个数，若不正常，返回0xff
  */
int I2C_Primary_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//根据flag判断是读数据还是写数据
		{
			//ret = I2C_Primary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC读取数据
			ret = I2C_Primary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC读取数据
		} else
		{
			ret = I2C_Primary_WriteBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);	//IIC写入数据
		}
	}

	if(ret) //若失败
		return -1;

	return im;   													//正常完成的传输结构个数
}
	/**
  * @brief   使用IIC进行数据传输
  * @param
  *		@arg i2c_msg:数据传输结构体
  *		@arg num:数据传输结构体的个数
  * @retval  正常完成的传输结构个数，若不正常，返回0xff
  */
int I2C_Tca9548_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//根据flag判断是读数据还是写数据
		{
			ret = I2C_Tca9548_ReadBytes(msgs[im].addr,msgs[im].buf, msgs[im].len);		//IIC读取数据
		} else
		{
			ret = I2C_Tca9548_WriteBytes(msgs[im].addr,msgs[im].buf, msgs[im].len);	//IIC写入数据
		}
	}

	if(ret) //若失败
		return -1;

	return im;   													//正常完成的传输结构个数
}

/**
  * @brief   使用IIC进行数据传输
  * @param
  *		@arg i2c_msg:数据传输结构体
  *		@arg num:数据传输结构体的个数
  * @retval  正常完成的传输结构个数，若不正常，返回0xff
  */
int I2C_Secondary_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//根据flag判断是读数据还是写数据
		{
			ret = I2C_Secondary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC读取数据
		} else
		{
			ret = I2C_Secondary_WriteBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);	//IIC写入数据
		}
	}

	if(ret) //若失败
		return -1;

	return im;   													//正常完成的传输结构个数
}



/**
  * @brief   从IIC设备中读取数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 读取数据寄存器的起始地址
  *		@arg buf[2~len-1]: 存储读出来数据的缓冲buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count（寄存器地址长度+读取的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，2为成功，其它为失败
  */
int32_t DEV_I2C_Read(unsigned char i2c_bus, unsigned char client_addr,uint16_t reg_addr,unsigned char reg_len,unsigned char *buf, int32_t len)
{
    struct i2c_msg msgs[2];
    int32_t ret=-1;
    int32_t retries = 0;
    unsigned char regaddr[2] = {0};
    switch(i2c_bus)
		{
      case 0:I2C_PRIMARY_GPIO_OUT(); break;
      case 1:I2C_SECONDARY_GPIO_OUT(); break;
      default : printf("\r\n I2C bus is Only 0: primary or 1: Secondary,please check");
    }
    /*一个读数据的过程可以分为两个传输过程:
     * 1. IIC  写入 要读取的寄存器地址
     * 2. IIC  读取  数据
     * */
    if(reg_len==2){
        regaddr[0] = (reg_addr>>8)&0xff;
        regaddr[1] = (reg_addr)&0xff;
    }
    else if(reg_len==1){
       regaddr[0] = (reg_addr)&0xff; 
    }
    
    msgs[0].flags = !I2C_M_RD;					//写入
    msgs[0].addr  = client_addr;					//IIC设备地址
    msgs[0].regaddr = reg_addr;
    msgs[0].reg_len = reg_len;
    msgs[0].len   = 0;	                        //寄存器地址为2字节(即写入两字节的数据)
    msgs[0].buf   = NULL;						//buf[0~1]存储的是要读取的寄存器地址
    
    msgs[1].flags = I2C_M_RD;					//读取
    msgs[1].addr  = client_addr;					//IIC设备地址
    msgs[1].reg_len = 0;
    msgs[1].len   = len ;	                    //要读取的数据长度
    msgs[1].buf   = &buf[0];	                //buf[GTP_ADDR_LENGTH]之后的缓冲区存储读出的数据

		switch(i2c_bus)
		{
			case 0: while(retries < 5)
              {
                  ret = I2C_Primary_Transfer(msgs, 2);					//调用IIC数据传输过程函数，有2个传输过程
                  if(ret == 2)break;
                  retries++;
              }

              if((retries >= 5))
              {
                  printf("\r\n%s, %d I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset, retires.", __FUNCTION__, __LINE__, (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
                  I2C_PRIMARY_GPIO_IN();
                  return -1;
              } 
              I2C_PRIMARY_GPIO_IN();
              break;
      case 1: while(retries < 5)
							{
									ret = I2C_Secondary_Transfer(msgs, 2);					//调用IIC数据传输过程函数，有2个传输过程
									if(ret == 2)break;
									retries++;
							}

							if((retries >= 5))
							{
									printf("\r\n%s, %d I2C Read: 0x%04X, %d bytes failed, errcode: %d! Process reset.", __FUNCTION__, __LINE__ , (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
									I2C_SECONDARY_GPIO_IN();
									return -1;
							} 
							I2C_SECONDARY_GPIO_IN();
							break;         
      default: printf("\r\n I2C bus is Only 0: primary or 1: Secondary,please check");
		}
    return 0;
}



/**
  * @brief   向IIC设备写入数据
  * @param
  *		@arg client_addr:设备地址
  *		@arg  buf[0~1]: 要写入的数据寄存器的起始地址
  *		@arg buf[2~len-1]: 要写入的数据
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count（寄存器地址长度+写入的数据字节数）
  * @retval  i2c_msgs传输结构体的个数，1为成功，其它为失败
  */
int32_t DEV_I2C_Write(unsigned char i2c_bus, unsigned char client_addr,uint16_t reg_addr,unsigned char reg_len,unsigned char *buf,int32_t len)
{
    struct i2c_msg msg;
    int32_t ret = -1;
    int32_t retries = 0;
    switch(i2c_bus)
		{
      case 0:I2C_PRIMARY_GPIO_OUT(); break;
      case 1:I2C_SECONDARY_GPIO_OUT(); break;
      default : printf("\r\n I2C bus is Only 0: primary or 1: Secondary,please check");
    }
#define RE_CONT  3
   
    /*一个写数据的过程只需要一个传输过程:
     * 1. IIC连续 写入 数据寄存器地址及数据
     * */
    msg.flags = !I2C_M_RD;			//写入
    msg.addr  = client_addr;			//从设备地址
    msg.regaddr = reg_addr;
    msg.reg_len = reg_len;
    msg.len   = len;							//长度直接等于(寄存器地址长度+写入的数据字节数)
    msg.buf   = buf;						//直接连续写入缓冲区中的数据(包括了寄存器地址)

		switch(i2c_bus)
		{
			case 0:     while(retries < RE_CONT)
              {
                  ret = I2C_Primary_Transfer(&msg, 1);	//调用IIC数据传输过程函数，1个传输过程
                  if (ret == 1)break;
                  retries++;
              }

              if((retries >= RE_CONT))
              {
								  printf("\r\n%s, %d: CHIP_ADDR 0x%x REG_ADDR : 0x%04x I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", __FUNCTION__, __LINE__,client_addr, reg_addr  , (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
                  I2C_PRIMARY_GPIO_IN();
                  return -1;
              }
              I2C_PRIMARY_GPIO_IN();
              break;
      case 1:     while(retries < RE_CONT)
              {
                  ret = I2C_Secondary_Transfer(&msg, 1);	//调用IIC数据传输过程函数，1个传输过程
                  if (ret == 1)break;
                  retries++;
              }

              if((retries >= RE_CONT))
              {
                  printf("\r\n I2C Write: 0x%04X, %d bytes failed, errcode: %d! Process reset.", (((uint16_t)(buf[0] << 8)) | buf[1]), len-2, ret);
                  I2C_SECONDARY_GPIO_IN();
                  return -1;
              }
              I2C_SECONDARY_GPIO_IN();
        break;         
      default: printf("\r\n I2C bus is Only 0: primary or 1: Secondary,please check");
		}


    return 0;
}
/*********************************************END OF FILE**********************/








