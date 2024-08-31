
//#include	<reg52.h>

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

void	actionDoNothing(void) {}
u8 comm[5];
//parameter_t	parameter;
/*******************************************************************************/
int sysProcess(msg_t *val)
{
	int iRet = TRUE;
//	u8 tmp;
//	static u8 P1_flag = 0;
//	msg_t msg;
	
	switch(val->msgType)
	{
		case CACT_TOUT:			/** 一个动作阶段完成 **/
			actProcess(&g_actionQueue);
			break;
		
		case CMSG_TMR:			/** tick **/
			g_tick++;
		
			//charQueueIn_irq(&g_charTxQueue, (g_tick & 0xff));
			break;
		
		case CMSG_UARX:			/** uart received data **/
			charQueueMove_irq(&g_charRxQueue, &g_charTmpQueue);	
		#if	0
			phrase_command(&g_charTmpQueue);
		#else
			//if(get_command(&g_charTmpQueue, &comm)) {
			if(get_command(&g_charTmpQueue, comm)) {
				//---Do command
		        switch(comm[0])
		        {
		        case CPROTOCAL_MOTOCOMM:		/** MOTO **/
		        	/** 51-2nd here do nothing **/
		            break;
		        
		        case CPROTOCAL_LEDCOMM:			/** LED **/
		        	/** do something here **/
		        	switch(comm[1])
		        	{
		        	case CPROTOCAL_LEDCOMM_TALK:		/** 说话(嘴巴白灯闪) **/
		        		//parameter.color = 5;
		        		//parameter.expired = 3;
		        		//parameter.shape = 5;
		        		//mouse(&parameter);
		        		break;
		        	
		        	case CPROTOCAL_LEDCOMM_BLINK:		/** 眨眼 **/
		        		//parameter.color = 5;
		        		//parameter.expired = 3;
		        		//parameter.shape = 6;
		        		//eye(&parameter);
		        	
		        		//parameter.shape = 2;
		        		//eye(&parameter);
		        	
		        		//parameter.shape = 6;
		        		//eye(&parameter);
		        			
		        		//parameter.shape = 7;
		        		//eye(&parameter);
		        		break;
		        	
		        	case CPROTOCAL_LEDCOMM_SHAKE:	/** 耳 **/
		        		//parameter.color = 5;
		        		//parameter.shape = 100;
		        		//parameter.expired = 3;
//		        		ear(&parameter);
		        				
		        		break;
		        	
		        	default:
		        		charQueueIn_irq(&g_charTxQueue, (comm[0]));
		        		charQueueIn_irq(&g_charTxQueue, (comm[1]));
		        		charQueueIn_irq(&g_charTxQueue, (comm[2]));
		        		/*** 0x03 0x21 0x70 ***/
		        		//P41 = !P41;
		        		//P42 = !P42;
		        	
		        		//parameter.color = (comm[1] & 0x1f);
		        		//parameter.shape = ((comm[2] >> 4) & 0x0f);
		        		//parameter.expired = (comm[2] & 0x0f);
					#if	1
						g_part_shape[(comm[1] >> 5) & 0x03][(comm[2] >> 4) & 0x0f]();
						g_part_color_expire[(comm[1] >> 5) & 0x03][comm[2] & 0x0f][comm[1] & 0xf]();
		        	#endif
		        		break;
		        	}
		        	break;
		        
		        case CPROTOCAL_IRCOMM:			/** uart received data **/
		        	/** do nothing **/
		        	break;
		        
		        case CPROTOCAL_SLEEPCOMM:			/** uart received data **/
		        	/** do nothing **/
		        	break;
		        
		        default:
		        	break;
		        }
				
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			
		#endif
			/** do something here **/
		
			break;
		
		default:
			/** Can't process the msg here **/
			iRet = FALSE;
		break;
	}
	
	return iRet;
}

/*******************************************************************************
 * value_inc()/value_dec()
 * 将指定的变量在[_max, _min]区间内加/减1. 
 *******************************************************************************/
#if	0
u8 value_inc(u8 _value, u8 _max, u8 _min)
{
	if(_value >= _max) {
		_value = _min;
	} else {
		_value += 1;
	}
	
	return	_value;
}

u8 value_dec(u8 _value, u8 _max, u8 _min)
{
	if(_value <= _min) {
		_value = _max;
	} else {
		_value -= 1;
	}
	
	return	_value;
}
#endif

 /******************************************************************************
  * function: get_command/phrase_command
  * Description: get received data from FIFO and phrase
  * input: src - pointer of FIFO
  * output: arr - the data get from FIFO
  * return: <= 12 the length of data get from FIFO
  * Get all of the data in the FIFO
  * 
  * make sure
  *******************************************************************************/
u8 get_command(charQueue_t *src, u8 *array)
{
	u8 i = 255;

	u8 head;
	u8 len;
	
	while(charQueueOut(src, &head) == TRUE) {
        if((head == 0x5a) && (i == 255)) {		/** 找到命令头(第一个0x5a) **/
    		i = 0;
            break;
        }
    }
	if(i == 0) {	//---如果找到了命令头，就继续找命令内容
		charQueueOut(src, &len);	//---command length
		
		while((len > 0) &&  (i < 5)) {	//---command context
			charQueueOut(src, array + i);
			i++;
		}
		return	i;
	}
	
	return	0;
}

/*****************************************************************************/
//----嘴巴相关
/********************************************************/
//---黑色
void mouse_OFF_stat(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(4, 5);  //---红常灭
	MPWMTMR_SETSTAT(3, 5);  //---绿常灭
	MPWMTMR_SETSTAT(5, 5);  //---蓝常灭	
	#else
	pwdTmr_set(4, 5);  //---红常灭
	pwdTmr_set(3, 5);  //---绿常灭
	pwdTmr_set(5, 5);  //---蓝常灭
	#endif
}
//---红色
void mouse_color_R(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 4);  //---红常亮
	MPWMTMR_SETSTAT(4, 5);  //---绿常灭
	MPWMTMR_SETSTAT(5, 5);  //---蓝常灭
	#else
	pwdTmr_set(3, 4);  //---红常亮
	pwdTmr_set(4, 5);  //---绿常灭
	pwdTmr_set(5, 5);  //---蓝常灭
	#endif
}

