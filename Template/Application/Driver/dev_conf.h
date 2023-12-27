#ifndef _DEV_CONF_H_
#define _DEV_CONF_H_

#include "stdio.h"

#define MICRO_7911UXC 1
#define MICRO_TD     0
#if MICRO_TD  

#define GLASSES_BOARD     0



/*I2C����*/
#define DEV_I2C                          I2C0
#define DEV_I2C_RCU                      RCU_I2C0

#define DEV_I2C_SCL_PIN                  GPIO_PIN_6                 
#define DEV_I2C_SCL_GPIO_PORT            GPIOB                      
#define DEV_I2C_SCL_GPIO_RCU             RCU_GPIOB

#define DEV_I2C_SDA_PIN                  GPIO_PIN_7                  
#define DEV_I2C_SDA_GPIO_PORT            GPIOB                    
#define DEV_I2C_SDA_GPIO_RCU             RCU_GPIOB


//aw37501 ��Դ����  enable
#define DEV_ENP_GPIO_RCU   RCU_GPIOA
#define DEV_ENP_GPIO_PORT  GPIOA
#define DEV_ENP_GPIO_PIN   GPIO_PIN_1

#define DEV_ENN_GPIO_RCU   RCU_GPIOA
#define DEV_ENN_GPIO_PORT  GPIOA
#define DEV_ENN_GPIO_PIN   GPIO_PIN_2



//key ����
#define DEV_KEY_BRT_P_RCU   RCU_GPIOA
#define DEV_KEY_BRT_P_PORT  GPIOA
#define DEV_KEY_BRT_P_PIN   GPIO_PIN_6
#define DEV_KEY_BRT_P_EXIT  EXTI_6
#define DEV_KEY_BRT_P_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_BRT_P_EXIT_PIN      GPIO_PIN_SOURCE_6
#define DEV_KEY_BRT_P_NVIC          EXTI5_9_IRQn
//#define key_brt_p_irq  EXTI5_9_IRQHandler



#define DEV_KEY_BRT_N_RCU   RCU_GPIOA
#define DEV_KEY_BRT_N_PORT  GPIOA
#define DEV_KEY_BRT_N_PIN   GPIO_PIN_7
#define DEV_KEY_BRT_N_EXIT  EXTI_7
#define DEV_KEY_BRT_N_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_BRT_N_EXIT_PIN      GPIO_PIN_SOURCE_7
#define DEV_KEY_BRT_N_NVIC          EXTI5_9_IRQn
//#define key_brt_n_irq  EXTI5_9_IRQHandler
#define key_brt_irq     EXTI5_9_IRQHandler

#define DEV_KEY_VOL_P_RCU   RCU_GPIOB
#define DEV_KEY_VOL_P_PORT  GPIOB
#define DEV_KEY_VOL_P_PIN   GPIO_PIN_0
#define DEV_KEY_VOL_P_EXIT  EXTI_0
#define DEV_KEY_VOL_P_EXIT_SOURCE    GPIO_PORT_SOURCE_GPIOB
#define DEV_KEY_VOL_P_EXIT_PIN       GPIO_PIN_SOURCE_0
#define DEV_KEY_VOL_P_NVIC           EXTI0_IRQn
#define key_vol_p_irq  EXTI0_IRQHandler

#define DEV_KEY_VOL_N_RCU   RCU_GPIOB
#define DEV_KEY_VOL_N_PORT  GPIOB
#define DEV_KEY_VOL_N_PIN   GPIO_PIN_1
#define DEV_KEY_VOL_N_EXIT  EXTI_1
#define DEV_KEY_VOL_N_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOB
#define DEV_KEY_VOL_N_EXIT_PIN      GPIO_PIN_SOURCE_1
#define DEV_KEY_VOL_N_NVIC          EXTI1_IRQn
#define key_vol_n_irq  EXTI1_IRQHandler


//3d switch 
#define DEV_3D_SW_RCU  RCU_GPIOA
#define DEV_3D_SW_PORT  GPIOA
#define DEV_3D_SW_PIN  GPIO_PIN_8


//audio switch 
#define DEV_AUDIO_RST_RCU   RCU_GPIOA
#define DEV_AUDIO_RST_PORT  GPIOA
#define DEV_AUDIO_RST_PIN   GPIO_PIN_5








