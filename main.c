/**************************************************************************
 *  
 *  项目名称: 机器人灯光执行部件
 *  作    者: 张龙(zhanglong93@sohu.com)
 *  MCU型号: IAP15W4K61S4
 *  V1.0日期: 
 *  版    本:V0.1
 *  备    注: 
 *  修改日期: 2016-06-30
 *
 **************************************************************************/
//#include	<reg52.h>

#include	"STC15W4K60S4.H"

#include	"const.h"
#include	"ptype.h"
#include 	"macro.h"
#include 	"global.h"
#include 	"arch.h"
#include 	"driver.h"
#include	"main.h"

#include    "f_idle.h"

bit		B_1ms;
bit		B_10ms;
bit		B_20ms;
bit		B_100ms;
u8		cnt_1ms;
u8		cnt_10ms;
u8		cnt_20ms;

u16 g_tick;

msgq_t  g_msgq;
fstack_t g_fstack;
//func_t g_func;
Timer_t g_timer[TIMER_NUM];		/** 约定g_timer[0]不用在sysProcess()中， g_timer[1]只用在sysProcess()中 **/
actionQueue_t g_actionQueue;
charQueue_t g_charTxQueue;		//only for Tx
charQueue_t g_charRxQueue;		//only for Rx
charQueue_t g_charTmpQueue;		//for Rx and process

pwmArray_t g_pwm;
portArray_t g_ledport;

/**********************************************/
void main(void)

{
	u8	i;
	msg_t msg;
	func_t func;
	
	pwmPort_Init();
	timer0_Init();
	Uart_Init();
	Uart2_Init();
	//Uart4_Init();
	
	msg_init(&msg);	
	msgq_init(&g_msgq);	
	charQueueInit(&g_charTxQueue);
	charQueueInit(&g_charRxQueue);
	actionQueueInit(&g_actionQueue, &(g_timer[1]), CACT_TOUT, CACT_OVER);
	
	for(i = 0; i < TIMER_NUM; i++) {
        ClrTimer(&g_timer[i]);
    }
    SetTimer(&g_timer[0], CTIMER_1SEC, CMSG_TMR);
    
	#if	0
	msg.msgType = CMSG_POWR;		/** message type **/
	msg.msgValue = 0;			/** message value(no need) **/
	msgq_in_irq(&g_msgq, &msg);
	#endif
	
	cnt_1ms	= Timer0_Rate / 1000;	//1ms计数
	cnt_20ms = 20;
	
   	fstack_init(&g_fstack);
	func.func = f_idle;
   	fstack_push(&g_fstack, &func);
	
	EA = 1;			//打开总中断
	while(1)
	{
		//串口发数据
		uart1_Send();
		//检查i/o事件并执行相应动作
		actionDoing(&g_actionQueue);
		
		#if	1
		//响应i/o事件并执行相应动作
		if(msgq_out_irq(&g_msgq, &msg) == FALSE) {     	/** 有消息吗? **/
		//if(msgq_out(&g_msgq, &msg) == FALSE) {     	/** 有消息吗? **/
			continue;
		}
		#endif
		if(sysProcess(&msg) == TRUE) {   			/** 是系统消息吗? **/
			continue;
		}
		
		if(fstack_top(&g_fstack, &func) == FALSE) {    /** 当前工作状态 **/
		  /** something wrong happend, Power Down or recover it **/
		  	fstack_init(&g_fstack);
			func.func = f_idle;
			fstack_push(&g_fstack, &func);
			
			g_tick = 0;
			SetTimer_irq(&g_timer[0], CTIMER_1SEC, CMSG_TMR);
			continue;
		}
		func.func((unsigned *)&msg);
	}
}

