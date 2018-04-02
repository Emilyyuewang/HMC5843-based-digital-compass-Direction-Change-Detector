/*
 * UART0.c
 *
 *  Created on: 2014Äê7ÔÂ23ÈÕ
 *      Author: Kevin
 */
#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include "UART.h"

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	switch(__even_in_range(UCA0IV,12))
	{
		case 0: break; // Vector 0: No interrupts
		case 2: break; // Vector 2: ALIFG
		case 4: break; // Vector 4: NACKIFG
		case 6: break; // Vector 6: STTIFG
		case 8: break; // Vector 8: STPIFG
		case 10: break; // Vector 10: RXIFG
		case 12: // Vector 12: TXIFG
			break;
		default: break;
	}
}

#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	switch(__even_in_range(UCA1IV,12))
	{
		case 0: break; // Vector 0: No interrupts
		case 2: break; // Vector 2: ALIFG
		case 4: break; // Vector 4: NACKIFG
		case 6: break; // Vector 6: STTIFG
		case 8: break; // Vector 8: STPIFG
		case 10: break; // Vector 10: RXIFG
		case 12: // Vector 12: TXIFG
		break;
		default: break;
	}
}

#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
	switch(__even_in_range(UCB1IV,12))
	{
		case 0: break; // Vector 0: No interrupts
		case 2: break; // Vector 2: ALIFG
		case 4: break; // Vector 4: NACKIFG
		case 6: break; // Vector 6: STTIFG
		case 8: break; // Vector 8: STPIFG
		case 10: break; // Vector 10: RXIFG
		case 12: // Vector 12: TXIFG
		break;
		default: break;
	}
}

void UART0_Init(void)
{
  P3SEL |= (1<<3)|(1<<4);                             // P3.3,4 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 6;                              // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRF3 + UCOS16;               // Modln UCBRSx=1, over sampling
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void UART0_TX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  for(i=0;i<size;i++)
  {
	while (!(UCA0IFG&UCTXIFG));
    UCA0TXBUF=*(p_buffer+i);
  }
}

void UART0_RX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  while (!(UCA0IFG&UCRXIFG));
  for(i=0;i<size;i++)
  {
    p_buffer[i]=UCA0RXBUF;
    while (!(UCA0IFG&UCRXIFG));
  }
}

void UART1_Init()
{
	P4SEL |= BIT5+BIT4;                        // P4.4,5 = USCI_A1 TXD/RXD
	UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA1CTL1 |= UCSSEL_2;                     // SMCLK
	UCA1BR0 = 6;                              // 1MHz 9600 (see User's Guide)
	UCA1BR1 = 0;                              // 1MHz 9600
	UCA1MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
	// over sampling
	UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

	 // __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
	  //__no_operation();                         // For debugger
}

void UART1_TX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  for(i=0;i<size;i++)
  {
	while (!(UCA1IFG&UCTXIFG));
    UCA1TXBUF=*(p_buffer+i);
  }
}

void UART1_RX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  while (!(UCA1IFG&UCRXIFG));
  for(i=0;i<size;i++)
  {
    p_buffer[i]=UCA1RXBUF;
    while (!(UCA1IFG&UCRXIFG));
  }
}

void UART2_Init()
{
	P4SEL |= BIT5+BIT4;                        // P4.4,5 = USCI_A1 TXD/RXD
	UCB1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCB1CTL1 |= UCSSEL_2;                     // SMCLK
	UCB1BR0 = 6;                              // 1MHz 9600 (see User's Guide)
	UCB1BR1 = 0;                              // 1MHz 9600
	UCA1MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
	// over sampling
	UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	UCB1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

	 // __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
	  //__no_operation();                         // For debugger
}

void UART2_TX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  for(i=0;i<size;i++)
  {
	while (!(UCB1IFG&UCTXIFG));
    UCB1TXBUF=*(p_buffer+i);
  }
}

void UART2_RX_BUFFER(unsigned char *p_buffer, unsigned int size)
{
  unsigned int i;
  while (!(UCB1IFG&UCRXIFG));
  for(i=0;i<size;i++)
  {
    p_buffer[i]=UCB1RXBUF;
    while (!(UCB1IFG&UCRXIFG));
  }
}
