/*
 * UCS.c
 *
 *  Created on: 2014Äê7ÔÂ23ÈÕ
 *      Author: Kevin
 */

#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include "UCS.h"
#include "HW.h"

void initClocks(void)
{
	P5SEL|=(1<<4)|(1<<5)|(1<<3)|(1<<2);
	P5DIR|=(1<<5)|(1<<3);
	UCSCTL5=0x0000;/*Set all divider to 1*/
	UCSCTL6=0x0001;/*Turn on XT1 and XT2, XT1 in LF mode, XT2 in 4M-8M mode*/
	__bis_SR_register(SCG0);
	UCSCTL1=0x0070;
	UCSCTL2=0x0003;/*FLLCLK feed back divider set to 2, multiplier set to 4*/
	UCSCTL3=0x0050;/*Select PLLREF=XT2*/
	__bic_SR_register(SCG0);
	UCSCTL4=0x0033;/*Select MCLK to XT2, SMCLK to DCOCLK, ACLK from XT1*/
	UCSCTL7=0x0000;/*Clear fault flags*/
}
