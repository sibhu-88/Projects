#include <LPC21xx.H>

/**
 * @brief Initializes UART0 with 9600 baud rate.
 */
void UART_INIT()
{
    PINSEL0 |= 0x05;    // Configure P0.0 and P0.1 as UART0 TXD and RXD
    U0LCR = 0x83;       // Enable DLAB, 8-bit data, 1 stop bit, no parity
    U0DLL = 97;         // Set baud rate to 9600 (Assuming PCLK = 15MHz)
    U0LCR = 0x03;       // Disable DLAB
}

/**
 * @brief Transmits a single character via UART0.
 * @param data Character to transmit.
 */
void UART_TX(char data)
{
    U0THR = data;  
    while (!(U0LSR & (1 << 5))); // Wait until THR is empty
}

/**
 * @brief Receives a single character via UART0.
 * @return Received character.
 */
char UART_RX()
{
    while (!(U0LSR & 1)); // Wait until data is received
    return U0RBR; 
}

/**
 * @brief Transmits a string via UART0.
 * @param str Pointer to the null-terminated string.
 */
void UART_TX_STR(const char *str)
{
    while (*str)
    {
        UART_TX(*str++);
    }
}

int main()
{
    char receivedChar;
    int i = 10;

    UART_INIT();
    // UART_TX_STR("SDB_RFID\n\r"); // Uncomment if needed

    while (i--)
    {
        receivedChar = UART_RX();
        UART_TX(receivedChar);
    }

    // UART_TX_STR("\n\r"); // Uncomment if needed

    return 0;
}
