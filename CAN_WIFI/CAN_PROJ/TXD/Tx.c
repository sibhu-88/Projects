/* main_nodeA_TX.c */
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\header.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\can_driver.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\delay.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\lcd.h"

#define SW1 14
#define SW2 15
#define SW3 16

#define READPIN(VAR, BIT) ((VAR >> BIT) & 1)
#define IER_RBR 0X01
#define IIR_RDA 0X02

unsigned char BUFFER;
unsigned char COMMAND;

unsigned char RIGHT = '@', LEFT = '%', WIPPER = '$';

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

void delay_ms(uint16_t j) // Function for delay in milliseconds
{
	T0PR = 15000 - 1;
	T0TCR = 0x01; // Start timer
	while (T0TC < j)
		;
	T0TCR = 0x03; // Reset timer
	T0TCR = 0x00; // Stop timer
}

void UART_INIT(void)
{
	PINSEL0 |= 0x05; // Enable UART Rx0 and Tx0 pins of UART
	U0LCR = 0x83;	 // DLAB = 1, 1 stop bit, 8-bit character length
	U0DLM = 0x00;	 // For baud rate of 9600 with Pclk = 15MHz
	U0DLL = 0x61;	 // We get these values of U0DLL and U0DLM from formula
	U0LCR = 0x03;	 // DLAB = 0

	VICIntEnable |= (1 << 6);		   // To enable UART interrupt
	VICVectCntl0 = (1 << 5) | 6;	   // Enable UART IRQ slot
	VICVectAddr0 = (unsigned)UART_ISR; // UART ISR function address
	U0IER = IER_RBR;				   // Enable RBR interrupt
}

void UART_TX(char ch) // A function to send a byte on UART
{
	U0THR = ch;
	while ((U0LSR & 0x40) == 0)
		; // Wait till THRE bit becomes 1 which tells that transmission is completed
}

void UART_STR(char *str) // A function to send string on UART
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		UART_TX(str[i++]);
	}
}

void WIFI_CONF(void)
{
	delay_ms(5000);
	UART_STR("AT\r\n"); // Sends AT to ESP8266
	delay_ms(3000);
	UART_STR("AT+CWMODE=2\r\n"); // Sends AT+CWMODE=2 (Setting ESP8266 in AP mode)
	delay_ms(3000);
	UART_STR("AT+CWJAP=”wifi1”,”password”\r\n"); // Sends AT+CWJAP=”SSID”,”PASSWORD” (Setting ESP8266 in Connects to a network with the specified SSID and password)
	delay_ms(3000);
	UART_STR("AT+CIFSR\r\n"); // Sends AT+CIFSR (For getting IP of AP)
	delay_ms(3000);
	UART_STR("AT+CIPMUX=1\r\n"); // Sends AT+CIPMUX=1 (For Mutliple Connections)
	delay_ms(3000);
	UART_STR("AT+CIPSERVER=1,80\r\n"); // Sends AT+CIPSERVER=1,80 (For ENABLING ESP8266 SERVER with OPEN PORT)
	delay_ms(3000);
}

main()
{
	CAN2_MSG m1, m2, m3;
	can2_init();
	LCD_INIT();
	UART_INIT(115200);
	/*sending data frame*/

	UART_TX_STR("BODY CONTROL MODIULE\r\n");
	LCD_STR("BODY CONTROL MODIULE");

	while (1)
	{
		if (BUFFER != 0)
		{
			if (COMMAND == RIGHT)
			{
				m1.id = 0x0A;
				m1.rtr = 0; // data frame
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				UART_TX_STR("\r\nRIGHT INDICATOR ON\r\n");
				LCD_STR("RIGHT INDICATOR ON");
				can2_tx(m1); // data-frame
				UART_TX_HEX(m1.id);
			}
			else if (COMMAND == LEFT)
			{
				m2.id = 0x0B;
				m2.rtr = 0;	 // data frame
				can2_tx(m2); // data-frame
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				UART_TX_STR("\r\nLEFT INDICATOR ON\r\n");
				LCD_STR("LEFT INDICATOR ON");
				UART_TX_HEX(m2.id);
			}
			else if (COMMAND == WIPPER)
			{
				m3.id = 0x0C;
				m3.rtr = 0;	 // data frame
				can2_tx(m3); // data-frame
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				UART_TX_STR("\r\nWIPER ON\r\n");
				LCD_STR("WIPER ON");
				UART_TX_HEX(m3.id);
			}
		}
	}
}
