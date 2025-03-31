#include <LPC21xx.H>
#include <stdio.h>
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\header.h"

void UART_INIT(u32 baud){
	PINSEL0|=0x5;
	U0LCR=0x83;
	switch(baud){	
		case 115200:U0DLL=32;	break;//PCLK=60MHz
		case 921600:U0DLL=4;	break;
		default:	U0DLL=32	;	
	}
	U0LCR=0x03;
}

void UART_TX(u8 data){
	while((U0LSR&(1<<5))==0);
	U0THR=data;
}

u8 UART_RX(void){
	while((U0LSR&0x1)==0);
	return U0RBR;
}


void UART_TX_STR(char *ptr){
	while (*ptr) {
        UART_TX(*ptr++); 
    }
}

void UART_TX_INT(int num){
	char buf[10];
	sprintf(buf,"%d",num);
	UART_TX_STR(buf);
}


void UART_TX_HEX(int num){
	char buf[10];
	sprintf(buf,"%X",num);
	UART_TX_STR(buf);
}

void UART_TX_FLOAT(float num){		
	int i=0;
	i=num;
	UART_TX_INT(i);
	i=(num-i)*10;
	UART_TX('.');
	UART_TX_INT(i);
}


