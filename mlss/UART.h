// WRITE AN ECP TO RECIVING CHARACTER SERIALLY THROUGH UART OF LPC2129.
#include <LPC21XX.H>
#include "typedef.h"

// Function prototypes
void UART_INIT(void);
void UART_TX(U8);
U8 UART_RX(void);
void UART_STR(U8 *);

// Initialize UART
void UART_INIT(void)
{
    PINSEL0 |= 0x05; // Enable UART on pins P0.0 (TXD0) and P0.1 (RXD0)
    U0LCR = 0x83;   // Set DLAB to access DLL and DLM registers
    U0DLL = 97;     // Set baud rate to 9600 (for 15MHz PCLK)
    U0LCR = 0x03;   // Clear DLAB to lock baud rate setting
}

// Transmit a character via UART
void UART_TX(U8 D)
{
    while (!(U0LSR & (1 << 5)))
        ;      // Wait until THR is empty
    U0THR = D; // Transmit the character
}

// Receive a character via UART
U8 UART_RX(void)
{
    while (!(U0LSR & (1 << 0)))
        ;         // Wait until RBR has valid data
    return U0RBR; // Return received character
}

// Transmit a string via UART
void UART_STR(U8 *S)
{
    while (*S != '\0')
    {
        UART_TX(*S++); // Transmit each character of the string
    }
}
