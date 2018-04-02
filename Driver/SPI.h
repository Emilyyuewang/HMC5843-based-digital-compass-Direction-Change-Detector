/*
 * SPI.h
 *
 *  Created on: 2014Äê7ÔÂ26ÈÕ
 *      Author: Kevin
 */

#ifndef __SPI_H__
#define __SPI_H__

extern void CS_HIGH(void);
extern void CS_LOW(void);
extern void SPI_INIT(void);
extern unsigned char SPI_TX_BYTE(unsigned char DATA);
extern unsigned char SPI_RX_BYTE(unsigned char DATA);
extern void SPI_TX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len);
extern void SPI_RX(unsigned char ADDR,unsigned char REG_ADDR,unsigned char *DATA,unsigned int len);

#endif /* __SPI_H__ */
