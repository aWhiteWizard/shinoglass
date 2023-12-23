#ifndef _DEV_KEY_H_
#define _DEV_KEY_H_


void Dev_key_init(void);

#include "dev_conf.h"

#define BRT_P_READ()   gpio_input_bit_get(DEV_KEY_BRT_P_PORT, DEV_KEY_BRT_P_PIN)	  
#define BRT_N_READ()   gpio_input_bit_get(DEV_KEY_BRT_N_PORT, DEV_KEY_BRT_N_PIN)	  
#define VOL_P_READ()   gpio_input_bit_get(DEV_KEY_VOL_P_PORT, DEV_KEY_VOL_P_PIN)	  
#define VOL_N_READ()   gpio_input_bit_get(DEV_KEY_VOL_N_PORT, DEV_KEY_VOL_N_PIN)	


void key_scan(void);

   







#endif

