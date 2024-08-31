
#include	"STC15W4K60S4.H"
#include "intrins.h"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"
#include "driver.h"
#include "arch.h"
#include "main.h"

#include "led.h"

/******************************************************************************/
#if	0
void portIdle(void){}
/******************************************************************************
 * PWM_ON/PWM_OFF
 ******************************************************************************/
void	ledpwm1_off(void){LED_PWM1_CRL = PWM_OFF;}
void	ledpwm2_off(void){LED_PWM2_CRL = PWM_OFF;}
void	ledpwm3_off(void){LED_PWM3_CRL = PWM_OFF;}
void	ledpwm4_off(void){LED_PWM4_CRL = PWM_OFF;}
void	ledpwm5_off(void){LED_PWM5_CRL = PWM_OFF;}
void	ledpwm6_off(void){LED_PWM6_CRL = PWM_OFF;}
void	ledpwm7_off(void){LED_PWM7_CRL = PWM_OFF;}

code paction_t_0 g_ledpwmArray_off[] = {
	portIdle,
	ledpwm1_off,
	ledpwm2_off,
	ledpwm3_off,
	ledpwm4_off,
	ledpwm5_off,
	ledpwm6_off,
	ledpwm7_off,
};
#endif

#if	0
void	ledpwm1_on(void){LED_PWM1_CRL = PWM_ON;}
void	ledpwm2_on(void){LED_PWM2_CRL = PWM_ON;}
void	ledpwm3_on(void){LED_PWM3_CRL = PWM_ON;}
void	ledpwm4_on(void){LED_PWM4_CRL = PWM_ON;}
void	ledpwm5_on(void){LED_PWM5_CRL = PWM_ON;}
void	ledpwm6_on(void){LED_PWM6_CRL = PWM_ON;}
void	ledpwm7_on(void){LED_PWM7_CRL = PWM_ON;}

code paction_t_0 g_ledpwmArray_on[] = {
	portIdle,
	ledpwm1_on,
	ledpwm2_on,
	ledpwm3_on,
	ledpwm4_on,
	ledpwm5_on,
	ledpwm6_on,
	ledpwm7_on,
};
#endif

#if	0
//void	ledpwm1_toggle(void){LED_PWM1_CRL = !LED_PWM1_CRL;}
void	ledpwm1_toggle(void){LED_PWM1_CRL ^= 1;}
void	ledpwm2_toggle(void){LED_PWM2_CRL ^= 1;}
void	ledpwm3_toggle(void){LED_PWM3_CRL ^= 1;}
void	ledpwm4_toggle(void){LED_PWM4_CRL ^= 1;}
void	ledpwm5_toggle(void){LED_PWM5_CRL ^= 1;}
void	ledpwm6_toggle(void){LED_PWM6_CRL ^= 1;}
void	ledpwm7_toggle(void){LED_PWM7_CRL ^= 1;}

code paction_t_0 g_ledpwmArray_toggle[] = {
	portIdle,
	ledpwm1_toggle,
	ledpwm2_toggle,
	ledpwm3_toggle,
	ledpwm4_toggle,
	ledpwm5_toggle,
	ledpwm6_toggle,
	ledpwm7_toggle,
};
#endif

/*** for shape control *******************************************************/
//#if	1
void	ledport1_L(void){LED_P1_CRL = 0;}
void	ledport2_L(void){LED_P2_CRL = 0;}
void	ledport3_L(void){LED_P3_CRL = 0;}
void	ledport4_L(void){LED_P4_CRL = 0;}
void	ledport5_L(void){LED_P5_CRL = 0;}
void	ledport6_L(void){LED_P6_CRL = 0;}
void	ledportR_L(void){LED_R_CRL = 0;}
void	ledportG_L(void){LED_G_CRL = 0;}
void	ledportB_L(void){LED_B_CRL = 0;}


