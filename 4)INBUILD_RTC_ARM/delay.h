#include"E:\v23ce5s9\SIVA\ARM\EMBEDDED\Header\typedef.h"

void delay_sec(U32 sec)
{
		T0PR = 15000000 - 1;
		T0TCR = 0X01;
		while(T0TC<sec);
		T0TCR = 0X03;
		T0TCR = 0X00;
}

void delay_milisec(U32 ms)
{
		T0PR = 15000 - 1;
		T0TCR = 0X01;
		while(T0TC<ms);
		T0TCR = 0X03;
		T0TCR = 0X00;
}

void delay_microsec(U32 mis)
{
		T0PR = 15 - 1;
		T0TCR = 0X01;
		while(T0TC<mis);
		T0TCR = 0X03;
		T0TCR = 0X00;
}