msg_t i_msg;
//u8 i;
u8 uart_Rx_Tmr = TIMER_UART_RX + 1;
//u8	pwm_duty;		//周期计数值
/********************** Timer0 10kHz 中断函数 ************************/
void timer0 (void) interrupt 1
{
	//TH0 = ((Timer0_Reload >> 8) & 0xff);	//Timer0 Load
	//TL0 = (Timer0_Reload & 0xff);
	u8	i;
	
	#if	1
	if(++g_pwm.pwm_duty == PWM_DUTY_MAX) {		//PWM周期结束，重新开始新的周期
		g_pwm.pwm_duty = 0;
		if((1 == g_pwm.buf[1].stat) || (2 == g_pwm.buf[1].stat) || (3 == g_pwm.buf[1].stat))LED_PWM1_CRL = PWM_ON;
		if((1 == g_pwm.buf[2].stat) || (2 == g_pwm.buf[2].stat) || (3 == g_pwm.buf[2].stat))LED_PWM2_CRL = PWM_ON;
		if((1 == g_pwm.buf[3].stat) || (2 == g_pwm.buf[3].stat) || (3 == g_pwm.buf[3].stat))LED_PWM3_CRL = PWM_ON;
		if((1 == g_pwm.buf[4].stat) || (2 == g_pwm.buf[4].stat) || (3 == g_pwm.buf[4].stat))LED_PWM4_CRL = PWM_ON;
		if((1 == g_pwm.buf[5].stat) || (2 == g_pwm.buf[5].stat) || (3 == g_pwm.buf[5].stat))LED_PWM5_CRL = PWM_ON;
		if((1 == g_pwm.buf[6].stat) || (2 == g_pwm.buf[6].stat) || (3 == g_pwm.buf[6].stat))LED_PWM6_CRL = PWM_ON;
		if((1 == g_pwm.buf[7].stat) || (2 == g_pwm.buf[7].stat) || (3 == g_pwm.buf[7].stat))LED_PWM7_CRL = PWM_ON;
	}
	
	if((g_pwm.pwm_duty == g_pwm.buf[1].step) && ((1 == g_pwm.buf[1].stat) || (2 == g_pwm.buf[1].stat) || (3 == g_pwm.buf[1].stat)))		LED_PWM1_CRL  = PWM_OFF;	//判断PWM占空比是否结束
	if((g_pwm.pwm_duty == g_pwm.buf[2].step) && ((1 == g_pwm.buf[2].stat) || (2 == g_pwm.buf[2].stat) || (3 == g_pwm.buf[2].stat)))		LED_PWM2_CRL  = PWM_OFF;
	if((g_pwm.pwm_duty == g_pwm.buf[3].step) && ((1 == g_pwm.buf[3].stat) || (2 == g_pwm.buf[3].stat) || (3 == g_pwm.buf[3].stat)))		LED_PWM3_CRL  = PWM_OFF;
	if((g_pwm.pwm_duty == g_pwm.buf[4].step) && ((1 == g_pwm.buf[4].stat) || (2 == g_pwm.buf[4].stat) || (3 == g_pwm.buf[4].stat)))		LED_PWM4_CRL  = PWM_OFF;
	if((g_pwm.pwm_duty == g_pwm.buf[5].step) && ((1 == g_pwm.buf[5].stat) || (2 == g_pwm.buf[5].stat) || (3 == g_pwm.buf[5].stat)))		LED_PWM5_CRL  = PWM_OFF;
	if((g_pwm.pwm_duty == g_pwm.buf[6].step) && ((1 == g_pwm.buf[6].stat) || (2 == g_pwm.buf[6].stat) || (3 == g_pwm.buf[6].stat)))		LED_PWM6_CRL  = PWM_OFF;
	if((g_pwm.pwm_duty == g_pwm.buf[7].step) && ((1 == g_pwm.buf[7].stat) || (2 == g_pwm.buf[7].stat) || (3 == g_pwm.buf[7].stat)))		LED_PWM7_CRL  = PWM_OFF;
	#endif
	
	if(--cnt_1ms == 0) {
		cnt_1ms	= (Timer0_Rate / 1000);
		B_1ms = 1;			// 1ms标志
					
		if(uart_Rx_Tmr < TIMER_UART_RX) {
			uart_Rx_Tmr++;
		} else if(uart_Rx_Tmr == TIMER_UART_RX) {
			uart_Rx_Tmr = TIMER_UART_RX + 1;
			i_msg.msgType = CMSG_UARX;		/** message type **/
			//i_msg.msgValue = i;			/** message value(no need) **/
			msgq_in(&g_msgq, &i_msg);
		}
		
		if(--cnt_10ms == 0) {
			cnt_10ms = 10;
			B_10ms = 1;		// 10ms标志	
 
			#if	1
			//定时消息产生
			for(i = 0; i < TIMER_NUM; i++) {
				if(g_timer[i].tick_bak > 0) {
					if(g_timer[i].tick > 0) {
						g_timer[i].tick--;
					} else {
						g_timer[i].tick = g_timer[i].tick_bak;
                
						i_msg.msgType = g_timer[i].msgType;		/** message type **/
						i_msg.msgValue = i;						/** message value(Timer index) **/
						msgq_in(&g_msgq, &i_msg);
					}
				}
			}
			#endif
		}
		
		if(--cnt_20ms == 0) {
			cnt_20ms = 20;
	
			#if	1
			/****** ---pwm (led NO: from 0 to CPWM_NUM - 1) ****/
			for(i = 0; i < CPWM_NUM; i++) {
				if(g_pwm.buf[i].stat == 0) {
					/** do nothing **/
				} else if(g_pwm.buf[i].stat == 1) {
					//---ascend
					if(g_pwm.buf[i].step >= PWM_DUTY_MAX) {
						g_pwm.buf[i].stat = 0;;		//---!!!增到最大后停止
					} else {
						g_pwm.buf[i].step++;
					}
				} else if(g_pwm.buf[i].stat == 2) {
					//---decline
					if(g_pwm.buf[i].step == 0) {
						g_pwm.buf[i].stat = 0;		//---!!!减到最小后停止
					} else {
						g_pwm.buf[i].step--;
					}
				} else if(g_pwm.buf[i].stat == 3) {
					/** keep **/
				} else if(g_pwm.buf[i].stat == 4) {
					//---on 
					g_pwm.buf[i].stat = 0;
					g_pwm.buf[i].step = PWM_DUTY_MAX;
					//g_ledpwmArray_on[i]();
				} else if(g_pwm.buf[i].stat == 5)  {
					//---off
					g_pwm.buf[i].stat = 0;
					g_pwm.buf[i].step = 0;
					//g_ledpwmArray_off[i]();
				} else if(g_pwm.buf[i].stat == 6) {
					#if	0
					//---blink
					if(g_pwm.buf[i].step == 0) {
						g_pwm.buf[i].step = g_pwm.buf[i].step_bak;
//						ledpwmArray_toggle[i]();
					} else {
						g_pwm.buf[i].step--;
					}
					#endif
				} else {
					/** nothing **/
				}
			}
			#endif
			
			#if	1
			for(i = 0; i < CPORT_NUM; i++) {
				if(g_ledport.buf[i].stat == 0) {
					/** do nothing **/
				} else if(g_ledport.buf[i].stat == 1) {
					/** high **/
					//g_ledportArray_H[i]();
				} else if(g_ledport.buf[i].stat == 2) {
					/** low **/
					//g_ledportArray_L[i]();
				} else if (g_ledport.buf[i].stat == 3) {
					/** high/low - low **/
					if(g_ledport.buf[i].wide_L == 0) {	//---状态切换
						g_ledport.buf[i].wide_L = g_ledport.buf[i].wide_L_bak;
						
						g_ledport.buf[i].stat = 4;					
						g_ledportArray_H[i]();
					} else {
						g_ledport.buf[i].wide_L--;
					}
				} else if (g_ledport.buf[i].stat == 4) {
					/** high/low - high **/
					if(g_ledport.buf[i].wide_H == 0) {		//---状态切换
						g_ledport.buf[i].wide_H = g_ledport.buf[i].wide_H_bak;
						
						g_ledport.buf[i].stat = 3;			
						g_ledportArray_L[i]();
					} else {
						g_ledport.buf[i].wide_H--;
					}
				} else {
				}
			}
			#endif
		}
	}
}

