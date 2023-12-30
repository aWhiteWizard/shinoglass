#ifndef _PANNEL_H
#define _PANNEL_H

#include "oled.h"

#define NormalMode              1
#define HAND_VOL                0
#define HAND_GAMMA              0

#define MCU_INITIAL_PANEL       1   //0:7911 LP TO initial panel;   1: GD32 IIC TO INITIAL PANEL
#define  input_1920_1080_60Hz        1   
#define  input_2560_1440_60Hz        0  
#define DSC_19201920_90         0   
#define DSC_25442544_75Hz      0

#define BRIGHT_LEVEL_MAX  1024
#define ADJUST_LEVEL_MAX  1024
#define DEFAULT_BRT_LEVEL 7

typedef enum 
{
    E_PANNEL_0,
    E_PANNEL_1,
    E_PANNEL_103,

    E_PANNEL_MAX
}e_pannel_dev;


typedef struct 
{
    unsigned char iicAddr;
    unsigned char dev_exit; //0-²»´æÔÚ 1-´æÔÚ
    unsigned char bright;
}_pannel_dev_t;



void GPIO_rst_Init(void);
void pannel_reset(void);
void pannel_display(void);
void set_bright(enum OLED_NUM oled_num, uint16_t bright);
void GPIO_2d3d_SW_set(void);

void pannel_config_303(void);
void pannel_init(void);

//void pannel_bright_add(enum OLED_NUM oled_num);
//void pannel_bright_sub(enum OLED_NUM oled_num);

#endif



