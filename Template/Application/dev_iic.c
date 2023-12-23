#include "dev_iic.h"
#include "gd32f30x.h"                   // Device header
/* STM32 I2C ����ģʽ */
#define I2C_Speed              400000

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
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
  * @brief  ������ I/O����
  * @param  ��
  * @retval ��
  */
void I2C_PRIMARY_GPIO_OUT(void)
{
    
    /* enable I2C clock */
    rcu_periph_clock_enable(DEV_PRIMARY_I2C_SCL_GPIO_RCU);
		rcu_periph_clock_enable(DEV_PRIMARY_I2C_SDA_GPIO_RCU);
#if !(SOFT_IIC)  //ʹ��Ӳ��IIC
    /* enable GPIO clock */
    rcu_periph_clock_enable(DEV_PRIMARY_I2C);
    /*����SCL���� */   
    gpio_init(DEV_PRIMARY_I2C_SCL_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN);

    /*����SDA���� */
    gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
#else  //ʹ�����IIC
    /*����SCL���� */   
    gpio_init(DEV_PRIMARY_I2C_SCL_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SCL_PIN); 
    I2C_PRIMARY_SCL_1();
    /*����SDA���� */
    gpio_init(DEV_PRIMARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_PRIMARY_I2C_SDA_PIN);
    I2C_PRIMARY_SDA_1();
		
#endif
}
/**
  * @brief  ������ I/O����
  * @param  ��
  * @retval ��
  */
