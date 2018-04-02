/*
 * RTC.c
 *
 *  Created on: 2014Äê7ÔÂ23ÈÕ
 *      Author: Kevin
 */

#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include "RTC.h"
#include "HW.h"

void RTC_Init(void)
{
	RTCCTL1=0x22;/* Calendar mode, event happen every midnight */
	RTCCTL2=0x00;/* Clear calibration */
	RTCCTL3=0x00;/* Clear RTCCLK output */

}

int RTC_Set_Datetime(t_DATETIME *Datetime)
{
	RTCYEARL=Datetime->year;
	RTCYEARH=(Datetime->year)>>8;
	RTCMON=Datetime->month;
	RTCDAY=Datetime->day;
	RTCHOUR=Datetime->hour;
	RTCMIN=Datetime->minute;
	RTCSEC=Datetime->second;
	return 0;
}

int RTC_Get_Datetime(t_DATETIME *Datetime)
{
	if(RTCCTL1&0x10)/* Check if the calendar is ready */
	{
		Datetime->year=RTCYEARL|(RTCYEARH<<8);
		Datetime->month=RTCMON;
		Datetime->day=RTCDAY;
		Datetime->hour=RTCHOUR;
		Datetime->minute=RTCMIN;
		Datetime->second=RTCSEC;
		return 0;
	}
	return -1;
}

int RTC_Set_Date(t_DATE *Date)
{
	RTCYEARL=Date->year;
	RTCYEARH=(Date->year)>>8;
	RTCMON=Date->month;
	RTCDAY=Date->day;
	return 0;
}

int RTC_Get_Date(t_DATE *Date)
{
	if(RTCCTL1&0x10)/* Check if the calendar is ready */
	{
		Date->year=RTCYEARL|(RTCYEARH<<8);
		Date->month=RTCMON;
		Date->day=RTCDAY;
		return 0;
	}
	return -1;
}

int RTC_Set_Time(t_TIME *Time)
{
	RTCHOUR=Time->hour;
	RTCMIN=Time->minute;
	RTCSEC=Time->second;
	return 0;
}

int RTC_Get_Time(t_TIME *Time)
{
	if(RTCCTL1&0x10)/* Check if the calendar is ready */
	{
		Time->hour=RTCHOUR;
		Time->minute=RTCMIN;
		Time->second=RTCSEC;
		return 0;
	}
	return -1;
}
