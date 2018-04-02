#include <stdio.h>
#include <msp430.h>
#include <stdlib.h>
#include <string.h>
#include "./Driver/IO.h"
#include "./OLED/OLED.h"
#include "./HMC5843/HMC5841.h"
#include "./KEY/KEY.h"
#include "math.h"
#include "Debug.h"

#define PI   3.14159
unsigned short R=0,G=0,B=0;
short x=0;
short y=0;
short z=0;


unsigned int MCU_Temp=0;
char str_buf[20];
t_DATETIME Datetime;
unsigned char clk_adj=0;

unsigned int TACount=0,TACR=0;


int main(void) {

    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer

    /*Initialize the clock*/
    initClocks();

    /*LED Initialize*/
    P1DIR |= 0x01;
    P1DS=0x01;
    P1OUT&=~0x01;

    P4DIR |= (1<<7);
    P4DS=1<<7;
    P4OUT&=~(1<<7);

    Inital_TA0();
    Inital_TB0();
    RTC_Init();
    //SPI_INIT();
    //Temp_Sensor_Init();
    //UART1_Init();
    I2C_INIT(0x78); //initiate I2C
    OLED_Init();    //initiate OLED
    OLED_Fill(0x00);
    init_hmc5843(); //initiate HMC5843
    KEY_Init();

    // present current time
    Datetime.year=2016;
    Datetime.month=11;
    Datetime.day=22;
    RTC_Set_Datetime(&Datetime);
    __bis_SR_register(GIE);//enable general interrupt

	while(1)
	{
		HMC5843_Read_Data(&x,&y,&z);
		RTC_Get_Datetime(&Datetime);

		sprintf(str_buf+2,"x:%d",x);
		Debug_Display(0,str_buf);

		sprintf(str_buf+2,"y:%d",y);
		Debug_Display(1,str_buf);

		sprintf(str_buf+2,"z:%d",z);
		Debug_Display(2,str_buf);

		sprintf(str_buf+2,"angle: %.2f",(atan ((double)y/x)) *180.0 / PI);//get the angle from x,y value
		Debug_Display(3,str_buf);

		sprintf(str_buf+2,"%.2f",((double)y)/x);//get the division value to do testing
		Debug_Display(4,str_buf);


		sprintf(str_buf+2,"%04d %02d %02d",Datetime.year,Datetime.month,Datetime.day);//get year,month,date.
		Debug_Display(5,str_buf);//get year,month,date

		sprintf(str_buf+2,"%02d:%02d:%02d",Datetime.hour,Datetime.minute,Datetime.second);//get time
		Debug_Display(6,str_buf);//present time
	}
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	P4OUT^=(1<<7);
	TACount=TACR;
	TACR=0;
}

// Timer B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{
	TACR++;
}

#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR(void)
{
	if(UCSCTL7&0x000F)
		UCSCTL7=0;
	P1OUT |= 0x01;
}

#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  switch(__even_in_range(DMAIV,16))
  {
    case 0: break;
    case 2:                                 // DMA0IFG = DMA Channel 0
                              // Toggle P1.0 - PLACE BREAKPOINT HERE AND CHECK DMA_DST VARIABLE
      break;
    case 4: break;                          // DMA1IFG = DMA Channel 1
    case 6: break;                          // DMA2IFG = DMA Channel 2
    case 8: break;                          // DMA3IFG = DMA Channel 3
    case 10: break;                         // DMA4IFG = DMA Channel 4
    case 12: break;                         // DMA5IFG = DMA Channel 5
    case 14: break;                         // DMA6IFG = DMA Channel 6
    case 16: break;                         // DMA7IFG = DMA Channel 7
    default: break;
  }
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	switch(__even_in_range(ADC12IV,36))
	{
	case 6:
		//ADC12MEM0 interrupt
		break;
	default:break;
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	switch(__even_in_range(P1IV,16))
	{
	case 4:
		//KEY_Scan_1();
		switch(clk_adj)
		{
		case 0:
			Datetime.year++;
			break;
		case 1:
			Datetime.month++;
			break;
		case 2:
			Datetime.day++;
			break;
		case 3:
			Datetime.hour++;
			break;
		case 4:
			Datetime.minute++;
			break;
		case 5:
			Datetime.second=0;
			break;
		default:
			break;
		}
		RTC_Set_Datetime(&Datetime);
		break;
	default:break;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
	switch(__even_in_range(P2IV,16))
	{
	case 4:
		//KEY_Scan_2();
		Debug_Switch();
		clk_adj=(++clk_adj)%8;
		break;
	default:break;
	}
}
