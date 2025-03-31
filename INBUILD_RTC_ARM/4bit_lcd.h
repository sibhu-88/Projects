#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\Header\typedef.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\Header\delay.h"

#define LCD 0x0f<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

void LCD_INIT(void);
void LCD_CMD(U32);
void LCD_DATA(U32);
void LCD_STR(U8 *);
void LCD_INTEGER(S32);
void LCD_FLOAT(float);

void LCD_INIT(void)
{
	IODIR1 |= LCD | RS | RW | E ;
	LCD_CMD(0X01); //CLEAR THE DISPLAY
	LCD_CMD(0X02); //RETURN TO HOME POSITION
	LCD_CMD(0X0C); //DISPLAY ON, CURSOR OFF
	LCD_CMD(0X28); //4-BIT INTERFACE MODE WITH BOTH LINES
	LCD_CMD(0X80); //SELECT STARTING ADDRESS OF DDRAM
}
void LCD_CMD(U32 C)
{
	//---UPPER NIPPILE----//
	IOCLR1 = LCD;
	IOSET1 = (C & 0XF0)<<16;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_milisec(2);
	IOCLR1 = E;
	
	//---LOWER NIPPILE----//
	IOCLR1 = LCD;
	IOSET1 = (C & 0X0F)<<20;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_milisec(2);
	IOCLR1 = E;
}
	
void LCD_DATA(U32 D)
{
	//---UPPER NIPPILE----//
	IOCLR1 = LCD;
	IOSET1 = (D & 0XF0)<<16;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_milisec(2);
	IOCLR1 = E;
	
	//---LOWER NIPPILE----//
	IOCLR1 = LCD;
	IOSET1 = (D & 0X0F)<<20;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = E;
	delay_milisec(2);
	IOCLR1 = E;
}

void LCD_STR(U8 *S){
	U8 ct=0;
	while(*S){
		LCD_DATA(*S++);
		ct++;
		if(ct==16)
			LCD_CMD(0x0c);
	}
}

void LCD_INTEGER(S32 n){
	U8 arr[5];
	S8 i=0;
	if(n==0)
		LCD_DATA('0');
	else
	{
		if(n<0)
		{
			LCD_DATA('-');
			n=-n;
		}
		
		while(n>0){
			arr[i++] = n%10+48;
			n = n/10;
		}
		
		for(--i;i>=0;i--)
			LCD_DATA(arr[i]);
	}
}

void LCD_FLOAT(float F){
	int temp = F;
	LCD_INTEGER(temp);
	LCD_DATA('.');
	temp=(F-temp)*100;
	LCD_INTEGER(temp);
}