//---绿色
void mouse_color_G(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 5);  //---红常灭
	MPWMTMR_SETSTAT(4, 4);  //---绿常亮
	MPWMTMR_SETSTAT(5, 5);  //---蓝常灭
	#else
	pwdTmr_set(3, 5);  //---红常灭
	pwdTmr_set(4, 4);  //---绿常亮
	pwdTmr_set(5, 5);  //---蓝常灭
	#endif
}

//---蓝色
void mouse_color_B(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 5);  //---红常灭
	MPWMTMR_SETSTAT(4, 5);  //---绿常灭
	MPWMTMR_SETSTAT(5, 4);  //---蓝常亮
	#else
	pwdTmr_set(3, 5);  //---红常灭
	pwdTmr_set(4, 5);  //---绿常灭
	pwdTmr_set(5, 4);  //---蓝常亮
	#endif
}

//---紫色
void mouse_color_RB(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 4);  //---红常亮
	MPWMTMR_SETSTAT(4, 5);  //---绿常灭
	MPWMTMR_SETSTAT(5, 4);  //---蓝常亮
	#else
	pwdTmr_set(3, 4);  //---红常亮
	pwdTmr_set(4, 5);  //---绿常灭
	pwdTmr_set(5, 4);  //---蓝常亮
	#endif
}

//---白色
void mouse_color_RGB(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 4);  //---红常亮
	MPWMTMR_SETSTAT(4, 4);  //---绿常亮
	MPWMTMR_SETSTAT(5, 4);  //---蓝常亮
	#else
	pwdTmr_set(3, 4);  //---红常亮
	pwdTmr_set(4, 4);  //---绿常亮
	pwdTmr_set(5, 4);  //---蓝常亮
	#endif
}

