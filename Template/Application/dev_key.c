#include "gd32f30x.h"
#include "dev_key.h"
#include "gd32_aw882xx.h"
#include "pannel.h"
#include "TCA9548.h"
#define u32 unsigned int
typedef enum 
{
    E_2D,
    E_3D,
}e_2d3d_para;
#define DEFAULT_D  E_2D

void Dev_3Dkey_init(void)
{
    rcu_periph_clock_enable(DEV_3D_SW_RCU);
    
    gpio_init(DEV_3D_SW_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, DEV_3D_SW_PIN); 
}

void dev_3d_switch(e_2d3d_para value)
{
    if(value)
        gpio_bit_set(DEV_3D_SW_PORT,DEV_3D_SW_PIN);
    else
        gpio_bit_reset(DEV_3D_SW_PORT,DEV_3D_SW_PIN);
}
//void dev_2d3d_switch()
//{
//    static unsigned char curd = DEFAULT_D;
//    if(curd==E_2D) {
//        curd = E_3D;
//        printf("switch 3d\n");
//    }
//    else if(curd==E_3D) 
//    {
//        curd = E_2D;
//        printf("switch 2d\n");
//    }

//    dev_3d_switch(curd);
//}

// solution to noise when switch 2d/3d
void dev_2d3d_switch()
{
	
//	  AW_ENN_0();
//	  delay_1ms(10);
//		AW_ENP_0();
//	
//    static unsigned char curd = DEFAULT_D;
//    if(curd==E_2D) {
//        curd = E_3D;
//        printf("switch 3d\n");
//    }
//    else if(curd==E_3D) 
//    {
//        curd = E_2D;
//        printf("switch 2d\n");
//    }

//    dev_3d_switch(curd);
//	 delay_1ms(1000);
//		AW_ENP_1();
//    delay_1ms(10);
//    AW_ENN_1();
//		
//	 pannel_init();  
//		
	

		AW_ENN_0();		
	  delay_1ms(10);
		AW_ENP_0(); 
    static unsigned char curd = DEFAULT_D;
    if(curd==E_2D) {
        curd = E_3D;
        printf("switch 3d\n");
    }
    else if(curd==E_3D) 
    {
        curd = E_2D;
        printf("switch 2d\n");
    }

    dev_3d_switch(curd);

	
    delay_1ms(2500);
//	  aw37501_pin_init();		
//    set_voutp_value(5.5);
//    set_voutn_value(4.5);
//    set_apps_value(3);	

		AW_ENP_1();	
	   delay_1ms(10);	
	  AW_ENN_1(); 
		
	//	pannel_init();  		
		 gd32_aw882xx();














}