/********************************************************************/
bit uart_Tx_busy = 0;

void uart1_Send(void)
{
	u8 ch;
	
	if(uart_Tx_busy) return;
	if(charQueueOut_irq(&g_charTxQueue, &ch) == TRUE) {
		SBUF = ch;
		S2BUF = ch;
		uart_Tx_busy = 1;	
    }
}

//串口发送接收中断函数
void Uart1_Isp(void) interrupt 4
{
	u8 ch;
    if(RI) {   //收到数据
   
        RI = 0;   //清中断请求
		ch = SBUF;
		S4BUF = ch;
        MCHARQUE_IN(g_charRxQueue, ch);
		uart_Rx_Tmr = 0;
    }
    if(TI) {     //发送完一字节数据
   
        TI = 0;
        uart_Tx_busy = 0;  //清正在发送标志
    }
}
/*********************************************************************/

//串口2发送接收中断函数
void Uart2_Isp(void) interrupt 8
{
#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3
	
	u8	ch;
	if (S2CON & S2RI) {
        S2CON &= ~S2RI;         //清除S2RI位
        ch = S2BUF;             //取串口数据
		S4BUF = ch;
        //P2 = (S2CON & S2RB8);   //P2.2显示校验位
		MCHARQUE_IN(g_charRxQueue, ch);
		uart_Rx_Tmr = 0;
    }
    if (S2CON & S2TI) {
        S2CON &= ~S2TI;         //清除S2TI位
		uart_Tx_busy = 0;  //清正在发送标志
        //busy = 0;               //清忙标志
    }
}
/*********************************************************************/
#if	0
//串口4发送接收中断函数
void Uart4_Isp(void) interrupt 18
{
#define S4RI  0x01              //S4CON.0
#define S4TI  0x02              //S4CON.1
#define S4RB8 0x04              //S4CON.2
#define S4TB8 0x08              //S4CON.3

	u8 ch;
    if (S4CON & S4RI) {
        S4CON &= ~S4RI;         //清除S4RI位
        ch = S4BUF;             //P0显示串口数据
        P2 = (S4CON & S4RB8);   //P2.2显示校验位
    }
    if (S4CON & S4TI {
        S4CON &= ~S4TI;         //清除S4TI位
        //busy = 0;               //清忙标志
    }
}
#endif
/*********************************************************************/