//---蓝白色
void mouse_color_BL(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 3);  //---1/2红
	MPWMTMR_SETWIDE(3, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(4, 3);  //---1/2绿
	MPWMTMR_SETWIDE(4, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(5, 4);  //---蓝常亮
	#else
	pwdTmr_set(3, 3);  //---1/2红
	pwdTmr_setWide(3, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(4, 3);  //---1/2绿
	pwdTmr_setWide(4, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(5, 4);  //---蓝常亮
	#endif
}

//---玫红色
void mouse_color_MH(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 4);  //---红常亮
	MPWMTMR_SETSTAT(4, 5);  //---绿常灭	
	
	MPWMTMR_SETSTAT(5, 3);  //---1/2蓝
	MPWMTMR_SETWIDE(5, PWM_DUTY_MAX / 2);
	
	#else
	pwdTmr_set(3, 4);  //---红常亮
	pwdTmr_set(4, 5);  //---绿常灭
	
	pwdTmr_set(5, 3);  //---1/2蓝
	pwdTmr_setWide(5, PWM_DUTY_MAX / 2);
	#endif
}

//---橙黄色
void mouse_color_CH(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(3, 4);  //---红常亮
	
	MPWMTMR_SETSTAT(4, 3);  //---1/2绿
	MPWMTMR_SETWIDE(4, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(5, 5);  //---蓝常灭
	#else
	pwdTmr_set(3, 4);  //---红常亮
	
	pwdTmr_set(4, 3);  //---1/2绿
	pwdTmr_setWide(4, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(5, 5);  //---蓝常灭
	#endif
}

/*********************************************/
	#ifdef DPWMTMR_SET
void mouse_breathAscend_R(void){MPWMTMR_SETSTAT(3, 1); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 5);}
void mouse_breathAscend_G(void){MPWMTMR_SETSTAT(3, 5); MPWMTMR_SETSTAT(4, 1); MPWMTMR_SETSTAT(5, 5);}
void mouse_breathAscend_B(void){MPWMTMR_SETSTAT(3, 5); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 1);}
void mouse_breathAscend_RB(void){MPWMTMR_SETSTAT(3, 1); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 1);}
void mouse_breathAscend_RGB(void){MPWMTMR_SETSTAT(3, 1); MPWMTMR_SETSTAT(4, 1); MPWMTMR_SETSTAT(5, 1);}
#else
void mouse_breathAscend_R(void){pwdTmr_set(3, 1); pwdTmr_set(4, 5); pwdTmr_set(5, 5);}
void mouse_breathAscend_G(void){pwdTmr_set(3, 5); pwdTmr_set(4, 1); pwdTmr_set(5, 5);}
void mouse_breathAscend_B(void){pwdTmr_set(3, 5); pwdTmr_set(4, 5); pwdTmr_set(5, 1);}
void mouse_breathAscend_RB(void){pwdTmr_set(3, 1); pwdTmr_set(4, 5); pwdTmr_set(5, 1);}
void mouse_breathAscend_RGB(void){pwdTmr_set(3, 1); pwdTmr_set(4, 1); pwdTmr_set(5, 1);}
#endif
/*********************************************/
	#ifdef DPWMTMR_SET
void mouse_breathDecline_R(void){MPWMTMR_SETSTAT(3, 2); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 5);}
void mouse_breathDecline_G(void){MPWMTMR_SETSTAT(3, 5); MPWMTMR_SETSTAT(4, 2); MPWMTMR_SETSTAT(5, 5);}
void mouse_breathDecline_B(void){MPWMTMR_SETSTAT(3, 5); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 2);}
void mouse_breathDecline_RB(void){MPWMTMR_SETSTAT(3, 2); MPWMTMR_SETSTAT(4, 5); MPWMTMR_SETSTAT(5, 2);}
void mouse_breathDecline_RGB(void){MPWMTMR_SETSTAT(3, 2); MPWMTMR_SETSTAT(4, 2); MPWMTMR_SETSTAT(5, 2);}
	#else
void mouse_breathDecline_R(void){pwdTmr_set(3, 2); pwdTmr_set(4, 5); pwdTmr_set(5, 5);}
void mouse_breathDecline_G(void){pwdTmr_set(3, 5); pwdTmr_set(4, 2); pwdTmr_set(5, 5);}
void mouse_breathDecline_B(void){pwdTmr_set(3, 5); pwdTmr_set(4, 5); pwdTmr_set(5, 2);}
void mouse_breathDecline_RB(void){pwdTmr_set(3, 2); pwdTmr_set(4, 5); pwdTmr_set(5, 2);}
void mouse_breathDecline_RGB(void){pwdTmr_set(3, 2); pwdTmr_set(4, 2); pwdTmr_set(5, 2);}
	#endif
/*****************************************************************************
 *
 * 通过控制LED_P1_CRL/LED_P2_CRL/LED_P3_CRL来控制嘴的形状(动作效果)
 *
 *****************************************************************************/

void	mouse_shape0(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 1);
	MLEDPORT_SETSTAT(1, 1);
	MLEDPORT_SETSTAT(2, 1);
	#else
	ledport_setStat(0, 1);
	ledport_setStat(1, 1);
	ledport_setStat(2, 1);
	#endif
}

void	mouse_shape1(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 2);
	MLEDPORT_SETSTAT(1, 1);
	MLEDPORT_SETSTAT(2, 1);
	#else
	ledport_setStat(0, 2);
	ledport_setStat(1, 1);
	ledport_setStat(2, 1);
	#endif
}

void	mouse_shape2(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 1);
	MLEDPORT_SETSTAT(1, 2);
	MLEDPORT_SETSTAT(2, 1);
	#else
	ledport_setStat(0, 1);
	ledport_setStat(1, 2);
	ledport_setStat(2, 1);
	#endif
}

void	mouse_shape3(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 2);
	MLEDPORT_SETSTAT(1, 2);
	MLEDPORT_SETSTAT(2, 1);
	#else
	ledport_setStat(0, 2);
	ledport_setStat(1, 2);
	ledport_setStat(2, 1);
	#endif
}

void	mouse_shape4(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 1);
	MLEDPORT_SETSTAT(1, 1);
	MLEDPORT_SETSTAT(2, 2);
	#else
	ledport_setStat(0, 1);
	ledport_setStat(1, 1);
	ledport_setStat(2, 2);
	#endif
}

void	mouse_shape5(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 2);
	MLEDPORT_SETSTAT(1, 1);
	MLEDPORT_SETSTAT(2, 2);
	#else
	ledport_setStat(0, 2);
	ledport_setStat(1, 1);
	ledport_setStat(2, 2);
	#endif
}

