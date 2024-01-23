#include "gd32f30x.h"
#include "pannel.h"
#include "systick.h"
#include "dev_iic.h"
#include "tca6408.h"
#include "oled.h"
#include "main.h"

#define Delay_ms(time) delay_1ms(time)  

void GPIO_rst_Init(void)
{
		unsigned char init_config = TCA6408_LV7911_GPIO_16;// | TCA6408_LV7911_RST_N;
		tca6408_write(init_config, TCA6408_OUTPUT);
}

void GPIO_2d3d_SW_set(void)
{
		unsigned char init_config = TCA6408_LV7911_GPIO_14;
		unsigned char read_sw;
		tca6408_read(&read_sw, TCA6408_OUTPUT);
		if((read_sw & TCA6408_LV7911_GPIO_14) == TCA6408_LV7911_GPIO_14)
				read_sw -= TCA6408_LV7911_GPIO_14;
		else 
				read_sw += TCA6408_LV7911_GPIO_14;
	  tca6408_write(read_sw, TCA6408_OUTPUT); 
				printf("\r\n [DEBUG] TCA6408_OUT setvalue = 0x%x", read_sw);
}

void pannel_reset(void)
{   
    tca6408_write(TCA6408_LV7911_GPIO_16, TCA6408_OUTPUT);
    Delay_ms(5);
    tca6408_write(TCA6408_LV7911_GPIO_16 | TCA6408_LV7911_RST_N, TCA6408_OUTPUT);
		Delay_ms(200);              //此处延时>=10ms
} 

void LT7911_RSTN(void)
{
    tca6408_write(TCA6408_LV7911_RST_N, TCA6408_OUTPUT);
    Delay_ms(55);
    tca6408_write(TCA6408_LV7911_GPIO_16 | TCA6408_LV7911_RST_N, TCA6408_OUTPUT);
}
#define CHIP1_ADDR      (0x4c)
#define CHIP2_ADDR      (0x4d)
#define CHIP_ADDR       (0x4e)
#define CHIP103_ADDR    (0x4c)
#define CHIP303_ADDR 		(0xA0)
_pannel_dev_t pannel_t[E_PANNEL_MAX] = 
{
    {CHIP1_ADDR,0,DEFAULT_BRT_LEVEL},{CHIP2_ADDR,0,DEFAULT_BRT_LEVEL},
    {CHIP103_ADDR,0,DEFAULT_BRT_LEVEL},
    
};


uint8_t chip_addr = CHIP303_ADDR;
unsigned char select_pannel(enum OLED_NUM oled_num)
{
		switch (oled_num)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL); break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}

    return chip_addr;
}

unsigned char  set_pannel_exist(enum OLED_NUM oled_num,unsigned char exit)
{
 		switch (oled_num)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL); break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}
    
    pannel_t[oled_num].dev_exit = exit;
    
    return 0;
}


int32_t Write_I2C_cmd(uint16_t RegAddr)
{
    return DEV_I2C_Write(OLED_IIC_BUS ,(unsigned char)OLED_IIC_ADDR ,RegAddr,2,NULL,0);
		printf("\r\n [DEBUG] Write_I2C_cmd OLED_IIC_ADDR is 0x%x, please check!", OLED_IIC_ADDR);
}

int32_t Write_I2C(uint16_t RegAddr,uint16_t RegData)
{
    unsigned char wdata[2] = {0};
    wdata[0] = 0;
    wdata[1] = RegData;
    return DEV_I2C_Write(OLED_IIC_BUS ,(unsigned char)OLED_IIC_ADDR,RegAddr,2,wdata,2);
		printf("\r\n [DEBUG] Write_I2C OLED_IIC_ADDR is 0x%x, please check!", OLED_IIC_ADDR);

}


void pannel_display(void)
{
	for(OLED_NUM i = OLED_0; i <= OLED_1; i++)
	{
		switch (i)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL); break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}
		printf("\r\n [DEBUG] Set OLED CHANNEL 0x%x", i);

#if NormalMode  
//////Normal Display//////////
    Write_I2C_cmd(0x1100);
    Write_I2C_cmd(0x2900);
#else    
///////Bist Display////////// 
//    control_pannel_2();

    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11); 

    Write_I2C(0xC400,0xAA);
    Write_I2C(0xC401,0x55);
    Write_I2C(0xC402,0x01);
    Write_I2C(0xC403,0x80);

    Write_I2C(0xC500,0x00);
    Write_I2C(0xC501,0x80);
    Write_I2C(0xC502,0xFF);
#endif
	}
}

