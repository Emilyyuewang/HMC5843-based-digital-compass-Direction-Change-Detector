/*
 * Debug.c
 *
 *  Created on: 2014Äê7ÔÂ29ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include ".\OLED\OLED.h"

static unsigned char debug_sel=0x01;

void Debug_Switch(void)
{
	debug_sel=debug_sel<<1;
	if(debug_sel==0)
		debug_sel=0x01;
}

void Debug_Display(int lcdline,char *str)
{
    if(debug_sel&(0x01<<lcdline))
    	str[0]='>';
    else
    	str[0]=' ';
    str[1]=' ';
    OLED_ShowStr(0,lcdline,str,1);
}
