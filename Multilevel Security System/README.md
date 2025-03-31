
# Multilevel Security System: Authentication with Automatic Door Open and Close

## Required Components

- LPC2129
- GSM (SIM900, in-built GPRS)
- EEPROM
- LCD
- Keypad
- DC Motor
- Buzzer

## System Overview

The "Multilevel Security System" is designed to provide secure access control using a combination of a password and a one-time password (OTP) sent via SMS. Here’s how the system works:

1. **Initialization and Setup**:
    - Initialize necessary components such as the EEPROM for storing passwords, the GSM module for sending OTPs, and the keypad for user input.
    - Set up pins for controlling external devices like the buzzer and door lock mechanisms.

2. **Password Entry**:
    - Prompt the user to enter a password via the keypad.
    - Compare the entered password with the stored password retrieved from the EEPROM.
    - If the password matches, generate and send an OTP.

3. **OTP Generation and Verification**:
    - Generate a random OTP and send it to a predefined phone number using the GSM module.
    - Prompt the user to enter the received OTP through the keypad.
    - Compare the entered OTP with the generated OTP. If they match, grant access to the user.

4. **Access Control**:
    - If the OTP is verified, trigger actions such as unlocking the door, activating the buzzer, and displaying messages on an LCD screen to indicate successful access.
    - After a predefined duration, automatically lock the door and reset for the next access attempt.

5. **Error Handling**:
    - If the user enters the wrong password or OTP multiple times (defined by `MAX_PASSWORD_ATTEMPTS` and `MAX_OTP_ATTEMPTS`), deny access and provide appropriate messages.
    - For instance, if the OTP is entered incorrectly three times, deny access and display an "ACCESS DENIED" message, prompting the user to retry after a delay.

6. **User Interface**:
    - Provide a user-friendly interface through an LCD screen displaying messages and a keypad for input.
    - Use UART communication for sending/receiving data to/from external devices like the GSM module.

7. **Security Measures**:
    - Implement multiple levels of security, including a strong password and a time-limited OTP, to ensure secure access control.
    - Include mechanisms to handle incorrect inputs, prevent brute-force attacks, and provide feedback to the user during the access process.

Overall, the "Multilevel Security System" enhances security in accessing restricted areas or resources by combining password-based authentication with OTP verification. It is suitable for applications where secure access control is critical.

## Tools and Equipment

To implement the "Multilevel Security System" described earlier, you will need the following components and equipment:

1. **Microcontroller Development Board**: A development board based on the LPC21xx series or a similar microcontroller that supports features such as GPIO, UART communication, timers, and I2C interfacing.
2. **Keypad**: A 4x4 matrix keypad or a similar input device that can be interfaced with the microcontroller to enter passwords and OTPs.
3. **LCD Display**: A 16x2 or 20x4 character LCD module for providing visual feedback and messages to the user.
4. **EEPROM**: An EEPROM (Electrically Erasable Programmable Read-Only Memory) for securely storing passwords. Ensure the EEPROM has sufficient capacity for storing passwords and relevant data.
5. **GSM Module**: A GSM module for sending OTPs via SMS. Ensure the GSM module supports AT commands for SMS communication and has a SIM card slot for sending/receiving messages.
6. **Buzzer**: An audio signalling device to provide audible feedback during certain system events, such as successful access or access denied.
7. **Electronic Lock Mechanism**: An electronic lock mechanism controlled by the microcontroller, such as a solenoid-based lock.
8. **Power Supply**: A stable power supply for the microcontroller board, keypad, LCD, GSM module, and other components. Use appropriate voltage regulators if needed.
9. **Connecting Wires and Breadboard/PCB**: Jumper wires, breadboard, or PCB for assembling the circuit.
10. **Development Tools**: Keil uVision for development.
11. **Computer with Terminal Software**: A computer with terminal software (such as PuTTY, Tera Term, or Arduino Serial Monitor) for communicating with the microcontroller over UART for debugging and monitoring purposes.
12. **Additional Components**: Depending on your specific implementation and customization, you may need additional components such as resistors, capacitors, voltage regulators, and connectors.
