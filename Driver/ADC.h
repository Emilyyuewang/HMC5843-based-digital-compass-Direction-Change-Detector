/*
 * ADC.h
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */

#ifndef ADC_H_
#define ADC_H_

extern void ADC_Init();
extern void ADC_Read(unsigned int ch);
extern double temperature;
extern void Temp_Sensor_Init();
extern float Temp_Sensor_Get_f();
extern double Temp_Sensor_Get_d();

#endif /* ADC_H_ */
