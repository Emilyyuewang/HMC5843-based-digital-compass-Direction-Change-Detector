/*
OLED Driver for STM32F103RBT6, using I2C with out ack recieved
*/

extern void OLED_Init(void);
extern void OLED_SetPos(unsigned char x, unsigned char y);
extern void OLED_Fill(unsigned char fill_Data);
extern void OLED_CLS(void);
extern void OLED_ON(void);
extern void OLED_OFF(void);
extern void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
extern void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char n);
extern void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
