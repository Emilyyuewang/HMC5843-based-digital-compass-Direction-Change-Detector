/*
 * ADC.c
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include "HW.h"

void Inital_TA0(void)
{
	TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
	TA0CCR0 = 16384;
	TA0CTL = TASSEL_1 + MC__UP + TACLR;       // ACLK, up to mode
}

void delay_ns(unsigned int ns)
{
	while(ns--)
		__delay_cycles(16);
}


void delay_us(unsigned int us)
{
	while(us--)
		__delay_cycles(16000);
}

void delay_ms(unsigned int ms)
{
	while(ms--)
		__delay_cycles(16000000);
}
