/* main_nodeB_RX.c */

#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\header.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\can_driver.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\delay.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\uart.h"
#include "E:\v23ce5s9\SIVA\ARM\EMBEDDED\project\CAN_1\indicate.h"

// #define led1 1<<17
// #define led2 1<<18
// #define led3 1<<19


main(){	
	CAN2_MSG m1;
	can2_init();
	UART_INIT(115200);
// 	IODIR0 = led1|led2|led3;
// 	IOSET0 = led1|led2|led3;
	UART_TX_STR("nodeB TESTING CAN\r\n");
	while(1){		
		can2_rx(&m1);
		
		if(m1.id==0XA){
			UART_TX_HEX(m1.id);
			UART_TX_STR(" node A: received\r\n");
			right();
		}	
		else if(m1.id==0XB){
			UART_TX_HEX(m1.id);
			UART_TX_STR(" node B: received\r\n");
			left();
		}
	}
	
}