void Dev_key_init(void)
{
#if 1
     /* enable the key clock */
    rcu_periph_clock_enable(DEV_KEY_BRT_P_RCU);
    rcu_periph_clock_enable(DEV_KEY_BRT_N_RCU);
    rcu_periph_clock_enable(DEV_KEY_VOL_P_RCU);
    rcu_periph_clock_enable(DEV_KEY_VOL_N_RCU);
    
    rcu_periph_clock_enable(RCU_AF);
    //nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);


    /* configure button pin as input */
    gpio_init(DEV_KEY_BRT_P_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,DEV_KEY_BRT_P_PIN);
    /* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(DEV_KEY_BRT_P_NVIC, 2U, 0U);
    /* connect key EXTI line to key GPIO pin */
    gpio_exti_source_select(DEV_KEY_BRT_P_EXIT_SOURCE,DEV_KEY_BRT_P_EXIT_PIN);
    /* configure key EXTI line */
    exti_init(DEV_KEY_BRT_P_EXIT, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(DEV_KEY_BRT_P_EXIT);
 
    gpio_init(DEV_KEY_BRT_N_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,DEV_KEY_BRT_N_PIN);
    nvic_irq_enable(DEV_KEY_BRT_N_NVIC, 2U, 0U);
    gpio_exti_source_select(DEV_KEY_BRT_N_EXIT_SOURCE,DEV_KEY_BRT_N_EXIT_PIN);
    exti_init(DEV_KEY_BRT_N_EXIT, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(DEV_KEY_BRT_N_EXIT);


    gpio_init(DEV_KEY_VOL_P_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,DEV_KEY_VOL_P_PIN);
    nvic_irq_enable(DEV_KEY_VOL_P_NVIC, 2U, 1U);
    gpio_exti_source_select(DEV_KEY_VOL_P_EXIT_SOURCE,DEV_KEY_VOL_P_EXIT_PIN);
    exti_init(DEV_KEY_VOL_P_EXIT, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(DEV_KEY_VOL_P_EXIT);


    gpio_init(DEV_KEY_VOL_N_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,DEV_KEY_VOL_N_PIN);
    nvic_irq_enable(DEV_KEY_VOL_N_NVIC, 2U, 2U);
    gpio_exti_source_select(DEV_KEY_VOL_N_EXIT_SOURCE,DEV_KEY_VOL_N_EXIT_PIN);
    exti_init(DEV_KEY_VOL_N_EXIT, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(DEV_KEY_VOL_N_EXIT);

    gpio_init(LT77XX_GPIO5_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ,LT77XX_GPIO5_PIN);
    nvic_irq_enable(LT77XX_GPIO5_NVIC, 2U, 3U);
    gpio_exti_source_select(LT77XX_GPIO5_EXIT_SOURCE,LT77XX_GPIO5_EXIT_PIN);
    exti_init(LT77XX_GPIO5_EXIT, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(LT77XX_GPIO5_EXIT);
#endif
    Dev_3Dkey_init();
    dev_3d_switch(DEFAULT_D);
}

unsigned char key_vol_p = 0;
unsigned char key_vol_n = 0;
unsigned char key_brt_p = 0;
unsigned char key_brt_n = 0;
u32 lkey_brt_n_time = 0;
void key_vol_p_irq(void)  
{
    if(RESET != exti_interrupt_flag_get(DEV_KEY_VOL_P_EXIT)){
        printf("key_vol_p_irq\n");
        key_vol_p=1;
        exti_interrupt_flag_clear(DEV_KEY_VOL_P_EXIT);
    }
}
void key_vol_n_irq(void)
{
    if(RESET != exti_interrupt_flag_get(DEV_KEY_VOL_N_EXIT)){
        printf("key_vol_n_irq\n");
        key_vol_n=1;
        
        exti_interrupt_flag_clear(DEV_KEY_VOL_N_EXIT);
    }
}
void lt77xx_gpio5_irq(void)
{
    if(RESET != exti_interrupt_flag_get(LT77XX_GPIO5_EXIT)){
        printf("lt77xx_gpio5_irq\n");
        i2s_inter_flag ++ ;
        exti_interrupt_flag_clear(LT77XX_GPIO5_EXIT);
    }
}
#if MICRO_TD
void key_brt_irq(void)
{
    if(RESET != exti_interrupt_flag_get(DEV_KEY_BRT_P_EXIT)){
        printf("key_brt_p irq\n");
        key_brt_p = 1;
        exti_interrupt_flag_clear(DEV_KEY_BRT_P_EXIT);
    }
    else if(RESET != exti_interrupt_flag_get(DEV_KEY_BRT_N_EXIT)){
        printf("key_brt_n irq\n");
        key_brt_n = 1;
        if(lkey_brt_n_time==0)
            lkey_brt_n_time = 1;
        exti_interrupt_flag_clear(DEV_KEY_BRT_N_EXIT);
    }
}
#elif  MICRO_7911UXC
void key_brt_p_irq(void)
{
    if(RESET != exti_interrupt_flag_get(DEV_KEY_BRT_P_EXIT)){
        printf("key_brt_p irq\n");
        key_brt_p = 1;
        exti_interrupt_flag_clear(DEV_KEY_BRT_P_EXIT);
    }
}
void key_brt_n_irq(void)
{
    if(RESET != exti_interrupt_flag_get(DEV_KEY_BRT_N_EXIT)){
        printf("key_brt_n irq\n");
        key_brt_n = 1;
        if(lkey_brt_n_time==0)
            lkey_brt_n_time = 1;
        exti_interrupt_flag_clear(DEV_KEY_BRT_N_EXIT);
    }
}
#endif

void key_scan(void)
{
    if(key_vol_p){
        delay_1ms(50);
        if(VOL_P_READ()==0){
            gd_volume_add();
        }
        key_vol_p = 0;
        
    }
    if(key_vol_n){
        delay_1ms(50);
        if(VOL_N_READ()==0){
            gd_volume_sub();
        }
        key_vol_n = 0;
    }
    if(key_brt_p){
        delay_1ms(50);
        if(BRT_P_READ()==0){
#if GLASSES_BOARD
            pannel_bright_add(E_PANNEL_0);
            pannel_bright_add(E_PANNEL_1);
#else
            pannel_bright_add(E_PANNEL_103);
#endif
        }
        key_brt_p=0;
    }
    if(key_brt_n){
        delay_1ms(50);
        if(BRT_N_READ()==0){
#if GLASSES_BOARD
            pannel_bright_sub(E_PANNEL_0);
            pannel_bright_sub(E_PANNEL_1);
#else
            pannel_bright_sub(E_PANNEL_103);
#endif
        }
        key_brt_n=0;
    }
    if(lkey_brt_n_time)
    {
        if(BRT_N_READ()==0){
            lkey_brt_n_time++;
            printf("lkey_brt_n_time=%d\n",lkey_brt_n_time);
            if(lkey_brt_n_time>=500)
            {
                dev_2d3d_switch();
                lkey_brt_n_time=0;
            }
        }
        else{
            lkey_brt_n_time = 0;
        } 
    }
    if(i2s_inter_flag>=2)
    {
        gd32_aw882xx();
        i2s_inter_flag = 0;
    }

    
}



































