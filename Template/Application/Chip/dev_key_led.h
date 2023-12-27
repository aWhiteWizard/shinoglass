#ifndef __DEV_KEY_LED_H
#define __DEV_KEY_LED_H

#include "main.h"
#include "gd32f30x.h"
#include "dev_conf.h"

#define KEY_UP_PIN						GPIO_PIN_12
#define KEY_UP_GPIO_PORT			GPIOB
#define KEY_UP_GPIO_RCU				RCU_GPIOB

#define KEY_DOWN_PIN						GPIO_PIN_13
#define KEY_DOWN_GPIO_PORT			GPIOB
#define KEY_DOWN_GPIO_RCU				RCU_GPIOB

#define KEY_LEFT_PIN						GPIO_PIN_14
#define KEY_LEFT_GPIO_PORT			GPIOB
#define KEY_LEFT_GPIO_RCU				RCU_GPIOB

#define KEY_RIGNT_PIN						GPIO_PIN_15
#define KEY_RIGNT_GPIO_PORT			GPIOB
#define KEY_RIGNT_GPIO_RCU				RCU_GPIOB

#define KEY_CENTER_PIN						GPIO_PIN_13
#define KEY_CENTER_GPIO_PORT			GPIOC
#define KEY_CENTER_GPIO_RCU				RCU_GPIOC

static int earphone_volume=20;
static int earphone_volume_reg=0;
static int oled_bright=20;
static int oled_bright_reg=0;

void Key_Init(void);
uint8_t Key_GPIO_Read(uint8_t keyNum);
#endif