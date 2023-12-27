#include "dev_key_led.h"

uint8_t Key_GPIO_Read(uint8_t keyNum)
{
    uint8_t value = 0;
		switch (keyNum)
		{	
			case 0: value = gpio_input_bit_get(KEY_UP_GPIO_PORT, KEY_UP_PIN); break;
			case 1: value = gpio_input_bit_get(KEY_DOWN_GPIO_PORT, KEY_DOWN_PIN); break;
			case 2: value = gpio_input_bit_get(KEY_LEFT_GPIO_PORT, KEY_LEFT_PIN); break;
			case 3: value = gpio_input_bit_get(KEY_RIGNT_GPIO_PORT, KEY_RIGNT_PIN); break;
			case 4: value = gpio_input_bit_get(KEY_CENTER_GPIO_PORT, KEY_CENTER_PIN); break;
			default : value = 2;
		}
    return value;
}

void Key_Init(void)
{
		rcu_periph_clock_enable(KEY_UP_GPIO_RCU);
		gpio_init(KEY_UP_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_UP_PIN); 

		rcu_periph_clock_enable(KEY_DOWN_GPIO_RCU);
		gpio_init(KEY_DOWN_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_DOWN_PIN); 

		rcu_periph_clock_enable(KEY_LEFT_GPIO_RCU);
		gpio_init(KEY_LEFT_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_LEFT_PIN); 

		rcu_periph_clock_enable(KEY_RIGNT_GPIO_RCU);
		gpio_init(KEY_RIGNT_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_RIGNT_PIN); 

		rcu_periph_clock_enable(KEY_CENTER_GPIO_RCU);
		gpio_init(KEY_CENTER_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, KEY_CENTER_PIN); 
	
		//使能复用功能时钟
		rcu_periph_clock_enable(RCU_AF);
		//设置优先级分组
		nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
		//设置优先级
		nvic_irq_enable(EXTI0_IRQn, 2U, 2U);
		//KEY_UP_PIN
		//设置EXTI触发源
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_12);
		//下降沿中断
		exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		//清中断标志
		exti_interrupt_flag_clear(EXTI_0);
		
		//KEY_DOWN_PIN
				//设置优先级
		nvic_irq_enable(EXTI1_IRQn, 2U, 2U);
		//设置EXTI触发源
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_13);
		//下降沿中断
		exti_init(EXTI_1, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		//清中断标志
		exti_interrupt_flag_clear(EXTI_1);
		
		//KEY_LEFT_PIN
				//设置优先级
		nvic_irq_enable(EXTI2_IRQn, 2U, 2U);
		//设置EXTI触发源
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_14);
		//下降沿中断
		exti_init(EXTI_2, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		//清中断标志
		exti_interrupt_flag_clear(EXTI_2);
		
		//KEY_RIGNT_PIN
				//设置优先级
		nvic_irq_enable(EXTI3_IRQn, 2U, 2U);
		//设置EXTI触发源
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOB, GPIO_PIN_SOURCE_15);
		//下降沿中断
		exti_init(EXTI_3, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		//清中断标志
		exti_interrupt_flag_clear(EXTI_3);
		
		//KEY_CENTER_PIN
				//设置优先级
		nvic_irq_enable(EXTI4_IRQn, 2U, 2U);

		//设置EXTI触发源
		gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOC, GPIO_PIN_SOURCE_13);
		//下降沿中断
		exti_init(EXTI_4, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
		//清中断标志
		exti_interrupt_flag_clear(EXTI_4);
}

/*!
    \brief      this function handles external lines 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI0_IRQHandler(void)
{
    //判定是否是外部中断线1
    if (RESET != exti_interrupt_flag_get(EXTI_0)) 
    {
        //在此加入自己的控制，一般为置标志等短暂非阻塞操作
				earphone_volume++;
				if(earphone_volume > 100)
					earphone_volume = 100;
        //清除中断标记
        exti_interrupt_flag_clear(EXTI_0);
    }
}
/*!
    \brief      this function handles external lines 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI1_IRQHandler(void)
{
    //判定是否是外部中断线1
    if (RESET != exti_interrupt_flag_get(EXTI_1)) 
    {
        //在此加入自己的控制，一般为置标志等短暂非阻塞操作
				earphone_volume--;
				if(earphone_volume < 0)
					earphone_volume = 0;
        //清除中断标记
        exti_interrupt_flag_clear(EXTI_1);
    }
}

/*!
    \brief      this function handles external lines 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI2_IRQHandler(void)
{
    //判定是否是外部中断线1
    if (RESET != exti_interrupt_flag_get(EXTI_2)) 
    {
        //在此加入自己的控制，一般为置标志等短暂非阻塞操作
				oled_bright--;
				if(oled_bright < 0)
					oled_bright = 0;
        //清除中断标记
        exti_interrupt_flag_clear(EXTI_2);
    }
}

/*!
    \brief      this function handles external lines 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI3_IRQHandler(void)
{
    //判定是否是外部中断线1
    if (RESET != exti_interrupt_flag_get(EXTI_3)) 
    {
        //在此加入自己的控制，一般为置标志等短暂非阻塞操作
				oled_bright++;
				if(oled_bright > 100)
					oled_bright = 100;
        //清除中断标记
        exti_interrupt_flag_clear(EXTI_3);
    }
}
