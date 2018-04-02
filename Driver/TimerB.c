/*
 * ADC.c
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>

//P3.5 3.6 7.4, TB0.5 0.6 0.2
void Inital_TB0(void)
{
	P3DIR |= (1<<5)|(1<<6);
	P3DS = (1<<5)|(1<<6);
	P3SEL |= (1<<5)|(1<<6);

	P7DIR |= (1<<4);
	P7DS = (1<<4);
	P7SEL |= (1<<4);

	TB0CCTL0 = CCIE;                          // TBCCR0 interrupt enabled
	TB0CCR0 = 16150;
	TB0CTL = TASSEL_2 + MC__UP + TACLR;       // SMCLK, up to mode

	TB0CCTL5 = OUTMOD_7;
	TB0CCTL6 = OUTMOD_7;
	TB0CCTL2 = OUTMOD_7;

	TB0CCR5 = 0;
	TB0CCR6 = 0;
	TB0CCR2 = 0;
}
