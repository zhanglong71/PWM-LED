#ifndef __DRIVER_H__
#define __DRIVER_H__


int sysProcess(msg_t *val);

u8 phrase_command(charQueue_t *src);
u8 get_command(charQueue_t *src, u8 *array);
void pwmPort_Init(void);

void Uart_Init();
void Uart2_Init();
void Uart4_Init();
void timer0_Init(void);

void led_test(u8 arg);

#endif