void	mouse_shape6(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 1);
	MLEDPORT_SETSTAT(1, 2);
	MLEDPORT_SETSTAT(2, 2);
	#else
	ledport_setStat(0, 1);
	ledport_setStat(1, 2);
	ledport_setStat(2, 2);
	#endif
}

void	mouse_shape7(void)
{
	#if	1
	MLEDPORT_SETSTAT(0, 2);
	MLEDPORT_SETSTAT(1, 2);
	MLEDPORT_SETSTAT(2, 2);
	#else
	ledport_setStat(0, 2);
	ledport_setStat(1, 2);
	ledport_setStat(2, 2);
	#endif
}

/**********************************************/

void ear_OFF_stat(u8 arg)
{
	#if	1
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 2);
	#else
	ledport_setStat(6, 2);
	ledport_setStat(7, 2);
	ledport_setStat(8, 2);
	#endif
	
	//pwdTmr_set(6, (arg = 5)/** 消除警告 **/);
	MPWMTMR_SETSTAT(6, (arg = 5)/** 消除警告 **/);
}
//----红
void ear_color_R(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---绿
void ear_color_G(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---蓝
void ear_color_B(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---黄
void ear_color_RG(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---青色
void ear_color_BG(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---紫色
void ear_color_RB(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//---白色
void ear_color_RGB(void)
{
	#if	1
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 4);
	MPWMTMR_SETSTAT(6, 4);
}

//void	ear_color_BL(void){}
//void	ear_color_MH(void){}
//void	ear_color_CH(void){}

/**********************************************/

void	ear_breathAscend_R(void)
{
	#if	0
	LED_R_CRL = 1;		//红常亮
	LED_G_CRL = 0;		//绿常灭
	LED_B_CRL = 0;		//蓝常灭
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathAscend_G(void)
{
	#if	0
	LED_R_CRL = 0;		//红常灭
	LED_G_CRL = 1;		//绿常高
	LED_B_CRL = 0;		//蓝常灭
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathAscend_B(void)
{
		#if	0
	LED_R_CRL = 0;		//红常灭
	LED_G_CRL = 0;		//绿常灭
	LED_B_CRL = 1;		//蓝常亮
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathAscend_RB(void)
{
		#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 0;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathAscend_RGB(void)
{
		#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}

void	ear_breathAscend_RG(void)
{
	#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 0;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathAscend_BG(void)
{
		#if	0
	LED_R_CRL = 0;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}

/**********************************************/

void	ear_breathDecline_R(void)
{
		#if	0
	LED_R_CRL = 1;		//红常亮
	LED_G_CRL = 0;		//绿常灭
	LED_B_CRL = 0;		//蓝常灭
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 2);
	MPWMTMR_SETSTAT(6, 2);
}
void	ear_breathDecline_G(void)
{
		#if	0
	LED_R_CRL = 0;		//红常灭
	LED_G_CRL = 1;		//绿常高
	LED_B_CRL = 0;		//蓝常灭
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 2);
	MPWMTMR_SETSTAT(6, 2);
}
void	ear_breathDecline_B(void)
{
	#if	0
	LED_R_CRL = 0;		//红常灭
	LED_G_CRL = 0;		//绿常灭
	LED_B_CRL = 1;		//蓝常亮
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathDecline_RB(void)
{
	#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 0;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 2);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 2);
	MPWMTMR_SETSTAT(6, 2);
}
void	ear_breathDecline_RGB(void)
{
	#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 2);
	MPWMTMR_SETSTAT(6, 2);
}

void	ear_breathDecline_RG(void)
{
	#if	0
	LED_R_CRL = 1;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 0;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 1);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 2);
	#endif
	//pwdTmr_set(6, 1);
	MPWMTMR_SETSTAT(6, 1);
}
void	ear_breathDecline_BG(void)
{
			#if	0
	LED_R_CRL = 0;		//高有效
	LED_G_CRL = 1;		//高有效
	LED_B_CRL = 1;		//高有效
	#else
	MLEDPORT_SETSTAT(6, 2);
	MLEDPORT_SETSTAT(7, 1);
	MLEDPORT_SETSTAT(8, 1);
	#endif
	//pwdTmr_set(6, 2);
	MPWMTMR_SETSTAT(6, 2);
}

/*****************************************************************************
 * 
 *****************************************************************************/
//---全熄灭
void eye_color_OFF(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 5);	//---红常灭
	MPWMTMR_SETSTAT(2, 5);	//---绿常灭
	MPWMTMR_SETSTAT(1, 5);	//---蓝常灭
	#else
	pwdTmr_set(7, 5);	//---红常灭
	pwdTmr_set(2, 5);	//---绿常灭
	pwdTmr_set(1, 5);	//---蓝常灭
	#endif
}
//---红
void eye_color_R(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 4);	//---红常亮
	MPWMTMR_SETSTAT(2, 5);	//---绿常灭
	MPWMTMR_SETSTAT(1, 5);	//---蓝常灭
	#else
	pwdTmr_set(7, 4);	//---红常亮
	pwdTmr_set(2, 5);	//---绿常灭
	pwdTmr_set(1, 5);	//---蓝常灭
	#endif
}

//---绿
void eye_color_G(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 5);	//---红常灭
	MPWMTMR_SETSTAT(2, 4);	//---绿常亮
	MPWMTMR_SETSTAT(1, 5);	//---蓝常灭
	#else
	pwdTmr_set(7, 5);	//---红常灭
	pwdTmr_set(2, 4);	//---绿常亮
	pwdTmr_set(1, 5);	//---蓝常灭
	#endif
}

//---蓝
void eye_color_B(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 5);	//---红常灭
	MPWMTMR_SETSTAT(2, 5);	//---绿常灭
	MPWMTMR_SETSTAT(1, 4);	//---蓝常亮
	#else
	pwdTmr_set(7, 5);	//---红常灭
	pwdTmr_set(2, 5);	//---绿常灭
	pwdTmr_set(1, 4);	//---蓝常亮
	#endif
}

//---紫 = 红+蓝
void eye_color_RB(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 4);	//---红常亮
	MPWMTMR_SETSTAT(2, 5);	//---绿常灭
	MPWMTMR_SETSTAT(1, 4);	//---蓝常亮
	#else
	pwdTmr_set(7, 4);	//---红常亮
	pwdTmr_set(2, 5);	//---绿常灭
	pwdTmr_set(1, 4);	//---蓝常亮
	#endif
}

//---白 = 红+绿+蓝
void eye_color_RGB(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 4);	//---红常亮
	MPWMTMR_SETSTAT(2, 4);	//---绿常亮
	MPWMTMR_SETSTAT(1, 4);	//---蓝常亮
	#else
	pwdTmr_set(7, 4);	//---红常亮
	pwdTmr_set(2, 4);	//---绿常亮
	pwdTmr_set(1, 4);	//---蓝常亮
	#endif
}

//---蓝白
void eye_color_LB(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 3);  //---1/2红
	MPWMTMR_SETWIDE(7, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(2, 3);  //---1/2绿
	MPWMTMR_SETWIDE(2, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(1, 4);  //---蓝常亮
	#else
	
	pwdTmr_set(7, 3);  //---1/2红
	pwdTmr_setWide(7, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(2, 3);  //---1/2绿
	pwdTmr_setWide(2, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(1, 4);  //---蓝常亮
	#endif
}

//---玫红 = 红+蓝/2
void eye_color_MH(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 4);  //---红常亮
	MPWMTMR_SETSTAT(2, 5);  //---绿常灭
	
	MPWMTMR_SETSTAT(1, 3);  //---1/2蓝
	MPWMTMR_SETWIDE(1, PWM_DUTY_MAX / 2);
	#else
	
	pwdTmr_set(7, 4);  //---红常亮
	pwdTmr_set(2, 5);  //---绿常灭
	
	pwdTmr_set(1, 3);  //---1/2蓝
	pwdTmr_setWide(1, PWM_DUTY_MAX / 2);
	#endif
}

//---橙黄 = 红+绿/2
void eye_color_CH(void)
{
	#ifdef DPWMTMR_SET
	MPWMTMR_SETSTAT(7, 4);  //---红常亮
	
	MPWMTMR_SETSTAT(2, 3);  //---1/2绿
	MPWMTMR_SETWIDE(2, PWM_DUTY_MAX / 2);
	
	MPWMTMR_SETSTAT(1, 5);  //---蓝常灭
	#else
	pwdTmr_set(7, 4);  //---红常亮
	
	pwdTmr_set(2, 3);  //---1/2绿
	pwdTmr_setWide(2, PWM_DUTY_MAX / 2);
	
	pwdTmr_set(1, 5);  //---蓝常灭
	#endif
}

/*********************************************/

	#ifdef DPWMTMR_SET
void eye_breathAscend_R(void){MPWMTMR_SETSTAT(7, 1); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 5);}
void eye_breathAscend_G(void){MPWMTMR_SETSTAT(7, 5); MPWMTMR_SETSTAT(2, 1); MPWMTMR_SETSTAT(1, 5);}
void eye_breathAscend_B(void){MPWMTMR_SETSTAT(7, 5); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 1);}
void eye_breathAscend_RB(void){MPWMTMR_SETSTAT(7, 1); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 1);}
void eye_breathAscend_RGB(void){MPWMTMR_SETSTAT(7, 1); MPWMTMR_SETSTAT(2, 1); MPWMTMR_SETSTAT(1, 1);}
	#else
void eye_breathAscend_R(void){pwdTmr_set(7, 1); pwdTmr_set(2, 5); pwdTmr_set(1, 5);}
void eye_breathAscend_G(void){pwdTmr_set(7, 5); pwdTmr_set(2, 1); pwdTmr_set(1, 5);}
void eye_breathAscend_B(void){pwdTmr_set(7, 5); pwdTmr_set(2, 5); pwdTmr_set(1, 1);}
void eye_breathAscend_RB(void){pwdTmr_set(7, 1); pwdTmr_set(2, 5); pwdTmr_set(1, 1);}
void eye_breathAscend_RGB(void){pwdTmr_set(7, 1); pwdTmr_set(2, 1); pwdTmr_set(1, 1);}
	#endif
//void eye_breathAscend_BL(void){}
//void eye_breathAscend_MH(void){}
//void eye_breathAscend_CH(void){}

/*********************************************/
#ifdef	DPWMTMR_SET
void eye_breathDecline_R(void){MPWMTMR_SETSTAT(7, 2); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 5);}
void eye_breathDecline_G(void){MPWMTMR_SETSTAT(7, 5); MPWMTMR_SETSTAT(2, 2); MPWMTMR_SETSTAT(1, 5);}
void eye_breathDecline_B(void){MPWMTMR_SETSTAT(7, 5); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 2);}
void eye_breathDecline_RB(void){MPWMTMR_SETSTAT(7, 2); MPWMTMR_SETSTAT(2, 5); MPWMTMR_SETSTAT(1, 2);}
void eye_breathDecline_RGB(void){MPWMTMR_SETSTAT(7, 2); MPWMTMR_SETSTAT(2, 2); MPWMTMR_SETSTAT(1, 2);}
#else
void eye_breathDecline_R(void){pwdTmr_set(7, 2); pwdTmr_set(2, 5); pwdTmr_set(1, 5);}
void eye_breathDecline_G(void){pwdTmr_set(7, 5); pwdTmr_set(2, 2); pwdTmr_set(1, 5);}
void eye_breathDecline_B(void){pwdTmr_set(7, 5); pwdTmr_set(2, 5); pwdTmr_set(1, 2);}
void eye_breathDecline_RB(void){pwdTmr_set(7, 2); pwdTmr_set(2, 5); pwdTmr_set(1, 2);}
void eye_breathDecline_RGB(void){pwdTmr_set(7, 2); pwdTmr_set(2, 2); pwdTmr_set(1, 2);}
#endif
//void eye_breathDecline_LB(void){}
//void eye_breathDecline_MH(void){}
//void eye_breathDecline_CH(void){}

