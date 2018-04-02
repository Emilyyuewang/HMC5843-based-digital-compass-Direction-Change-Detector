/*
 * I2C.h
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */

#ifndef __I2C_H__
#define __I2C_H__

extern void I2C_INIT(unsigned char slave_addr);
extern void I2C_TX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len);
extern void I2C_RX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len);

#endif /* __I2C_H__ */
