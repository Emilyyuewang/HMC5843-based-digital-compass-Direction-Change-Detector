/*
 * ADC.c
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>

void ADC_Init()
{
	ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
	ADC12CTL1 = ADC12SHP;                     // Use sampling timer
	//ADC12IE = 0x01;                         // Enable interrupt
	__delay_cycles(100);                      // delay to allow Ref to settle
	ADC12CTL0 |= ADC12ENC;
	P6SEL |= 0x01;                            // P6.0 ADC option select
}

void ADC_Read(unsigned int ch)
{
	ADC12CTL0 &= ~ADC12SC;
	ADC12MCTL0 = ADC12INCH_0;
	__delay_cycles(100);
	ADC12CTL0 |= ADC12SC;                     // Start sampling/conversion
	while(!(ADC12IFG&ADC12IFG0));
}

void Temp_Sensor_Init()
{
	REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to
	                                            // ADC12_A ref control registers
	ADC12CTL0 = ADC12SHT0_8 | ADC12REFON | ADC12ON | ADC12MSC;
	                                            // Internal ref = 1.5V
	ADC12CTL1 = ADC12SHP | ADC12CONSEQ_2;       // enable sample timer
	ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
	__delay_cycles(100);                       // delay to allow Ref to settle
	ADC12CTL0 |= ADC12ENC;
	//ADC12IE|=ADC12IE10;

}

float Temp_Sensor_Get_f()
{
	#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
	#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C
	unsigned int temp;
	float temperatureDegC;
	ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
	ADC12CTL0 &= ~ADC12SC;
	ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
	while(ADC12IFG&ADC12IFG10){}
	temp = ADC12MEM0;
	temperatureDegC = (float)(((long)temp - CALADC12_15V_30C) * (85 - 30))/(CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
	return temperatureDegC;
}

double Temp_Sensor_Get_d()
{
	#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
	#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C
	unsigned int temp;
	double temperatureDegC;
	ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense i/p
	ADC12CTL0 &= ~ADC12SC;
	ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
	while(ADC12IFG&ADC12IFG10){}
	temp = ADC12MEM0;
	temperatureDegC = (double)(((long)temp - CALADC12_15V_30C) * (85 - 30))/(CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
	return temperatureDegC;
}