void pannel_config_303(void)
{
	for(OLED_NUM i = OLED_0; i <= OLED_1; i++)
	{
		switch (i)
		{
			case OLED_0: tca9548_i2c_set(OLED_0_CHANNEL); break;
			case OLED_1: tca9548_i2c_set(OLED_1_CHANNEL); break;
			default : printf("\r\n [ERROR] OLED NUM is OLED_0 or OLED_1, please check!");
		}
		printf("\r\n [DEBUG] Set OLED CHANNEL 0x%x", i);
#if input_2560_1440_60Hz 
		{
		//CMD1
    Write_I2C(0x0300,0x80);//DSC close

    Write_I2C(0x5300,0x29);
		
    Write_I2C(0x5100,0xFF);
    Write_I2C(0x5101,0x01);

   // Write_I2C(0x6900,0x02);// for 1920*1080 input
    Write_I2C(0x6900,0x00);// for 2560*1440 input
		
    Write_I2C(0x6B00,0x10);

    Write_I2C(0x8000,0x00);//01 //FHD with 60Hz use 0x00, others use 0x01
    Write_I2C(0x8001,0x40);
    Write_I2C(0x8002,0xb4);
    Write_I2C(0x8003,0x10);

		
		
		
    Write_I2C(0x8100,0x02);
    Write_I2C(0x8101,0x56);
    Write_I2C(0x8102,0x00);
    Write_I2C(0x8103,0x05);//09
    Write_I2C(0x8104,0x00);
    Write_I2C(0x8105,0x23);//0f
    Write_I2C(0x8106,0x00);

    Write_I2C(0x8200,0x02);
    Write_I2C(0x8201,0x56);
    Write_I2C(0x8202,0x00);
    Write_I2C(0x8203,0x05); //09
    Write_I2C(0x8204,0x00);
    Write_I2C(0x8205,0x23);//0f
    Write_I2C(0x8206,0x00);

    Write_I2C(0x2500,0x01);   
//------------------------------------------------------------

	  Write_I2C(0x2b00,0x02); 
    Write_I2C(0x2b01,0x30);	 
		 
		 
		 
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC000,0x00);
    Write_I2C(0xC001,0x04);
    Write_I2C(0xC002,0x00);



//    Write_I2C(0xC200,0x03);
//    Write_I2C(0xC201,0xff);
//    Write_I2C(0xC202,0x03);
//    Write_I2C(0xC203,0xFF);
//    Write_I2C(0xC204,0x03);
//    Write_I2C(0xC205,0xFF);
//    Write_I2C(0xC206,0x00);
//    Write_I2C(0xC207,0x90);
//    Write_I2C(0xC208,0x82);//brightness control
    set_bright(i,DEFAULT_BRT_LEVEL);
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x12);

    Write_I2C(0xD300,0x20);

    Write_I2C(0xBF00,0x37);
    Write_I2C(0xBF01,0xBE);
//rotation begin
    Write_I2C(0x3600,0x03);  //180degree
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x13);

    Write_I2C(0xc101,0xa2);
		
		
	  Write_I2C(0xC400,0x12);
    Write_I2C(0xC401,0x53);
    Write_I2C(0xC402,0x64);
    Write_I2C(0xC403,0x31);
    Write_I2C(0xC404,0x42);
    Write_I2C(0xC405,0x56);
	/////	rotation end
		
		


    Write_I2C(0xFF00,0x5A);
    Write_I2C(0xFF01,0x81);



    Write_I2C(0xF90B,0x58);
    Write_I2C(0xF90C,0x5F);
    Write_I2C(0xF90D,0x66);
    Write_I2C(0xF90E,0x6D);
    Write_I2C(0xF90F,0x74);
    Write_I2C(0xF910,0x7B);
    Write_I2C(0xF911,0x82);
    Write_I2C(0xF912,0x89);
    Write_I2C(0xF913,0x90);
    Write_I2C(0xF914,0x97);
    Write_I2C(0xF915,0x9E);
    Write_I2C(0xF916,0xA5);
    Write_I2C(0xF917,0xAC);


    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC500,0x00);
		Write_I2C(0xC501,0x08);
		Write_I2C(0xC502,0xFF);





    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC000,0xFF);	
	}
#elif input_1920_1080_60Hz
	{
		Write_I2C(0x0300,0x80);//DSC close

    Write_I2C(0x5300,0x29);
    Write_I2C(0x5100,0xFF);
    Write_I2C(0x5101,0x01);

    Write_I2C(0x6900,0x02);// for 1920*1080 input
//    Write_I2C(0x6900,0x00);// for 2560*1440 input
		
    Write_I2C(0x6B00,0x10);

    Write_I2C(0x8000,0x00);//01 //FHD with 60Hz use 0x00, others use 0x01
    Write_I2C(0x8001,0x40);
    Write_I2C(0x8002,0xb4);
    Write_I2C(0x8003,0x10);

		
		
		
    Write_I2C(0x8100,0x02);
    Write_I2C(0x8101,0x56);
    Write_I2C(0x8102,0x00);
    Write_I2C(0x8103,0x05);//09
    Write_I2C(0x8104,0x00);
    Write_I2C(0x8105,0x23);//0f
    Write_I2C(0x8106,0x00);

    Write_I2C(0x8200,0x02);
    Write_I2C(0x8201,0x56);
    Write_I2C(0x8202,0x00);
    Write_I2C(0x8203,0x05);//09
    Write_I2C(0x8204,0x00);
    Write_I2C(0x8205,0x23);//0f
    Write_I2C(0x8206,0x00);

    Write_I2C(0x2500,0x01);   
		
	  Write_I2C(0x2b00,0x02); 
    Write_I2C(0x2b01,0x30);	 
		 
		 
		 
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC000,0x00);
    Write_I2C(0xC001,0x04);
    Write_I2C(0xC002,0x00);



