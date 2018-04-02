/*
 * KEY.c
 *
 *  Created on: 2014Äê7ÔÂ29ÈÕ
 *      Author: Kevin
 */

#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include "KEY.h"

unsigned char KEY=0x00;
void KEY_Init()//P1.1, P2.1, interrupt enable
{
	P1DIR&=~(1<<1);
	P2DIR&=~(1<<1);
	P1OUT|=(1<<1);
	P2OUT|=(1<<1);
	P1REN|=(1<<1);
	P2REN|=(1<<1);

	P1IE|=1<<1;
	P2IE|=1<<1;
}

void KEY_Scan_1()
{
	volatile unsigned int i;

	if(!(P1IN & (1<<1)))
	for(i=500;i>0;i--);
	if(!(P1IN & (1<<1)))
		KEY|=0x01;
}

void KEY_Scan_2()
{
	volatile unsigned int i;

	if(!(P2IN & (1<<1)))
	for(i=500;i>0;i--);
	if(!(P2IN & (1<<1)))
		KEY|=0x02;
}