/*********************************************/
void	eye_shape0(void)
{
	MLEDPORT_SETSTAT(3, 1);
	MLEDPORT_SETSTAT(4, 1);
	MLEDPORT_SETSTAT(5, 1);
}

void	eye_shape1(void)
{
	MLEDPORT_SETSTAT(3, 2);
	MLEDPORT_SETSTAT(4, 1);
	MLEDPORT_SETSTAT(5, 1);
}

void	eye_shape2(void)
{
	MLEDPORT_SETSTAT(3, 1);
	MLEDPORT_SETSTAT(4, 2);
	MLEDPORT_SETSTAT(5, 1);
}

void	eye_shape3(void)
{
	MLEDPORT_SETSTAT(3, 2);
	MLEDPORT_SETSTAT(4, 2);
	MLEDPORT_SETSTAT(5, 1);
}

void	eye_shape4(void)
{
	MLEDPORT_SETSTAT(3, 1);
	MLEDPORT_SETSTAT(4, 1);
	MLEDPORT_SETSTAT(5, 2);
}

void	eye_shape5(void)
{
	MLEDPORT_SETSTAT(3, 2);
	MLEDPORT_SETSTAT(4, 1);
	MLEDPORT_SETSTAT(5, 2);
}

void	eye_shape6(void)
{
	MLEDPORT_SETSTAT(3, 1);
	MLEDPORT_SETSTAT(4, 2);
	MLEDPORT_SETSTAT(5, 2);
}

