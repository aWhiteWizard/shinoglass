#ifndef _PCA9544_H_
#define _PCA9544_H_



#include "dev_conf.h"

#define PCA9544_IIC_BUS 0
#define PCA9544_MAX_DEV_COUNT 4


typedef enum PCA9544Channel
{
	PCA9544_CHANNEL_0,
	PCA9544_CHANNEL_1,
	PCA9544_CHANNEL_2,
	PCA9544_CHANNEL_3,
	PCA9544_CHANNEL_DISABLED,
	PCA9544_test 
}PCA9544Channel;


int pca9544_i2c_set(enum PCA9544Channel channel);
int pca9544_i2c_init(void);




















#endif

