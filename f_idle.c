

#include	"STC15W4K60S4.H"

#include	"const.h"
#include	"ptype.h"
#include 	"macro.h"
#include 	"global.h"
#include 	"arch.h"
#include 	"driver.h"
#include	"main.h"

#include    "f_idle.h"

void* f_idle(void *pMsg)
{
    switch(((msg_t *)pMsg)->msgType) 
	{
	case CACT_OVER:
		break;

	case CMSG_TMR:
		break;
	
	default:
		break;
	}
	
    return  (void*)0;
}