void	eye_shape7(void)
{
	MLEDPORT_SETSTAT(3, 2);
	MLEDPORT_SETSTAT(4, 2);
	MLEDPORT_SETSTAT(5, 2);
}


/*******************************************************************************
 * 嘴巴/眼睛/耳朵
 *******************************************************************************/
void pwmPort_Init(void)
{
	P0M0 &= ~0xc0;
    P0M1 &= ~0xc0;
    P0 &= ~0xc0;                    //设置P0.6/.P0.7电平
	
    P2M0 &= ~0x8e;
    P2M1 &= ~0x8e;
    P2 &= ~0x8e;                    //设置P2.1/P2.2/P2.3/P2.7电平
	
    P3M0 &= ~0x80;
    P3M1 &= ~0x80;
    P3 &= ~0x80;                    //设置P3.7电平
	/***mouse *********/
	P4M0 &= ~0x18;
	P4M1 &= ~0x18;
	P4 &= ~0x18; 					//设置P4.3/P4.4电平
	
	P2M0 &= ~0x01;
    P2M1 &= ~0x01;
    P2 &= ~0x01;                    //设置P2.0电平
	/*** eye **********/
	P4M0 &= ~0x60;
	P4M1 &= ~0x60;
	P4 &= ~0x60; 					//设置P4.5/P4.6电平
	
	P0M0 &= ~0x10;
    P0M1 &= ~0x10;
    P0 &= ~0x10;                    //设置P0.4电平
	/*** ear **********/
	P4M0 &= ~0x80;
	P4M1 &= ~0x80;
	P4 &= ~0x80; 					//设置P4.7电平
	/*** for debug ********/
	P4M0 &= ~0x06;
	P4M1 &= ~0x06;
	P4 &= ~0x06; 					//设置P4.1/P4.2电平
}

