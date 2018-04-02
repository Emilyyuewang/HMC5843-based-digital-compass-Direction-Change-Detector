/*
 * SPI.c
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>

void CS_HIGH(void)
{
	P2OUT|=1<<7;
}

void CS_LOW(void)
{
	P2OUT&=~(1<<7);
}

void SPI_INIT(void)
{
	P2OUT|=(1<<7);/* Set P2.7 to High */
	P2DIR|=(1<<7);/* Select P2.7 to CS signal */

	P3OUT|=1|(1<<1)|(1<<2);
	P3DIR|=1|(1<<2);
	P3SEL|=1|(1<<1)|(1<<2); /* Assign SPI pins to USCI_B0 P3.0 MOSI, P3.1 MISO, P3.2 SCK */

	UCB0CTL1 |= UCSWRST; // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_0 + UCSYNC; // SPI Master
	UCB0CTL1 = UCSSEL__SMCLK|UCSWRST; // Use SMCLK, keep SW reset
	UCB1BR0 = 1; // fSCL = SMCLK/1
	UCB1BR1 = 0;
	UCB1CTL1 &= ~UCSWRST; // Clear SW reset, resume operation
}

unsigned char SPI_TX_BYTE(unsigned char DATA)
{
	UCB1TXBUF = DATA; // Load TX buffer
	while(!(UCB1IFG& UCTXIFG)){}
	while(!(UCB1IFG& UCRXIFG)){}
	return UCB1RXBUF; // Get RX data;
}

unsigned char SPI_RX_BYTE(unsigned char DATA)
{
	return SPI_TX_BYTE(DATA);
}

void SPI_TX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len)
{
	unsigned int i;
	while(!(UCB1IFG& UCTXIFG)){}
	for(i=0;i<len;i++)
	{
		SPI_TX_BYTE(DATA[i]);
	}
}
void SPI_RX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len)
{
	unsigned int i;
	for(i= 0; i< len-1;i++)
	{
		DATA[i]= SPI_RX_BYTE(0x00);
	}
}