//7211 reset
#define LT77XX_RST_RCU          RCU_GPIOA
#define LT77XX_RST_PIN          GPIO_PIN_15
#define LT77XX_RST_PORT         GPIOA






#if (GLASSES_BOARD==0)
//7211 gpio5 �����Ƶ�ź�
#define LT77XX_GPIO5_RCU          RCU_GPIOB
#define LT77XX_GPIO5_PIN          GPIO_PIN_3
#define LT77XX_GPIO5_PORT         GPIOB
#define LT77XX_GPIO5_EXIT         EXTI_3
#define LT77XX_GPIO5_EXIT_SOURCE  GPIO_PORT_SOURCE_GPIOB
#define LT77XX_GPIO5_EXIT_PIN     GPIO_PIN_SOURCE_3
#define LT77XX_GPIO5_NVIC         EXTI3_IRQn
#define lt77xx_gpio5_irq  EXTI3_IRQHandler


//pannel reset
#define PANEL_RSTN_RCU          RCU_GPIOB
#define PANEL_RSTN_PIN          GPIO_PIN_4
#define PANEL_RSTN_PORT         GPIOB


#else
//7211 gpio5 �����Ƶ�ź�
#define LT77XX_GPIO5_RCU          RCU_GPIOA
#define LT77XX_GPIO5_PIN          GPIO_PIN_3
#define LT77XX_GPIO5_PORT         GPIOA
#define LT77XX_GPIO5_EXIT         EXTI_3
#define LT77XX_GPIO5_EXIT_SOURCE  GPIO_PORT_SOURCE_GPIOA
#define LT77XX_GPIO5_EXIT_PIN     GPIO_PIN_SOURCE_3
#define LT77XX_GPIO5_NVIC         EXTI3_IRQn
#define lt77xx_gpio5_irq  EXTI3_IRQHandler




//pannel reset
#define PANEL_RSTN_RCU          RCU_GPIOB
#define PANEL_RSTN_PIN          GPIO_PIN_3
#define PANEL_RSTN_PORT         GPIOB

#endif

#elif MICRO_7911UXC


/*I2C����*/
#define DEV_PRIMARY_I2C                          I2C0
#define DEV_PRIMARY_I2C_RCU                      RCU_I2C0

#define DEV_PRIMARY_I2C_SCL_PIN                  GPIO_PIN_6                 
#define DEV_PRIMARY_I2C_SCL_GPIO_PORT            GPIOB                      
#define DEV_PRIMARY_I2C_SCL_GPIO_RCU             RCU_GPIOB

#define DEV_PRIMARY_I2C_SDA_PIN                  GPIO_PIN_7                  
#define DEV_PRIMARY_I2C_SDA_GPIO_PORT            GPIOB                    
#define DEV_PRIMARY_I2C_SDA_GPIO_RCU             RCU_GPIOB

#define TCA9548_RESET_BIT 									GPIO_PIN_8
#define TCA9548_RESET_BIT_PORT            	GPIOB  
#define TCA9548_RESET_BIT_RCU             	RCU_GPIOB
/*I2C����*/
#define DEV_SECONDARY_I2C                          I2C1
#define DEV_SECONDARY_I2C_RCU                      RCU_I2C1

#define DEV_SECONDARY_I2C_SCL_PIN                  GPIO_PIN_10                 
#define DEV_SECONDARY_I2C_SCL_GPIO_PORT            GPIOB                      
#define DEV_SECONDARY_I2C_SCL_GPIO_RCU             RCU_GPIOB

#define DEV_SECONDARY_I2C_SDA_PIN                  GPIO_PIN_11                  
#define DEV_SECONDARY_I2C_SDA_GPIO_PORT            GPIOB                    
#define DEV_SECONDARY_I2C_SDA_GPIO_RCU             RCU_GPIOB

//aw37501 ��Դ����  enable
#define DEV_ENP_GPIO_RCU   RCU_GPIOB
#define DEV_ENP_GPIO_PORT  GPIOB
#define DEV_ENP_GPIO_PIN   GPIO_PIN_7

#define DEV_ENN_GPIO_RCU   RCU_GPIOB
#define DEV_ENN_GPIO_PORT  GPIOB
#define DEV_ENN_GPIO_PIN   GPIO_PIN_7

