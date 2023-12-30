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
		gpio_init(KEY_UP_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY_UP_PIN); 

		rcu_periph_clock_enable(KEY_DOWN_GPIO_RCU);
		gpio_init(KEY_DOWN_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY_DOWN_PIN); 

		rcu_periph_clock_enable(KEY_LEFT_GPIO_RCU);
		gpio_init(KEY_LEFT_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY_LEFT_PIN); 

		rcu_periph_clock_enable(KEY_RIGNT_GPIO_RCU);
		gpio_init(KEY_RIGNT_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY_RIGNT_PIN); 

		rcu_periph_clock_enable(KEY_CENTER_GPIO_RCU);
		gpio_init(KEY_CENTER_GPIO_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, KEY_CENTER_PIN); 
}


/*!
    \brief      this function handles external lines 1 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI1_IRQHandler(void)
{
    //�ж��Ƿ����ⲿ�ж���1
    if (RESET != exti_interrupt_flag_get(EXTI_1)) 
    {
        //�ڴ˼����Լ��Ŀ��ƣ�һ��Ϊ�ñ�־�ȶ��ݷ���������

        //����жϱ��
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
    //�ж��Ƿ����ⲿ�ж���1
    if (RESET != exti_interrupt_flag_get(EXTI_2)) 
    {
        //�ڴ˼����Լ��Ŀ��ƣ�һ��Ϊ�ñ�־�ȶ��ݷ���������

        //����жϱ��
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
    //�ж��Ƿ����ⲿ�ж���1
    if (RESET != exti_interrupt_flag_get(EXTI_3)) 
    {
        //�ڴ˼����Լ��Ŀ��ƣ�һ��Ϊ�ñ�־�ȶ��ݷ���������

        //����жϱ��
        exti_interrupt_flag_clear(EXTI_3);
    }
}
