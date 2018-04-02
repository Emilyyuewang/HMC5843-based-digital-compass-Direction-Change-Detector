/*
 * HMC5843.c
 *
 *  Created on: 2016
 *      Author: emily
 */

#include <stdio.h>
#include <msp430.h>
#include "../Driver/IO.h"

#define HMC5843_ADDR               0x3C
// config_Address
#define HMC5843_RA_CONFIG_A        0x00
#define HMC5843_RA_CONFIG_B        0x01
#define HMC5843_RA_MODE            0x02
#define HMC5843_RA_DATAX_H         0x03
#define HMC5843_RA_DATAX_L         0x04
#define HMC5843_RA_DATAY_H         0x05
#define HMC5843_RA_DATAY_L         0x06
#define HMC5843_RA_DATAZ_H         0x07
#define HMC5843_RA_DATAZ_L         0x08
#define HMC5843_RA_STATUS          0x09


void init_hmc5843(){
	unsigned char temp=0;
	I2C_INIT(HMC5843_ADDR);
	I2C_TX(HMC5843_ADDR,HMC5843_RA_MODE,&temp,1);
	//I2C_TX(HMC5843_ADDR,HMC5843_RA_CONFIG_A,&temp,1);
	I2C_TX(HMC5843_ADDR,HMC5843_RA_CONFIG_B,&temp,1);
}

unsigned char HMC5843_Read_Status(){

	unsigned char temp=0;
	I2C_RX(HMC5843_ADDR,HMC5843_RA_STATUS,&temp,1);
	return temp;
}



void HMC5843_Read_Data(unsigned short *x,unsigned short *y,unsigned short *z){
	  unsigned char temp[2]={0,0};
      I2C_RX(0x3C,0x03,temp,2);
      *x=temp[1]|temp[0]<<8;

      I2C_RX(0x3C,0x05,temp,2);
      *y=temp[1]|temp[0]<<8;

      I2C_RX(0x3C,0x07,temp,2);
      *z=temp[1]|temp[0]<<8;
}

void HMC5843_Gener_Data(unsigned short *x,unsigned short *y,unsigned short *z){
	unsigned char temp[2]={0,0};
	I2C_TX(0x3D,0x03,&temp[0],1);
	I2C_TX(0x3D,0x04,&temp[1],1);
	*x=temp[1]|temp[0]<<8;

	I2C_TX(0x3D,0x05,&temp[0],1);
	I2C_TX(0x3D,0x06,&temp[1],1);
	*y=temp[1]|temp[0]<<8;

	I2C_TX(0x3D,0x07,&temp[0],1);
	I2C_TX(0x3D,0x08,&temp[1],1);
	*z=temp[1]|temp[0]<<8;
}