void I2C_SECONDARY_GPIO_OUT(void)
{
    /* enable I2C clock */
		rcu_periph_clock_enable(DEV_SECONDARY_I2C_SCL_GPIO_RCU);
		rcu_periph_clock_enable(DEV_SECONDARY_I2C_SDA_GPIO_RCU);

#if !(SOFT_IIC)  //ʹ��Ӳ��IIC
    /* enable GPIO clock */
    rcu_periph_clock_enable(DEV_SECONDARY_I2C);
    /*����SCL���� */   
    gpio_init(DEV_SECONDARY_I2C_SCL_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN);

    /*����SDA���� */
    gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
#else  //ʹ�����IIC

		/*����SCL���� */   
    gpio_init(DEV_SECONDARY_I2C_SCL_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SCL_PIN); 
    I2C_SECONDARY_SCL_1();
    /*����SDA���� */
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
//  * @brief  I2C0 ����ģʽ����
//  * @param  ��
//  * @retval ��
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
//  * @brief  I2C1 ����ģʽ����
//  * @param  ��
//  * @retval ��
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
{//��������
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
{//��������
	gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
}

void SDA_SECONDARY_Out(void)
{
	gpio_init(DEV_SECONDARY_I2C_SDA_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_SECONDARY_I2C_SDA_PIN);
}

/**
  * @brief  I2C ����(GT1xx)��ʼ��
  * @param  ��
  * @retval ��
  */
void I2C_Init(void)
{				
    I2C_PRIMARY_GPIO_OUT(); 
    I2C_SECONDARY_GPIO_OUT(); 
 
#if !(SOFT_IIC) //Ӳ��IICģʽ 
		I2C_PRIMARY_Mode_Config();
		I2C_SECONDARY_Mode_Config();
#endif

		I2C_PRIMARY_Mode_Config();
		I2C_SECONDARY_Mode_Config();
}


#if !(SOFT_IIC)   //ʹ��Ӳ��IIC     


__IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;

/**
  * @brief   ʹ��IIC��ȡ����
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:����ɴӻ���ȡ�����ݵĻ�����ָ��
  *		@arg NumByteToRead:��ȡ�����ݳ���
  * @retval  ��
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
  * @brief   ʹ��IIC��ȡ����
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:����ɴӻ���ȡ�����ݵĻ�����ָ��
  *		@arg NumByteToRead:��ȡ�����ݳ���
  * @retval  ��
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
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
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
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
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
  * @brief  IIC�ȴ���ʱ���ñ��������������Ϣ
  * @param  None.
  * @retval ����0xff����ʾIIC��ȡ����ʧ��
  */
static  uint32_t I2C_TIMEOUT_UserCallback(unsigned char errorCode)
{
  /* Block communication and all processes */
  printf("I2C �ȴ���ʱ!errorCode = %d",errorCode);
  
  return 0xFF;
}

#else //ʹ�����IIC

/*
*********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	unsigned char i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
      
		ѭ������Ϊ5ʱ��Լ��ʱ5.3us 
		ѭ������Ϊ10ʱ��Լ��ʱ8.6~8.8 us ��  
		ѭ������Ϊ100ʱ��Լ��ʱ71.6~71.8 us ��  
  */
	for (i = 0; i < 140; i++);
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Primary_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Primary_Start(void)
{
	SDA_PRIMARY_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
*	�� �� ��: i2c_Primary_Stop
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Primary_Stop(void)
{
	SDA_PRIMARY_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */\
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
*	�� �� ��: i2c_Secondary_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Secondary_Start(void)
{
	SDA_SECONDARY_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
*	�� �� ��: i2c_Secondary_Stop
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Secondary_Stop(void)
{
	SDA_SECONDARY_Out();    //���ó��������
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */\
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
*	�� �� ��: i2c_Primary_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
  void i2c_Primary_SendByte(unsigned char _ucByte)
{
	unsigned char i;

	SDA_PRIMARY_Out();    //���ó��������
	/* �ȷ����ֽڵĸ�λbit7 */
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
		_ucByte <<= 1;	/* ����һ��bit */
		I2C_PRIMARY_SCL_1();
		i2c_Delay();	
		I2C_PRIMARY_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // �ͷ�����
			//SDA_In();	/* SDA����Ϊ�������� */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Secondary_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
  void i2c_Secondary_SendByte(unsigned char _ucByte)
{
	unsigned char i;

	SDA_SECONDARY_Out();    //���ó��������
	/* �ȷ����ֽڵĸ�λbit7 */
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
		_ucByte <<= 1;	/* ����һ��bit */
		I2C_SECONDARY_SCL_1();
		i2c_Delay();	
		I2C_SECONDARY_SCL_0();
		if (i == 7)
		{
//			 I2C_SDA_1(); // �ͷ�����
			//SDA_In();	/* SDA����Ϊ�������� */
		}
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Primary_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
unsigned char i2c_Primary_ReadByte(void)
{
	unsigned char i;
	unsigned char value;

	SDA_PRIMARY_In();	/* SDA����Ϊ�������� */
	
	/* ������1��bitΪ���ݵ�bit7 */
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
*	�� �� ��: i2c_Secondary_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
unsigned char i2c_Secondary_ReadByte(void)
{
	unsigned char i;
	unsigned char value;

	SDA_SECONDARY_In();	/* SDA����Ϊ�������� */
	
	/* ������1��bitΪ���ݵ�bit7 */
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
*	�� �� ��: i2c_Primary_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
unsigned char i2c_Primary_WaitAck(void)
{
	unsigned char time = 0;
	unsigned char re=0;
	I2C_PRIMARY_SDA_1();
	SDA_PRIMARY_In();	/* SDA����Ϊ�������� */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
#if 1
	while (I2C_PRIMARY_SDA_READ() != 0)	/* CPU��ȡSDA����״̬ */
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
*	�� �� ��: i2c_Primary_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
unsigned char i2c_Secondary_WaitAck(void)
{
  unsigned char time = 0;
	unsigned char re=0;
  I2C_SECONDARY_SDA_1();
	SDA_SECONDARY_In();	/* SDA����Ϊ�������� */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
#if 1
	while (I2C_SECONDARY_SDA_READ() != 0)	/* CPU��ȡSDA����״̬ */
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
*	�� �� ��: i2c_Primary_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Primary_Ack(void)
{
	SDA_PRIMARY_Out();    //���ó��������
	
	I2C_PRIMARY_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_PRIMARY_SCL_0();
	i2c_Delay();
	I2C_PRIMARY_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Secondary_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Secondary_Ack(void)
{
	SDA_SECONDARY_Out();    //���ó��������
	
	I2C_SECONDARY_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SECONDARY_SCL_0();
	i2c_Delay();
	I2C_SECONDARY_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Primary_NAck(void)
{
	SDA_PRIMARY_Out();    //���ó��������
	I2C_PRIMARY_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_PRIMARY_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_PRIMARY_SCL_0();
	i2c_Delay();	
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Secondary_NAck(void)
{
	SDA_SECONDARY_Out();    //���ó��������
	I2C_SECONDARY_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SECONDARY_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SECONDARY_SCL_0();
	i2c_Delay();	
}

#define I2C_DIR_WR	0		/* д����bit */
#define I2C_DIR_RD	1		/* ������bit */

/**
  * @brief   ʹ��IIC��ȡ����
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:����ɴӻ���ȡ�����ݵĻ�����ָ��
  *		@arg NumByteToRead:��ȡ�����ݳ���
  * @retval  ��
  */
uint32_t I2C_Primary_ReadBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	/* ��1��������I2C���������ź� */
	i2c_Primary_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_Primary_SendByte(ClientAddr | I2C_DIR_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��3�����ȴ�ACK */
	if (i2c_Primary_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}
    //���ͼĴ�����ַ
    while(reg_len--)
    {
       i2c_Primary_SendByte(RegAddr>>(8*(reg_len)));
       if (i2c_Primary_WaitAck() != 0)
       {
           goto cmd_fail;  /* ������Ӧ�� */
       }   
    }

	while(NumByteToRead) 
    {
        *pBuffer = i2c_Primary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Primary_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
            break;
        }
        /* ��ָ������ */
        pBuffer++; 
          
        /*�������Լ� */
        NumByteToRead--;
    
        i2c_Primary_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */  
    }

    /* ����I2C����ֹͣ�ź� */
    i2c_Primary_Stop();
    return 0;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 1;
}

uint32_t I2C_Tca9548_ReadBytes(unsigned char ClientAddr,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	/* ��1��������I2C���������ź� */
	i2c_Primary_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_Primary_SendByte(ClientAddr | I2C_DIR_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��3�����ȴ�ACK */
	if (i2c_Primary_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}
	while(NumByteToRead) 
    {
        *pBuffer = i2c_Primary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Primary_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
            break;
        }
        /* ��ָ������ */
        pBuffer++; 
          
        /*�������Լ� */
        NumByteToRead--;
    
        i2c_Primary_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */  
    }

    /* ����I2C����ֹͣ�ź� */
    i2c_Primary_Stop();
    return 0;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 1;
}

/**
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
uint32_t I2C_Primary_WriteBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*����0������ֹͣ�źţ������ڲ�д������*/
   // i2c_Stop();

    /* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
    CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
    */
    for (m = 0; m < 100; m++)
    {				
        /* ��1��������I2C���������ź� */
        i2c_Primary_Start();

        /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
        i2c_Primary_SendByte(ClientAddr | I2C_DIR_WR);	/* �˴���дָ�� */

        /* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
        if (i2c_Primary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM����д��ʱ */
    }	
    //���ͼĴ�����ַ
    while(reg_len--)
    {
        i2c_Primary_SendByte(RegAddr>>(8*(reg_len)));
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;  /* ������Ӧ�� */
        }   
    }

    while(NumByteToWrite--)
    {
        /* ��4������ʼд������ */
        i2c_Primary_SendByte(*pBuffer);

        /* ��5�������ACK */
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;	/* ������Ӧ�� */
        }

        pBuffer++;	/* ��ַ��1 */		
    }
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 0;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 1;
}


/**
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
uint32_t I2C_Tca9548_WriteBytes(unsigned char ClientAddr,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*����0������ֹͣ�źţ������ڲ�д������*/
   // i2c_Stop();

    /* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
    CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
    */
    for (m = 0; m < 100; m++)
    {				
        /* ��1��������I2C���������ź� */
        i2c_Primary_Start();

        /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
        i2c_Primary_SendByte(ClientAddr | I2C_DIR_WR);	/* �˴���дָ�� */

        /* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
        if (i2c_Primary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM����д��ʱ */
    }	
    while(NumByteToWrite--)
    {
        /* ��4������ʼд������ */
        i2c_Primary_SendByte(*pBuffer);

        /* ��5�������ACK */
        if (i2c_Primary_WaitAck() != 0)
        {
            goto cmd_fail;	/* ������Ӧ�� */
        }

        pBuffer++;	/* ��ַ��1 */		
    }
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 0;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Primary_Stop();
	return 1;
}

/**
  * @brief   ʹ��IIC��ȡ����
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:����ɴӻ���ȡ�����ݵĻ�����ָ��
  *		@arg NumByteToRead:��ȡ�����ݳ���
  * @retval  ��
  */
uint32_t I2C_Secondary_ReadBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer, uint16_t NumByteToRead)
{
	
	/* ��1��������I2C���������ź� */
	i2c_Secondary_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_Secondary_SendByte(ClientAddr | I2C_DIR_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��3�����ȴ�ACK */
	if (i2c_Secondary_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}
    //���ͼĴ�����ַ
    while(reg_len--)
    {
       i2c_Secondary_SendByte(RegAddr>>(8*(reg_len)));
       if (i2c_Secondary_WaitAck() != 0)
       {
           goto cmd_fail;  /* ������Ӧ�� */
       }   
    }

	while(NumByteToRead) 
    {
        *pBuffer = i2c_Secondary_ReadByte();
        if(NumByteToRead == 1)
        {
            i2c_Secondary_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
            break;
        }
        /* ��ָ������ */
        pBuffer++; 
          
        /*�������Լ� */
        NumByteToRead--;
    
        i2c_Secondary_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */  
    }

    /* ����I2C����ֹͣ�ź� */
    i2c_Secondary_Stop();
    return 0;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Secondary_Stop();
	return 1;
}

/**
  * @brief   ʹ��IICд������
  * @param   
  * 	@arg ClientAddr:���豸��ַ
  *		@arg pBuffer:������ָ��
  *     @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
uint32_t I2C_Secondary_WriteBytes(unsigned char ClientAddr,uint16_t RegAddr,unsigned char reg_len,unsigned char* pBuffer,  unsigned char NumByteToWrite)
{
	uint16_t m;	

    /*����0������ֹͣ�źţ������ڲ�д������*/
   // i2c_Stop();

    /* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
    CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
    */
    for (m = 0; m < 100; m++)
    {				
        /* ��1��������I2C���������ź� */
        i2c_Secondary_Start();

        /* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
        i2c_Secondary_SendByte(ClientAddr | I2C_DIR_WR);	/* �˴���дָ�� */

        /* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
        if (i2c_Secondary_WaitAck() == 0)
        {
            break;
        }
    }
    if (m  == 100)
    {
        goto cmd_fail;	/* EEPROM����д��ʱ */
    }	
    //���ͼĴ�����ַ
    while(reg_len--)
    {
        i2c_Secondary_SendByte(RegAddr>>(8*(reg_len)));
        if (i2c_Secondary_WaitAck() != 0)
        {
            goto cmd_fail;  /* ������Ӧ�� */
        }   
    }

    while(NumByteToWrite--)
    {
        /* ��4������ʼд������ */
        i2c_Secondary_SendByte(*pBuffer);

        /* ��5�������ACK */
        if (i2c_Secondary_WaitAck() != 0)
        {
            goto cmd_fail;	/* ������Ӧ�� */
        }

        pBuffer++;	/* ��ַ��1 */		
    }
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Secondary_Stop();
	return 0;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Secondary_Stop();
	return 1;
}
#endif

/**
  * @brief   ʹ��IIC�������ݴ���
  * @param
  *		@arg i2c_msg:���ݴ���ṹ��
  *		@arg num:���ݴ���ṹ��ĸ���
  * @retval  ������ɵĴ���ṹ��������������������0xff
  */
int I2C_Primary_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//����flag�ж��Ƕ����ݻ���д����
		{
			//ret = I2C_Primary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC��ȡ����
			ret = I2C_Primary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC��ȡ����
		} else
		{
			ret = I2C_Primary_WriteBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);	//IICд������
		}
	}

	if(ret) //��ʧ��
		return -1;

	return im;   													//������ɵĴ���ṹ����
}
	/**
  * @brief   ʹ��IIC�������ݴ���
  * @param
  *		@arg i2c_msg:���ݴ���ṹ��
  *		@arg num:���ݴ���ṹ��ĸ���
  * @retval  ������ɵĴ���ṹ��������������������0xff
  */
int I2C_Tca9548_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//����flag�ж��Ƕ����ݻ���д����
		{
			ret = I2C_Tca9548_ReadBytes(msgs[im].addr,msgs[im].buf, msgs[im].len);		//IIC��ȡ����
		} else
		{
			ret = I2C_Tca9548_WriteBytes(msgs[im].addr,msgs[im].buf, msgs[im].len);	//IICд������
		}
	}

	if(ret) //��ʧ��
		return -1;

	return im;   													//������ɵĴ���ṹ����
}

/**
  * @brief   ʹ��IIC�������ݴ���
  * @param
  *		@arg i2c_msg:���ݴ���ṹ��
  *		@arg num:���ݴ���ṹ��ĸ���
  * @retval  ������ɵĴ���ṹ��������������������0xff
  */
int I2C_Secondary_Transfer( struct i2c_msg *msgs, int num)
{
	int im = 0;
	int ret = 0;

	for (im = 0; ret == 0 && im < num; im++)
	{
		if ((msgs[im].flags&I2C_M_RD))																//����flag�ж��Ƕ����ݻ���д����
		{
			ret = I2C_Secondary_ReadBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);		//IIC��ȡ����
		} else
		{
			ret = I2C_Secondary_WriteBytes(msgs[im].addr,msgs[im].regaddr,msgs[im].reg_len,msgs[im].buf, msgs[im].len);	//IICд������
		}
	}

	if(ret) //��ʧ��
		return -1;

	return im;   													//������ɵĴ���ṹ����
}



/**
  * @brief   ��IIC�豸�ж�ȡ����
  * @param
  *		@arg client_addr:�豸��ַ
  *		@arg  buf[0~1]: ��ȡ���ݼĴ�������ʼ��ַ
  *		@arg buf[2~len-1]: �洢���������ݵĻ���buffer
  *		@arg len:    GTP_ADDR_LENGTH + read bytes count���Ĵ�����ַ����+��ȡ�������ֽ�����
  * @retval  i2c_msgs����ṹ��ĸ�����2Ϊ�ɹ�������Ϊʧ��
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
    /*һ�������ݵĹ��̿��Է�Ϊ�����������:
     * 1. IIC  д�� Ҫ��ȡ�ļĴ�����ַ
     * 2. IIC  ��ȡ  ����
     * */
    if(reg_len==2){
        regaddr[0] = (reg_addr>>8)&0xff;
        regaddr[1] = (reg_addr)&0xff;
    }
    else if(reg_len==1){
       regaddr[0] = (reg_addr)&0xff; 
    }
    
    msgs[0].flags = !I2C_M_RD;					//д��
    msgs[0].addr  = client_addr;					//IIC�豸��ַ
    msgs[0].regaddr = reg_addr;
    msgs[0].reg_len = reg_len;
    msgs[0].len   = 0;	                        //�Ĵ�����ַΪ2�ֽ�(��д�����ֽڵ�����)
    msgs[0].buf   = NULL;						//buf[0~1]�洢����Ҫ��ȡ�ļĴ�����ַ
    
    msgs[1].flags = I2C_M_RD;					//��ȡ
    msgs[1].addr  = client_addr;					//IIC�豸��ַ
    msgs[1].reg_len = 0;
    msgs[1].len   = len ;	                    //Ҫ��ȡ�����ݳ���
    msgs[1].buf   = &buf[0];	                //buf[GTP_ADDR_LENGTH]֮��Ļ������洢����������

		switch(i2c_bus)
		{
			case 0: while(retries < 5)
              {
                  ret = I2C_Primary_Transfer(msgs, 2);					//����IIC���ݴ�����̺�������2���������
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
									ret = I2C_Secondary_Transfer(msgs, 2);					//����IIC���ݴ�����̺�������2���������
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
  * @brief   ��IIC�豸д������
  * @param
  *		@arg client_addr:�豸��ַ
  *		@arg  buf[0~1]: Ҫд������ݼĴ�������ʼ��ַ
  *		@arg buf[2~len-1]: Ҫд�������
  *		@arg len:    GTP_ADDR_LENGTH + write bytes count���Ĵ�����ַ����+д��������ֽ�����
  * @retval  i2c_msgs����ṹ��ĸ�����1Ϊ�ɹ�������Ϊʧ��
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
   
    /*һ��д���ݵĹ���ֻ��Ҫһ���������:
     * 1. IIC���� д�� ���ݼĴ�����ַ������
     * */
    msg.flags = !I2C_M_RD;			//д��
    msg.addr  = client_addr;			//���豸��ַ
    msg.regaddr = reg_addr;
    msg.reg_len = reg_len;
    msg.len   = len;							//����ֱ�ӵ���(�Ĵ�����ַ����+д��������ֽ���)
    msg.buf   = buf;						//ֱ������д�뻺�����е�����(�����˼Ĵ�����ַ)

		switch(i2c_bus)
		{
			case 0:     while(retries < RE_CONT)
              {
                  ret = I2C_Primary_Transfer(&msg, 1);	//����IIC���ݴ�����̺�����1���������
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
                  ret = I2C_Secondary_Transfer(&msg, 1);	//����IIC���ݴ�����̺�����1���������
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








