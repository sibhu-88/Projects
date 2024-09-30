# GPS and GSM-Based Car Location System

## Overview
This project implements a GPS and GSM-based car location tracking system using UART communication. The system retrieves the car's current GPS coordinates and sends them via SMS using a GSM module. It leverages various embedded system techniques such as UART communication, interrupt handling, and timers for delays.

## Features
- **GPS Location Retrieval**: Fetches the car’s current North and East coordinates using the GPS module.
- **GSM SMS Messaging**: Sends the car's GPS location to a specified phone number via SMS using the GSM module.
- **UART Communication**: Utilizes UART interrupts for efficiently handling incoming GPS data.
- **Configurable Delays**: Implements delay functions for precise timing in seconds, milliseconds, and microseconds.

## Files

### Source Files:
- **MAIN.C**: 
  - Initializes UART communication and sets up a continuous loop to check the status of a switch. When the switch is activated, it triggers the GPS function to retrieve location data.
  
- **gps.c**:
  - Contains the GPS function that retrieves the GPS coordinates using UART communication and sends them via GSM.
  
- **uart.h**:
  - Defines the UART initialization and communication functions (transmit, receive, and string-based operations).
  
- **typedef.h**:
  - Contains type definitions for shorthand notations of various data types (e.g., U32 for unsigned 32-bit integers).
  
- **delay.h**:
  - Implements delay functions (`delay_sec`, `delay_milisec`, and `delay_micsec`) for precise time management using a timer register.

### Header Files:
- **uart.h**: 
  - Prototypes for UART initialization, transmission, and reception of data.
  
- **delay.h**: 
  - Provides the delay functions for seconds, milliseconds, and microseconds.

## How It Works

1. **GPS Setup**: 
   - The GPS module is configured using AT commands to retrieve location data.
   - The data is processed and prepared for transmission via GSM.
   
2. **GSM SMS**: 
   - The GSM module sends the car’s location via SMS to a specified phone number.
   
3. **UART Interrupt**: 
   - UART interrupts are used to handle incoming GPS data efficiently.
   
4. **Delay Functions**: 
   - The system uses precise delay functions based on a timer register to manage UART communication timing and control flow.

## Usage

1. **Setup**: Connect the GPS and GSM modules to the microcontroller and ensure proper wiring for UART communication.
2. **Compilation**: Compile the project and upload it to the microcontroller.
3. **Running**: The system will continuously check if the switch is pressed. Upon activation, it will retrieve GPS data and send it as an SMS to the pre-configured phone number.
4. **Customization**: Modify the phone number in the GSM SMS function to send the SMS to your desired recipient.

## Dependencies

- **GPS Module**: Used to retrieve real-time location data.
- **GSM Module**: Sends SMS messages containing the GPS coordinates.
- **UART Communication**: Utilized for serial communication with the GPS and GSM modules.
- **Timer**: Used for generating delays required for the system’s timing.
---

You can modify the phone number and certain settings in the code depending on your requirements. Let me know if you'd like any further customization!
