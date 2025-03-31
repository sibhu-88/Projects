#include <LPC21xx.H>

void DELAY_SEC(u32 s){
	T0PR=6000000-1;
	//T0TC=T0PC=0;
	T0TCR=0x1;
	while(T0TC<s);
	T0TCR=0x03;
	T0TCR = 0x00;
}

void DELAY_MS(u32 ms){
	T0PR=60000-1;
	T0TC=T0PC=0;
	T0TCR=0x1;
	while(T0TC<ms);
	T0TCR=0x0;
}