code paction_t_0 g_ledportArray_L[] = {
	/** 嘴巴 **/
	ledport1_L,
	ledport2_L,
	ledport3_L,
	/** 眼睛 **/
	ledport4_L,
	ledport5_L,
	ledport6_L,
	/** 耳朵 **/
	ledportR_L,
	ledportG_L,
	ledportB_L,
};

void	ledport1_H(void){LED_P1_CRL = 1;}
void	ledport2_H(void){LED_P2_CRL = 1;}
void	ledport3_H(void){LED_P3_CRL = 1;}
void	ledport4_H(void){LED_P4_CRL = 1;}
void	ledport5_H(void){LED_P5_CRL = 1;}
void	ledport6_H(void){LED_P6_CRL = 1;}
void	ledportR_H(void){LED_R_CRL = 1;}
void	ledportG_H(void){LED_G_CRL = 1;}
void	ledportB_H(void){LED_B_CRL = 1;}

code paction_t_0 g_ledportArray_H[] = {
	/** 嘴巴 **/
	ledport1_H,
	ledport2_H,
	ledport3_H,
	/** 眼睛 **/
	ledport4_H,
	ledport5_H,
	ledport6_H,
	/** 耳朵 **/
	ledportR_H,
	ledportG_H,
	ledportB_H,
};

#if	0
void	ledport1_L_irq(void){EA = 0; LED_P1_CRL = 0; EA = 1;}
void	ledport2_L_irq(void){EA = 0; LED_P2_CRL = 0; EA = 1;}
void	ledport3_L_irq(void){EA = 0; LED_P3_CRL = 0; EA = 1;}
void	ledport4_L_irq(void){EA = 0; LED_P4_CRL = 0; EA = 1;}
void	ledport5_L_irq(void){EA = 0; LED_P5_CRL = 0; EA = 1;}
void	ledport6_L_irq(void){EA = 0; LED_P6_CRL = 0; EA = 1;}
void	ledportR_L_irq(void){EA = 0; LED_R_CRL = 0; EA = 1;}
void	ledportG_L_irq(void){EA = 0; LED_G_CRL = 0; EA = 1;}
void	ledportB_L_irq(void){EA = 0; LED_B_CRL = 0; EA = 1;}

code paction_t_0 g_ledportArray_L_irq[] = {
	/** 嘴巴 **/
	ledport1_L_irq,
	ledport2_L_irq,
	ledport3_L_irq,
	/** 眼睛 **/
	ledport4_L_irq,
	ledport5_L_irq,
	ledport6_L_irq,
	/** 耳朵 **/
	ledportR_L_irq,
	ledportG_L_irq,
	ledportB_L_irq,
};
#endif

#if	0
void	ledport1_H_irq(void){EA = 0; LED_P1_CRL = 1; EA = 1;}
void	ledport2_H_irq(void){EA = 0; LED_P2_CRL = 1; EA = 1;}
void	ledport3_H_irq(void){EA = 0; LED_P3_CRL = 1; EA = 1;}
void	ledport4_H_irq(void){EA = 0; LED_P4_CRL = 1; EA = 1;}
void	ledport5_H_irq(void){EA = 0; LED_P5_CRL = 1; EA = 1;}
void	ledport6_H_irq(void){EA = 0; LED_P6_CRL = 1; EA = 1;}
void	ledportR_H_irq(void){EA = 0; LED_R_CRL = 1; EA = 1;}
void	ledportG_H_irq(void){EA = 0; LED_G_CRL = 1; EA = 1;}
void	ledportB_H_irq(void){EA = 0; LED_B_CRL = 1; EA = 1;}

code paction_t_0 g_ledportArray_H_irq[] = {
	/** 嘴巴 **/
	ledport1_H_irq,
	ledport2_H_irq,
	ledport3_H_irq,
	/** 眼睛 **/
	ledport4_H_irq,
	ledport5_H_irq,
	ledport6_H_irq,
	/** 耳朵 **/
	ledportR_H_irq,
	ledportG_H_irq,
	ledportB_H_irq,
};
#endif

