#include <LPC21xx.H>
#include <stdio.h>
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\header.h"

void UART_ISR() __irq // ISR Interrupt Service Routine Function
{
    unsigned char IIRValue;

    IIRValue = U0IIR;

    IIRValue >>= 1;
    IIRValue &= 0x02;
    if (IIRValue == IIR_RDA)
    {
        BUFFER = U0RBR;
    }
    VICVectAddr = 0x0;
}

void UART_INIT(void)
{
    PINSEL0 |= 0x05; // Enable UART Rx0 and Tx0 pins of UART
    U0LCR = 0x83;    // DLAB = 1, 1 stop bit, 8-bit character length
    U0DLM = 0x00;    // For baud rate of 9600 with Pclk = 15MHz
    U0DLL = 0x61;    // We get these values of U0DLL and U0DLM from formula
    U0LCR = 0x03;    // DLAB = 0

    VICIntEnable |= (1 << 6);          // To enable UART interrupt
    VICVectCntl0 = (1 << 5) | 6;       // Enable UART IRQ slot
    VICVectAddr0 = (unsigned)UART_ISR; // UART ISR function address
    U0IER = IER_RBR;                   // Enable RBR interrupt
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


