#ifndef __CTYPE_H__
#define __CTYPE_H__


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long	u32;

typedef char s8;
typedef short s16;
typedef long	s32;

typedef	void	(*paction_t_0)(void);
typedef	void	(*paction_t_1)(void* arg);
//typedef	void	(*paction_t_3)(void* arg1, void* arg2, void* arg3);
//typedef	int	(*pfunc_t)(void* arg);
typedef	void*	(*pfunc_t)(void* arg);

typedef struct func_s {
    pfunc_t		func;       /** function **/
    void  *arg;    	/** argument **/
} func_t;

typedef struct func_stack{
	u8		top;
		#define	STACKSIZE	8
	func_t		func[STACKSIZE]; 
} xdata fstack_t;

typedef enum {
	CMSG_NONE,
	CMSG_POWR,
	CMSG_TMR,
	
	CACT_TOUT,	//phrase over
	CACT_OVER,	//all over
	
	CMSG_UARX,	//uart received
	CMSG_UATX,	//uart transported
}msgType_t;

typedef struct msg_s {
	msgType_t msgType;
	
	u8	msgValue;
}xdata msg_t;

typedef struct msg_queue{
	u8	head;
	u8	tail;
	
		#define	QUEUESIZE	8		/** ÏûÏ¢¶ÓÁĞ³¤¶È **/
	msg_t msg[QUEUESIZE];
}xdata msgq_t;

typedef struct Timer_s {
    u16 tick_bak;
    u16 tick;
    msgType_t msgType;                      /** the type of msg when timeout **/
    //unsigned int count;                   /** Is it necessary ? **/
}xdata Timer_t; 

typedef struct charQueue_s {
  
    u8	head;
		u8	tail;
		//u8 flag;
        #define CHARQUEUESIZE 8
    u8 buf[CHARQUEUESIZE];     /** 8 bytes **/
}xdata charQueue_t;

typedef struct action_s {
	
#define CACT_DFLT	0xff	//---ä¸€ä¸ªå‡½æ•°+ä¸€ä¸ªå‚æ•°f(x)
#define CACT_F0F0	0xfe	//---ä¸¤ä¸ªå‡½æ•°ï¼Œéƒ½æ²¡æœ‰å‚æ•°
#define CACT_F000	0xfd	//---ä¸€ä¸ªå‡½æ•°ï¼Œæ²¡æœ‰å‚æ•°
#define CACT_MISC	0xfc	//---!!!

    paction_t_0		func;
    void* actionPara;	/** ¶¯×÷ĞèÒªµÄÆäËü²ÎÊı£¬ÈçVPidxË÷ÒıºÅ **/

    u16 actionTime;	/** ³ÖĞøÊ±¼ä **/
    u8 actionType;	/** ¶¯×÷ÀàĞÍ. ËÆÓëÇ°ÃæµÄ²ÎÊıÓĞÖØµşÖ®ÏÓ£¬ÊÇÒ»¸öÇø±ğ¶¯×÷µÄÒÀ¾İ **/
    //u8 __pad1;		/** ×Ö½Ú¶ÔÆë **/
}xdata action_t;

typedef struct actionQueue_s {
    u8	head;
	u8	tail;
    u8 flag;
	msgType_t stepMsgType;			/** ½×¶ÎÊÂ¼şÍê³ÉÏûÏ¢ **/
	msgType_t overMsgType;			/** ¶ÓÁĞÊÂ¼şÈ«²¿Íê³ÉÏûÏ¢ **/
	Timer_t *timer;
        #define ACTIONQUEUESIZE 16
    action_t buf[ACTIONQUEUESIZE];     /** 16 bytes **/
}xdata actionQueue_t;

typedef struct pwmStat_s {
	/*************************
	 * stat = 
	 * 	0 - do nothing
	 * 	1 - ascend
	 * 	2 - discline
	 *  3 - remain
	 * 	4 - on
	 * 	5 - off
	 *	6 - blink
	 *	7 - 
	 *************************/
	u8	stat;
	u8	step;
	u8	step_bak;
} pwmStat_t;
typedef struct pwmArray_s {
	#define	CPWM_NUM	8
	pwmStat_t buf[CPWM_NUM];
	u8 pwm_duty;
} pwmArray_t;

typedef struct portStat_s {
	u8	wide_L;
	u8	wide_L_bak;
	u8	wide_H;
	u8	wide_H_bak;
	
	u8	scale:4;		//---åˆ†é¢‘
	/**********************
	 * 0 - no nothing
	 * 1 - high
	 * 2 - low
	 * 3 - high(high/low)
	 * 4 - low(high/low)
	 * 5 - 
	 **********************/
	u8	stat:4;			//---çŠ¶æ€æ§åˆ¶
} portStat_t;

typedef struct portArray_s {
	#define	CPORT_NUM	9
	portStat_t buf[CPORT_NUM];
	//u8 pwm_duty;
} xdata portArray_t;

#if	0
/** ç”¨äºä¼ é€’å‚æ•° **/
typedef struct parameter_s {
	u8	color;
	u8	shape;
	u16	expired;
} xdata parameter_t;
#endif

#endif