//    Write_I2C(0xC200,0x03);
//    Write_I2C(0xC201,0xff);
//    Write_I2C(0xC202,0x03);
//    Write_I2C(0xC203,0xFF);
//    Write_I2C(0xC204,0x03);
//    Write_I2C(0xC205,0xFF);
//    Write_I2C(0xC206,0x00);
//    Write_I2C(0xC207,0x90);
//    Write_I2C(0xC208,0x82);//brightness control
    set_bright(i,DEFAULT_BRT_LEVEL);
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x12);

    Write_I2C(0xD300,0x20);

    Write_I2C(0xBF00,0x37);
    Write_I2C(0xBF01,0xBE);
//rotation begin
    Write_I2C(0x3600,0x03);  //180degree
		
    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x13);

    Write_I2C(0xc101,0xa2);
		
		
	  Write_I2C(0xC400,0x12);
    Write_I2C(0xC401,0x53);
    Write_I2C(0xC402,0x64);
    Write_I2C(0xC403,0x31);
    Write_I2C(0xC404,0x42);
    Write_I2C(0xC405,0x56);
	/////	rotation end
		
		


    Write_I2C(0xFF00,0x5A);
    Write_I2C(0xFF01,0x81);



    Write_I2C(0xF90B,0x58);
    Write_I2C(0xF90C,0x5F);
    Write_I2C(0xF90D,0x66);
    Write_I2C(0xF90E,0x6D);
    Write_I2C(0xF90F,0x74);
    Write_I2C(0xF910,0x7B);
    Write_I2C(0xF911,0x82);
    Write_I2C(0xF912,0x89);
    Write_I2C(0xF913,0x90);
    Write_I2C(0xF914,0x97);
    Write_I2C(0xF915,0x9E);
    Write_I2C(0xF916,0xA5);
    Write_I2C(0xF917,0xAC);


    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC500,0x00);
		Write_I2C(0xC501,0x08);
		Write_I2C(0xC502,0xFF);





    Write_I2C(0xF000,0xAA);
    Write_I2C(0xF001,0x11);

    Write_I2C(0xC000,0xFF);	
	}
#endif

	}
}	

void set_bright(enum OLED_NUM oled_num, uint16_t bright)
{
    uint16_t curbright = 0;
    uint8_t bright_lo=0,bright_hi=0;

    if(select_pannel(oled_num)==0)
        return ;
    
    if(bright>ADJUST_LEVEL_MAX) 
        bright = ADJUST_LEVEL_MAX;
    if(bright==0)
      curbright = 57;
    else
      curbright = (BRIGHT_LEVEL_MAX/ADJUST_LEVEL_MAX)*bright;
    
    printf("\r\n curbright=%d bright=%d",curbright,bright);
    bright_hi = (bright&0xff00)>>8;
    bright_lo = bright&0xff;
    
//    if(bright==7){
//        bright_hi = 0x03;bright_lo = 0xff;
//    }

    printf("\r\n bright_hi=%02X bright_lo=%02X ",bright_hi,bright_lo);
    
    Write_I2C(0xC200,bright_hi);
    Write_I2C(0xC201,bright_lo);
    Write_I2C(0xC202,bright_hi);
    Write_I2C(0xC203,bright_lo);
    Write_I2C(0xC204,bright_hi);
    Write_I2C(0xC205,bright_lo);
    
//    Write_I2C(0xC206,bright_hi);
//    Write_I2C(0xC207,bright_lo);
//    
    Write_I2C(0xC206,0x00);
    Write_I2C(0xC207,0x90);
    Write_I2C(0xC208,0x82);//brightness control
}


void pannel_init()
{
	
#if MCU_INITIAL_PANEL
	
	{
	
    GPIO_rst_Init();
    pannel_reset();
    Delay_ms(1000); 
  

    pannel_config_303();
    pannel_display();
    
 
     
    LT7911_RSTN();
 
 }
 
#else

{
    GPIO_rst_Init();
    pannel_reset();
   Delay_ms(1000); 
  

  //  pannel_config_103();
  //  pannel_display(E_PANNEL_103);
    


     
   LT7911_RSTN();
 
}

#endif

    
}