//key ����
#define DEV_KEY_BRT_P_RCU   RCU_GPIOA
#define DEV_KEY_BRT_P_PORT  GPIOA
#define DEV_KEY_BRT_P_PIN   GPIO_PIN_2
#define DEV_KEY_BRT_P_EXIT  EXTI_2
#define DEV_KEY_BRT_P_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_BRT_P_EXIT_PIN      GPIO_PIN_SOURCE_2
#define DEV_KEY_BRT_P_NVIC          EXTI2_IRQn
#define key_brt_p_irq  EXTI2_IRQHandler

#define DEV_KEY_BRT_N_RCU   RCU_GPIOA
#define DEV_KEY_BRT_N_PORT  GPIOA
#define DEV_KEY_BRT_N_PIN   GPIO_PIN_1
#define DEV_KEY_BRT_N_EXIT  EXTI_1
#define DEV_KEY_BRT_N_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_BRT_N_EXIT_PIN      GPIO_PIN_SOURCE_1
#define DEV_KEY_BRT_N_NVIC          EXTI1_IRQn
#define key_brt_n_irq  EXTI1_IRQHandler
//#define key_brt_irq     EXTI5_9_IRQHandler

#define DEV_KEY_VOL_P_RCU   RCU_GPIOA
#define DEV_KEY_VOL_P_PORT  GPIOA
#define DEV_KEY_VOL_P_PIN   GPIO_PIN_3
#define DEV_KEY_VOL_P_EXIT  EXTI_3
#define DEV_KEY_VOL_P_EXIT_SOURCE    GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_VOL_P_EXIT_PIN       GPIO_PIN_SOURCE_3
#define DEV_KEY_VOL_P_NVIC           EXTI3_IRQn
#define key_vol_p_irq  EXTI3_IRQHandler

#define DEV_KEY_VOL_N_RCU   RCU_GPIOA
#define DEV_KEY_VOL_N_PORT  GPIOA
#define DEV_KEY_VOL_N_PIN   GPIO_PIN_4
#define DEV_KEY_VOL_N_EXIT  EXTI_4
#define DEV_KEY_VOL_N_EXIT_SOURCE   GPIO_PORT_SOURCE_GPIOA
#define DEV_KEY_VOL_N_EXIT_PIN      GPIO_PIN_SOURCE_4
#define DEV_KEY_VOL_N_NVIC          EXTI4_IRQn
#define key_vol_n_irq  EXTI4_IRQHandler

//7211 gpio5 �����Ƶ�ź�
#define LT77XX_GPIO5_RCU          RCU_GPIOA
#define LT77XX_GPIO5_PIN          GPIO_PIN_6
#define LT77XX_GPIO5_PORT         GPIOA

#define LT77XX_GPIO5_EXIT         EXTI_6
#define LT77XX_GPIO5_EXIT_SOURCE  GPIO_PORT_SOURCE_GPIOA
#define LT77XX_GPIO5_EXIT_PIN     GPIO_PIN_SOURCE_6
#define LT77XX_GPIO5_NVIC         EXTI5_9_IRQn
#define lt77xx_gpio5_irq  EXTI5_9_IRQHandler

//3d switch 
#define DEV_3D_SW_RCU  RCU_GPIOA
#define DEV_3D_SW_PORT  GPIOA
#define DEV_3D_SW_PIN  GPIO_PIN_7

//audio switch 
#define DEV_AUDIO_RST_RCU   RCU_GPIOB
#define DEV_AUDIO_RST_PORT  GPIOB
#define DEV_AUDIO_RST_PIN   GPIO_PIN_3

//7211 reset
#define LT77XX_RST_RCU          RCU_GPIOB
#define LT77XX_RST_PIN          GPIO_PIN_1
#define LT77XX_RST_PORT         GPIOB

//pannel reset
#define PANEL_RSTN_RCU          RCU_GPIOB
#define PANEL_RSTN_PIN          GPIO_PIN_2
#define PANEL_RSTN_PORT         GPIOB

//LT7911 
#define LT7911_RST 0x10			// RST = 7211 reset
#define LT7911_GPIO_14 0x20 // GPIO_14 = 3d switch 
#define LT7911_GPIO_16 0x40 // GPIO_16 = pannel reset

#endif

#endif

