#ifndef __MACRO_H__
#define __MACRO_H__

/** process charQueue_t **/

#define	MCHARQUE_INIT(q) do{\
						q->tail = q->head = 0;\
								}while(0);
#if	0
#define	MCHARQUE_IN(q, ch) do{\
								q->buf[q->tail]      = ch;\
								q->tail = (q->tail + 1) % CHARQUEUESIZE;\
								}while(0);
#else
#define	MCHARQUE_IN(q, ch) do{\
								q.buf[q.tail]      = ch;\
								q.tail = (q.tail + 1) % CHARQUEUESIZE;\
								}while(0);
#endif

#define	MCHARQUE_OUT(q, ch) do{\
								q->buf[q->tail]      = ch;\
								q->tail = (q->tail + 1) % CHARQUEUESIZE;\
								}while(0);

/************************************************************************/
#define	MPWMTMR_SET(id, val) do {g_pwm.buf[id] = val;} while(0);
/************************************************************************/
//sfr P4    = 0xC0;
//嘴巴
sbit LED_P1_CRL = P2^0;		//---位置(形状)控制。低有效
sbit LED_P2_CRL = P4^4;
sbit LED_P3_CRL = P4^3;
sbit LED_PWM3_CRL = P2^1;	//---颜色控制。高->亮
sbit LED_PWM4_CRL = P2^2;
sbit LED_PWM5_CRL = P2^3;

//耳朵
sbit LED_R_CRL	 = P4^7;	//高有效
sbit LED_G_CRL	 = P1^2;
sbit LED_B_CRL	 = P1^3;
sbit LED_PWM6_CRL = P0^7;	//高->亮

//眼睛
#if	0
//---v1
sbit LED_R1_CRL	 = P4^6;	//高有效
sbit LED_G1_CRL	 = P4^5;
sbit LED_B1_CRL	 = P2^7;
sbit LED_PWM7_CRL = P0^6;	//高->亮

sbit LED_PWM2_CRL = P3^7;
#endif

#if	1
//---v2
sbit LED_P4_CRL = P4^6;		//---位置(形状)控制。低有效
sbit LED_P5_CRL = P4^5;
sbit LED_P6_CRL = P0^4;

sbit LED_PWM7_CRL = P0^6;	//---颜色控制。高->亮
sbit LED_PWM2_CRL = P3^7;
sbit LED_B1_CRL = P2^7;		//---作为PWM输出
#define	LED_PWM1_CRL	(LED_B1_CRL)
#endif

/*************************************************************************/
/** #define	MLEDPORT_SETSTAT(x, y)	ledport_setStat(x, y) **/

#define	MLEDPORT_SETSTAT(x, y)	do{\
	if(x < 9) {\
		EA = 0;\
	    if(y == 1) {\
	        g_ledport.buf[x].stat = 0;\
	        g_ledportArray_H[x]();\
	    } else if(y == 2) {\
	        g_ledport.buf[x].stat = 0;\
	        g_ledportArray_L[x]();\
	    } else if(y == 3) {\
	        g_ledport.buf[x].stat = 3;\
	        g_ledportArray_L[x]();\	
	    } else if(y == 4) {\
	        g_ledport.buf[x].stat = 4;\
	        g_ledportArray_H[x]();\
	    } else {\
	    	g_ledport.buf[x].stat = y;\
	    }\
		EA = 1;\
	}\
								}while(0)\
/*************************************************************************/
#define	MLEDPORT_SETTMR(x, __H, __L)	do{\
	if(x < 9) {\
		EA = 0;\
		g_ledport.buf[x].wide_H = __H;\
		g_ledport.buf[x].wide_H_bak = __H;\
										\
		g_ledport.buf[x].wide_L = __L;\
		g_ledport.buf[x].wide_L_bak = __L;\
		EA = 1;\
	}\
								}while(0)\
/*************************************************************************/
/** #define	MPWMTMR_SETSTAT(x, y)	pwdTmr_set(x, y) **/							
								
#define	MPWMTMR_SETSTAT(x, y)	do{\
	if(x == 1) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM1_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM1_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 2) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM2_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM2_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 3) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM3_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM3_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 4) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM4_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM4_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 5) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM5_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM5_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 6) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM6_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM6_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else if(x == 7) {\
		if(y == 4) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM7_CRL = PWM_ON;\
		} else if(y == 5) {\
			g_pwm.buf[x].stat = 0;\
			LED_PWM7_CRL = PWM_OFF;\
		} else {\
			g_pwm.buf[x].stat = y;\
		}\
	} else {/** nothing **/}\
								}while(0)\
/*************************************************************************/
/** #define	MPWMTMR_SETWIDE(x, y)	pwdTmr_setWide(x, y) **/

#define	MPWMTMR_SETWIDE(x, y)	do{\
    if((x < 8) && (x >= 1)) {\
		if(y <= PWM_DUTY_MAX) {\
			EA = 0;\
			g_pwm.buf[x].step = y;\
			EA = 1;\
		}\
    }\
								}while(0)\
/*************************************************************************/
#endif
