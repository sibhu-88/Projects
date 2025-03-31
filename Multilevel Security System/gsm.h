#include <stdlib.h>
#include "typedef.h"

#define NUMBER "+919488289487" // Define recipient phone number //In atd mode remove +91

// Function prototypes
void GSM_SMS(const char *, const char *);
void generateOTP(char *);

void GSM(char *otp)
{
    // Generate random OTP
    generateOTP(otp);

    // Send SMS with the OTP
    GSM_SMS(NUMBER, otp);
}

void generateOTP(char *otp)
{
    // Declare variables
    int x;

    // Generate random number (OTP)
    srand(T1TC);
    x = rand() % (9999 - 1000) + 1000;
    sprintf(otp, "%d", x);
}

// Send SMS using GSM module
void GSM_SMS(const char *num, const char *msg)
{
    delay_sec(1);

    // Send "AT" command to check connection
    UART_STR("AT\r\n");
    delay_sec(2);

    // Set SMS text mode
    UART_STR("AT+CMGF=1\r\n");
    delay_sec(2);

    // Send recipient's phone number
    UART_STR("AT+CMGS=\"");
    UART_STR(num);
    UART_STR("\"\r\n");
    delay_milisec(250);

    // Send message content
    UART_STR("Your Login OTP is -> ");
    UART_STR(msg);
    UART_TX(0x1A); // End of message transmission (Ctrl+Z)
}
