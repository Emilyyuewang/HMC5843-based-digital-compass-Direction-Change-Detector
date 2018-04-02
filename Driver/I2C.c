/*
 * I2C.c
 *
 *  Created on: 2014��7��26��
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

	UCB1CTL1 |= UCTR;// дģʽ
	UCB1CTL1 |= UCTXSTT;// ��������λ��д�����ֽ�
	UCB1TXBUF = REG_ADDR;           // �����ֽڵ�ַ
	// �ȴ�UCTXIFG=1��UCTXSTT=0 ͬʱ�仯�ȴ�һ����־λ����
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

	UCB1CTL1 |= UCTR;                // дģʽ
	UCB1CTL1 |= UCTXSTT;             // ��������λ��д�����ֽ�

	UCB1TXBUF = REG_ADDR;           // �����ֽڵ�ַ
	// �ȴ�UCTXIFG=1��UCTXSTT=0 ͬʱ�仯�ȴ�һ����־λ����
	while(!(UCB1IFG& UCTXIFG)){}

	UCB1CTL1 &= ~UCTR;               // ��ģʽ
	UCB1CTL1 |= UCTXSTT;             // ��������λ�Ͷ������ֽ�

	while(UCB1CTL1& UCTXSTT);       // �ȴ�UCTXSTT=0
	// ����Ӧ�� UCNACKIFG = 1

	for(i= 0; i< len-1;i++)
	{
		DATA[i]= I2C_RX_BYTE();
	}

	UCB1CTL1 |= UCTXSTP;             // �ڽ������һ���ֽ�֮ǰ����ֹͣλ

	DATA[len-1] = I2C_RX_BYTE();// ��ȡ���һ���ֽ�����

	while( UCB1CTL1& UCTXSTP );
}
