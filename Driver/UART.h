/*
 * UART0.h
 *
 *  Created on: 2014Äê7ÔÂ23ÈÕ
 *      Author: Kevin
 */

#ifndef __UART_H__
#define __UART_H__

typedef enum  _command
		{
			Shutdown_All,
			SET_20mA,
			SET_2mA,
			SET_200uA,
			Command_Error,
			System_Busy
		}COMMAND;

extern void UART0_Init(void);
extern void UART0_TX_BUFFER(unsigned char *p_buffer, unsigned int size);
extern void UART0_RX_BUFFER(unsigned char *p_buffer, unsigned int size);

extern void UART1_Init();
extern void UART1_TX_BUFFER(unsigned char *p_buffer, unsigned int size);
extern void UART1_RX_BUFFER(unsigned char *p_buffer, unsigned int size);

extern void UART2_Init();
extern void UART2_TX_BUFFER(unsigned char *p_buffer, unsigned int size);
extern void UART2_RX_BUFFER(unsigned char *p_buffer, unsigned int size);


#endif /* UART_H_ */