//#endif


/*******************************************************************************
 * 
 * 设置pwm输出状态:
 * order: specified pwm NO.
 * value: 
 *  0 - none
 *  1 - 渐亮(脉宽变宽)
 *  2 - 渐暗(脉宽变窄)
    3 - 保持(脉宽不变)
 *  4 - 常亮(高电平)
 *  5 - 常灭(低电平)
 *	6 - 未定义
 * 
 *******************************************************************************/
#if	0
void pwdTmr_set(u8 order, u8 value)
{
	#if	1
	if(order == 1) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM1_CRL = PWM_ON;
			#else 
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM1_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}
	} else if(order == 2) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM2_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM2_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}
	} else if(order == 3) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM3_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM3_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}
		
	} else if(order == 4) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM4_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM4_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}	
	} else if(order == 5) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM5_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM5_CRL = PWM_OFF;;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}
	
	} else if(order == 6) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM6_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
			
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM6_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
			
		} else {
			g_pwm.buf[order].stat = value;
		}
	} else if(order == 7) {
		if(value == 4) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM7_CRL = PWM_ON;
			#else
				g_ledpwmArray_on[order]();
			#endif
		} else if(value == 5) {
			g_pwm.buf[order].stat = 0;
			#if	1
				LED_PWM7_CRL = PWM_OFF;
			#else
				g_ledpwmArray_off[order]();
			#endif
		} else {
			g_pwm.buf[order].stat = value;
		}

	} else {
		/** nothing **/
	}
	
	#endif
}
#endif
/******************************************************************************
 *
 * 设置指定输出脚的脉冲宽度(表现为各种颜色的亮度). 只在状态5用得上
 * 
 ******************************************************************************/
#if	0	//---用MPWMTMR_SETWIDE(x, y)宏代替
void pwdTmr_setWide(u8 order, u8 value)
{
    if((order < 8) && (order >= 1)) {
		if(value <= PWM_DUTY_MAX) {
			g_pwm.buf[order].step = value;
		}
    }
}
#endif
/*******************************************************************************
 * 
 * ledport_setTmr
 * input: __order
 * 		: __H
 *		: __L
 * output: none
 * return: none
 *******************************************************************************/
#if	0	//---用MLEDPORT_SETSTAT()宏代替
void ledport_setTmr(u8 __order, u8 __H, u8  __L)
{
	if(__order < 9) {
		EA = 0;
		g_ledport.buf[__order].wide_H = __H;
		g_ledport.buf[__order].wide_H_bak = __H;
		
		g_ledport.buf[__order].wide_L = __L;
		g_ledport.buf[__order].wide_L_bak = __L;
		EA = 1;
	}
}
#endif
/*******************************************************************************
 *
 * 控制ledport的状态(具体见ptype.h)
 *  0 - no nothing
 *  1 - high(led off)
 *  2 - low
 *  3 - high/low - low
 *  4 - high/low - high
 *  5 - 
 *******************************************************************************/
#if	0	//---用MLEDPORT_SETSTAT()宏代替
void ledport_setStat(u8 __order, u8 __stat)
{
	#if	1
	if(__order < 9) {
		EA = 0;
	    if(__stat == 1) {
	        g_ledport.buf[__order].stat = 0;
	        g_ledportArray_H[__order]();
	    } else if(__stat == 2) {   
	        g_ledport.buf[__order].stat = 0;
	        g_ledportArray_L[__order]();
	    } else if(__stat == 3) {
	        g_ledport.buf[__order].stat = 3;
	        g_ledportArray_L[__order]();		
	    } else if(__stat == 4) {       
	        g_ledport.buf[__order].stat = 4;
	        g_ledportArray_H[__order]();
	    } else {
	    	g_ledport.buf[__order].stat = (__stat & 0x0f);
	    }
		EA = 1;
	}
	#endif
}
#endif

