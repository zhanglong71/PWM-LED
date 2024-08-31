#ifndef __CONST_H__
#define __CONST_H__

/**************************************************************************/
#define MAIN_Fosc		11059200UL	//定义主时钟
//#define	Timer0_Rate		25000UL		//中断频率
#define	Timer0_Rate		10000UL		//定时中断频率
#define	Baud_Rate		9600UL		//uart波特率

#define	Timer0_Reload	(65536UL -(MAIN_Fosc / Timer0_Rate))		//Timer 0 重装值
/**************************************************************************/

#define TIMER_NUM	2       /** the number of timer **/

#define	TRUE	1
#define	FALSE	0

//#define	TIMER_1MS	(10)
//#define	TIMER_10MS	(10 * TIMER_1MS)
#define	CTIMER_10MS	(1)
#define	CTIMER_20MS	(2 * CTIMER_10MS)
#define	CTIMER_100MS	(10 * CTIMER_10MS)

#define	CTIMER_1SEC	(10 * CTIMER_100MS)
//-----------------------
#define		PWM_DUTY_MAX		198	// 0~200	PWM周期, 最大200
//#define		PWM_DUTY_MAX	250	// 0~255	PWM周期, 最大255

#define		PWM_ON			1	// 定义占空比的电平, 1 或 0
#define		PWM_OFF			(!PWM_ON)
#define		PWM_ALL_ON		(0xff * PWM_ON)
//-----------------------
#define TIMER_UART_RX (7)	//---规定不能超过10ms对应值
/**************************************************************************/
//--- for protocal
#define	CPROTOCAL_HEAD	(0x5A)
//----------------------------
#define	CPROTOCAL_MOTOCOMM	(1)
				#define	CPROTOCAL_MOTOCOMM_FORWARD	(1)
				#define	CPROTOCAL_MOTOCOMM_BACKWARD	(2)
				#define	CPROTOCAL_MOTOCOMM_TURNLEFT	(3)
				#define	CPROTOCAL_MOTOCOMM_TURNRIGHT	(4)
				#define	CPROTOCAL_MOTOCOMM_FOOTSTOP	(5)
				
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_FORWARD		(8)
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_BACKWARD		(9)
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_STOP			(10)
				
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_FORWARD		(16)
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_BACKWARD	(17)
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_STOP		(18)
				
				#define	CPROTOCAL_MOTOCOMM_NECK_FORWARD			(24)
				#define	CPROTOCAL_MOTOCOMM_NECK_BACKWARD			(25)
				#define	CPROTOCAL_MOTOCOMM_NECK_STOP				(26)
				
				#define	CPROTOCAL_MOTOCOMM_NECK_LEFT			(32)
				#define	CPROTOCAL_MOTOCOMM_NECK_RIGHT		(33)			
#define	CPROTOCAL_MOTORESP	(2)
//-----------------------------
#define	CPROTOCAL_LEDCOMM	(3)
				#define	CPROTOCAL_LEDCOMM_TALK		(1)
				#define	CPROTOCAL_LEDCOMM_BLINK		(2)
				#define	CPROTOCAL_LEDCOMM_SHAKE		(3)
#define	CPROTOCAL_LEDRESP	(4)
//-----------------------------
#define	CPROTOCAL_IRCOMM	(5)		//---红外壁障
#define	CPROTOCAL_IRRESP	(6)
//-----------------------------
#define	CPROTOCAL_SLEEPCOMM	(7)		//---休眠按键
#define	CPROTOCAL_SLEEPRESP	(8)
//-----------------------------
#define	CPROTOCAL_ADCCOMM	(9)		//---ADC电量检测
#define	CPROTOCAL_ADCRESP	(9)		//---ADC电量检测
/**************************************************************************/
#endif