/*
 * RTC.h
 *
 *  Created on: 2014Äê7ÔÂ23ÈÕ
 *      Author: Kevin
 */

#ifndef RTC_H_
#define RTC_H_

typedef struct _date{
	unsigned short year;
	unsigned char month;
	unsigned char day;
}t_DATE;

typedef struct _time{
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}t_TIME;

typedef struct _datetime{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
}t_DATETIME;

extern void RTC_Init(void);
extern int RTC_Set_Datetime(t_DATETIME *Datetime);
extern int RTC_Get_Datetime(t_DATETIME *Datetime);
extern int RTC_Set_Date(t_DATE *Date);
extern int RTC_Get_Date(t_DATE *Date);
extern int RTC_Set_Time(t_TIME *Time);
extern int RTC_Get_Time(t_TIME *Time);

#endif /* RTC_H_ */
