/*
 * I2C.c
 *
 *  Created on: 2014年7月26日
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>

void I2C_INIT(unsigned char slave_addr)
{
	P4SEL |= (1<<1)|(1<<2); // Assign I2C pins to USCI_B1 P4.1,P4.2
	UCB1CTL1 |= UCSWRST; // Enable SW reset
	UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
	UCB1CTL1 = UCSSEL__SMCLK|UCSWRST; // Use SMCLK, keep SW reset
	UCB1BR0 = 160; // fSCL = SMCLK/160
	UCB1BR1 = 0;
	UCB1I2CSA = slave_addr>>1; // Slave Address
	UCB1CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
}

void I2C_TX_BYTE(unsigned char DATA)
{
	UCB1TXBUF = DATA; // Load TX buffer
	while(!(UCB1IFG& UCTXIFG)){}
}

unsigned char I2C_RX_BYTE(void)
{
	while(!(UCB1IFG& UCRXIFG)){}
	return UCB1RXBUF; // Get RX data;
}

void I2C_TX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len)
{
	unsigned int i;
	UCB1I2CSA = ADDR>>1;

	UCB1CTL1 |= UCTR;// 写模式
	UCB1CTL1 |= UCTXSTT;// 发送启动位和写控制字节
	UCB1TXBUF = REG_ADDR;           // 发送字节地址
	// 等待UCTXIFG=1与UCTXSTT=0 同时变化等待一个标志位即可
	while(!(UCB1IFG& UCTXIFG)){}
	for(i=0;i<len;i++)
	{
		I2C_TX_BYTE(DATA[i]);
	}
	UCB1CTL1 |= UCTXSTP;
	while (UCB1CTL1 & UCTXSTP){} // Ensure stop condition got sent
}

void I2C_RX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len)
{
	unsigned int i;
	UCB1I2CSA = ADDR>>1; // Slave Address is 078h

	UCB1CTL1 |= UCTR;                // 写模式
	UCB1CTL1 |= UCTXSTT;             // 发送启动位和写控制字节

	UCB1TXBUF = REG_ADDR;           // 发送字节地址
	// 等待UCTXIFG=1与UCTXSTT=0 同时变化等待一个标志位即可
	while(!(UCB1IFG& UCTXIFG)){}

	UCB1CTL1 &= ~UCTR;               // 读模式
	UCB1CTL1 |= UCTXSTT;             // 发送启动位和读控制字节

	while(UCB1CTL1& UCTXSTT);       // 等待UCTXSTT=0
	// 若无应答 UCNACKIFG = 1

	for(i= 0; i< len-1;i++)
	{
		DATA[i]= I2C_RX_BYTE();
	}

	UCB1CTL1 |= UCTXSTP;             // 在接收最后一个字节之前发送停止位

	DATA[len-1] = I2C_RX_BYTE();// 读取最后一个字节内容

	while( UCB1CTL1& UCTXSTP );
}