/**
 * bl51 driver.obj IX OVERLAY (?CO?DRIVER ~ mouse, sysProcess ! mouse)
 **/
code paction_t_0 g_part_color_expire[4][4][16] = {
#define	color_doNothing	actionDoNothing
	/** reserved **/
	{
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
	},
	/** mouse color **/
	{
		/** no expire **/
		{	mouse_OFF_stat, 
			mouse_color_R, 
			mouse_color_G, 
			mouse_color_B, 
			mouse_color_RB, 
			mouse_color_RGB, 
			mouse_color_BL, 
			mouse_color_MH, 
			mouse_color_CH, 
			color_doNothing, 
			color_doNothing, 
			color_doNothing, 
			color_doNothing, 
			color_doNothing, 
			color_doNothing, 
			color_doNothing,
		},
		/** ascend **/
		{
			color_doNothing,	//---黑
			mouse_breathAscend_R,
			mouse_breathAscend_G,
			mouse_breathAscend_B,
			mouse_breathAscend_RB,
			mouse_breathAscend_RGB,	//---白
	
			color_doNothing,	//---BL
			color_doNothing,	//---MH
			color_doNothing,	//---CH
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** Decline **/
		{
			mouse_OFF_stat,	//---黑
			mouse_breathDecline_R,
			mouse_breathDecline_G,
			mouse_breathDecline_B,
			mouse_breathDecline_RB,
			mouse_breathDecline_RGB,	//---白
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** reserved **/
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
	},
	/** eye color **/
	{
		/** no expire **/
		{
			eye_color_OFF,	//---黑
			eye_color_R,
			eye_color_G,
			eye_color_B,
			eye_color_RB,
			eye_color_RGB,
	
			eye_color_LB,
			eye_color_MH,
			eye_color_CH,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** ascend **/
		{
			eye_color_OFF,	//---黑
			eye_breathAscend_R,
			eye_breathAscend_G,
			eye_breathAscend_B,
			eye_breathAscend_RB,
			eye_breathAscend_RGB,
	
			color_doNothing,	//---BL
			color_doNothing,	//---MH
			color_doNothing,	//---CH
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** Decline **/
		{
			eye_color_OFF,	//---黑
			eye_breathDecline_R,
			eye_breathDecline_G,
			eye_breathDecline_B,
			eye_breathDecline_RB,
			eye_breathDecline_RGB,
	
			color_doNothing,	//---LB
			color_doNothing,	//---MH
			color_doNothing,	//---CH
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** reserved **/
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
	},
	/** ear color **/
	{
		/** no expire **/
		{
			ear_OFF_stat,	//---黑
			ear_color_R,
			ear_color_G,
			ear_color_B,
			ear_color_RB,	//---紫
			ear_color_RGB,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
	
			ear_color_RG,	//---黄
			ear_color_BG,	//---青
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** ascend **/
		{
			ear_OFF_stat,		//---黑
			ear_breathAscend_R,
			ear_breathAscend_G,
			ear_breathAscend_B,
			ear_breathAscend_RB,
			ear_breathAscend_RGB,
	
			color_doNothing,	//---BL
			color_doNothing,	//---MH
			color_doNothing,	//---CH
	
			ear_breathAscend_RG,
			ear_breathAscend_BG,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** Decline **/
		{
			ear_OFF_stat,	//---黑
			ear_breathDecline_R,
			ear_breathDecline_G,
			ear_breathDecline_B,
			ear_breathDecline_RB,
			ear_breathDecline_RGB,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
	
			ear_breathDecline_RG,
			ear_breathDecline_BG,
	
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
			color_doNothing,
		},
		/** reserved **/
		{	color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing, 
			color_doNothing, color_doNothing, color_doNothing, color_doNothing,
		},
	},
#undef	color_doNothing
};


code paction_t_0 g_part_shape[4][8] = {
#define	shape_doNothing	actionDoNothing
	/** reserved **/
	{shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing},
	/** mouse shape **/
	{mouse_shape0, mouse_shape1, mouse_shape2, mouse_shape3, mouse_shape4, mouse_shape5, mouse_shape6, mouse_shape7},
	/** eye shape **/
	{eye_shape0, eye_shape1, eye_shape2, eye_shape3, eye_shape4, eye_shape5, eye_shape6, eye_shape7},
	/** ear shape **/
	{shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing, shape_doNothing},

#undef	shape_doNothing
};
/*************************************************************************/
void Uart_Init() 
{
	#if	0	//---raw
	EA = 0; 		//暂时关闭中断
	P_SW1 &= 0xC0;
	TMOD &= 0x0F;  //定时器1模式控制在高4位
	TMOD |= 0x20;    //定时器1工作在模式2，自动重装模式
	SCON = 0x50;     //串口工作在模式1
	
	TH1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));  //计算定时器重装值
	TL1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));
	PCON |= 0x80;    //串口波特率加倍
	ES = 1;         //串行中断允许
	TR1 = 1;        //启动定时器1
	REN = 1;        //允许接收 
	//EA = 1;         //允许中断
	#endif
	
	#if	0
	EA = 0; 		//暂时关闭中断
	P_SW1 &= 0xC0;
	TMOD &= 0x0F;  //定时器1模式控制在高4位
	TMOD |= 0x20;    //定时器1工作在模式2，自动重装模式
	SCON = 0x50;     //串口工作在模式1
	
	TH1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));  //计算定时器重装值
	TL1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));
	PCON |= 0x80;    //串口波特率加倍
	ES = 1;         //串行中断允许
	TR1 = 1;        //启动定时器1
	REN = 1;        //允许接收 
	//EA = 1;         //允许中断
	#else
	
	EA = 0; 		//暂时关闭中断
	P_SW1 &= 0xC0;
	SCON = 0x50;                //8位可变波特率
	//AUXR = 0x40;                //定时器1为1T模式
	AUXR |= (1 << 6);             //定时器1为1T模式
	AUXR &= 0xFE;                //---定时器1波特率发生器
    //TMOD = 0x20;                //定时器1为模式2(8位自动重载)
	TMOD &= 0x0F;  //定时器1模式控制在高4位
	TMOD |= 0x20;    //定时器1工作在模式2，自动重装模式
    TL1 = (256 - (MAIN_Fosc/32/Baud_Rate));   //设置波特率重装值
    TH1 = (256 - (MAIN_Fosc/32/Baud_Rate));
    TR1 = 1;                    //定时器1开始工作
    ES = 1;                     //使能串口中断
    //EA = 1;
	
	#endif
}

