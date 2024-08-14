#include <lpc21xx.h>
#include "UART.h"
#include "lcd.h"
#include "unlock.c"

#define SW 15
#define READPIN(VAR, BIT) ((VAR >> BIT) & 1)

int main() {
    // Initialize peripherals
    LCD_INIT();
    init_i2c();
    UART_INIT();

    // Start Timer 1
    T1TCR = 0x01;

    // Send initialization message via UART and display on LCD
    UART_STR("MULTILEVEL SECURITY SYSTEM\r\n");
    LCD_STR("MULTILEVEL SECURITY SYSTEM");

    // Wait for the switch to be pressed
    while (READPIN(IOPIN0, SW) == 1);

    // Start the multilevel security system
    UNLOCK();

    return 0;
}
