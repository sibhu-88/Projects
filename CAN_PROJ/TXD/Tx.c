					/* main_nodeA_TX.c */
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\header.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\can_driver.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\delay.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\uart.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\lcd.h"

#define SW1 14
#define SW2 15
#define SW3 16

#define READPIN(VAR,BIT) ((VAR >> BIT)&1)

main(){	
	CAN2_MSG m1,m2,m3;
	can2_init();
	LCD_INIT();
	UART_INIT(115200);
	/*sending data frame*/

	UART_TX_STR("BODY CONTROL MODIULE\r\n");
	LCD_STR("BODY CONTROL MODIULE");

	while(1){	
		if(READPIN(IOPIN0,SW1)==0){
			DELAY_MS(150);
			m1.id=0x0A;
			m1.rtr=0;//data frame
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			UART_TX_STR("\r\nRIGHT INDICATOR ON\r\n");
			LCD_STR("RIGHT INDICATOR ON");
			can2_tx(m1);//data-frame
			UART_TX_HEX(m1.id);
			while(READPIN(IOPIN0,SW1)==0);
		}
		else if(READPIN(IOPIN0,SW2)==0){
			DELAY_MS(150);
			m2.id=0x0B;
			m2.rtr=0;//data frame
			can2_tx(m2);//data-frame		 
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			UART_TX_STR("\r\nLEFT INDICATOR ON\r\n");
			LCD_STR("LEFT INDICATOR ON");
			UART_TX_HEX(m2.id);
			while(READPIN(IOPIN0,SW2)==0);
		}
		else if(READPIN(IOPIN0,SW3)==0){
			DELAY_MS(150);
			m3.id=0x0C;
			m3.rtr=0;//data frame
			can2_tx(m3);//data-frame	
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			UART_TX_STR("\r\nWIPER ON\r\n");
			LCD_STR("WIPER ON");
			UART_TX_HEX(m3.id);
			while(READPIN(IOPIN0,SW3)==0);
		}
	}
}
