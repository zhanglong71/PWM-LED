#ifndef __GLOBAL_H__
#define __GLOBAL_H__

extern u16 g_tick;
extern	msgq_t  g_msgq;
extern	fstack_t g_fstack;
extern	Timer_t g_timer[TIMER_NUM];

extern actionQueue_t g_actionQueue;
//extern charQueue_t g_charQueue;
extern charQueue_t g_charTxQueue;
extern charQueue_t g_charRxQueue;
extern charQueue_t g_charTmpQueue;		//for Rx and process

extern pwmArray_t g_pwm;
extern portArray_t g_ledport;

extern code paction_t_0 g_ledpwmArray_off[];
extern code paction_t_0 g_ledpwmArray_on[];
//extern code paction_t_0 g_ledpwmArray_toggle[];

extern	code paction_t_0 g_ledportArray_L[];
extern	code paction_t_0 g_ledportArray_L_irq[];
extern	code paction_t_0 g_ledportArray_H[];
extern	code paction_t_0 g_ledportArray_H_irq[];

//extern xdata paction_t_1 g_partActionTable[];
//extern code paction_t_1 g_partActionTable[];
//extern paction_t_1 g_partActionTable[];
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if	0
extern	code paction_t_0 mouseColor_tab[];
extern	code paction_t_0 mouseBreathAscend_tab[];
extern	code paction_t_0 mouseBreathDecline_tab[];
extern	code paction_t_0 mouseShape_tab[];

extern	code paction_t_0 eyeColor_tab[];
extern	code paction_t_0 eyeBreathAscend_tab[];
extern	code paction_t_0 eyeBreathDecline_tab[];
extern	code paction_t_0 eyeShape_tab[];

extern	code paction_t_0 earColor_tab[];
extern	code paction_t_0 earBreathAscend_tab[];
extern	code paction_t_0 earBreathDecline_tab[];
#endif
//------------------------
extern	code paction_t_0 g_part_color_expire[4][4][16];
extern	code paction_t_0 g_part_shape[4][8];

#endif