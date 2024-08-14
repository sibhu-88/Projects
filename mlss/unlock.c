#define MAX_PASSWORD_ATTEMPTS 3 // Maximum number of attempts for entering the password
#define MAX_OTP_ATTEMPTS 3 // Maximum number of attempts for entering the OTP

void UNLOCK() {
    int i = 0, k = 0, L = 0; // Initialize counters for attempts
    char E_PASSWORD[4], key = 0, E_OTP[4];
    IODIR0 |= BUZZER | M1 | M2; // Set the direction of I/O pins

    PASSWORD:
    // Write default password to EEPROM
    i2c_eeprom_page_write(I2C_EEPROM_SA, 0X00, "1234", 4);
    // Read the stored password from EEPROM
    i2c_eeprom_seq_read(I2C_EEPROM_SA, 0x00, P, 4);

    LCD_CMD(0X01);
    LCD_STR("ENTER PASSWORD");
    UART_STR("ENTER PASSWORD\r\n");
    LCD_CMD(0XC0);

    i = 0;
    // Read password characters until ':' is entered
    while ((key = KEYSCAN()) != ':') {
        UART_TX(key);
        E_PASSWORD[i++] = key;
        LCD_DATA('*');
    }
    E_PASSWORD[i] = '\0'; // Null-terminate the password string
    UART_STR("\r\n");
    UART_STR(E_PASSWORD);

    delay_milisec(1000);

    if ((strcmp(E_PASSWORD, P)) == 0) { // Compare entered password with stored password
        GSM(G_OTP); // Generate and send OTP

        ENTER_OTP:
        LCD_CMD(0X01);
        LCD_STR("ENTER OTP");
        UART_STR("\r\nENTER OTP\r\n");
        LCD_CMD(0XC0);

        i = 0;
        // Read OTP characters until ':' is entered
        while ((key = KEYSCAN()) != ':') {
            E_OTP[i++] = key;
            UART_TX(key);
            LCD_DATA('*');
        }
        E_OTP[i] = '\0'; // Null-terminate the OTP string

        delay_milisec(1000);

        if ((strcmp(E_OTP, G_OTP)) == 0) { // Compare entered OTP with generated OTP
            LCD_CMD(0X01);
            LCD_STR("Door OPENING");
            UART_STR("\r\nDoor OPENING\r\n");

            IOSET0 = BUZZER | M1;
            IOCLR0 = M2;
            delay_sec(2);
            IOCLR0 = BUZZER;
            IOCLR0 = M1 | M2;

            delay_sec(3);

            LCD_CMD(0X01);
            LCD_STR("Door CLOSING");
            UART_STR("\r\nDoor CLOSING\r\n");

            IOSET0 = M2 | BUZZER;
            IOCLR0 = M1;
            delay_sec(2);
            IOCLR0 = BUZZER;
            IOCLR0 = M1 | M2;

            delay_sec(2);
            LCD_CMD(0X01);
            LCD_STR("THANK YOU");
            UART_STR("THANK YOU");
        } else {
            L++;
            if (L < MAX_OTP_ATTEMPTS) {
                LCD_CMD(0X01);
                LCD_STR("OTP is wrong");
                UART_STR("\r\nOTP is wrong\r\n");
                goto ENTER_OTP; // Retry OTP entry
            } else {
                LCD_CMD(0X01);
                LCD_STR("ACCESS DENIED");
                UART_STR("ACCESS DENIED\r\n");
                while (1); // Access denied, halt execution
            }
        }
    } else {
        k++;
        if (k < MAX_PASSWORD_ATTEMPTS) {
            LCD_CMD(0X01);
            LCD_STR("Password is wrong");
            UART_STR("Password is wrong\r\n");
            goto PASSWORD; // Retry password entry
        } else {
            LCD_STR("WAIT 5 SEC....-> ");
            UART_STR("WAIT 5 SEC....-> ");
            for (i = 0; i < 5; i++) {
                LCD_DATA(i + 48);
                UART_TX(i);
                delay_sec(1);
            }
            UART_STR("\r\n");
            UNLOCK(); // Wait 5 seconds and retry unlocking process
        }
    }
}