void Uart2_Init()
{
//---
	#if	1
	S2CON = 0x50;       //8-bit variable UART. 允许接收
	T2L = ((65536 - (MAIN_Fosc/4/Baud_Rate)) & 0xff);
    T2H = (((65536 - (MAIN_Fosc/4/Baud_Rate)) >> 8) & 0xff);
	AUXR &= ~(1<<3);	//---T2用作定时器
	AUXR |=  (1<<2);	//---定时器2为1T模式
	AUXR |=  (1<<4);	//---允许T2定时器运行
   // AUXR |= 0x14;            
    IE2 |= 0x01;              //使能串口2中断            
    //EA = 1;
	#endif
}

#if	0
void Uart4_Init() 
{
//---P0.2->RXD4 P0.3->TXD4	
	S4CON = 0x50;         
    T4L = (65536 - (MAIN_Fosc/4/Baud_Rate)) & 0xff; 
    T4H = ((65536 - (MAIN_Fosc/4/Baud_Rate)) >> 8) & 0xff;
    T4T3M |= 0x20;             
    T4T3M |= 0x80;              
    IE2 |= 0x10;               
    //EA = 1;
}
#endif

#if	0
//向串口1发一个字符串
void SendString(char *s)
{
    while(*s != '\0')
		SendData(*s++);
}
#endif

void timer0_Init(void)
{
	EA = 0; 		//暂时关闭中断
	ET0 = 0;		//Timer0 Interrupt disable
	AUXR |=  (1 << 7);	// Timer0 set as 1T mode
	TMOD &= ~(1 << 2);	// Timer0 set as Timer
	TMOD &= ~0x03;		// Timer0 set as 16 bits Auto Reload
	TH0 = ((Timer0_Reload >> 8) & 0xff);	//Timer0 Load
	TL0 = (Timer0_Reload & 0xff);
	ET0 = 1;		//Timer0 Interrupt Enable
	PT0 = 1;		//高优先级
	TR0 = 1;		//Timer0 Run
	//EA = 1;			//打开总中断
	
	#if	0
	EA = 0; 		//暂时关闭中断
	ET0 = 0;		//Timer0 Interrupt disable
	AUXR |=  (1 << 7);	// Timer0 set as 1T mode
	TMOD &= ~(1 << 2);	// Timer0 set as Timer
	TMOD &= ~0x03;		// Timer0 set as 16 bits Auto Reload
	TH0 = ((Timer0_Reload >> 8) & 0xff);	//Timer0 Load
	TL0 = (Timer0_Reload & 0xff);
	ET0 = 1;		//Timer0 Interrupt Enable
	PT0 = 1;		//高优先级
	TR0 = 1;		//Timer0 Run
	//EA = 1;			//打开总中断
	#endif
}
/*************************************************************************/

/*************************************************************************/