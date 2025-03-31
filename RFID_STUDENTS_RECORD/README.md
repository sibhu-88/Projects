# RFID-Based Student Database Management System

## Project Overview
This project is designed to manage student records efficiently using **RFID technology**. The system allows users to scan RFID tags to retrieve, add, modify, and delete student information. It is implemented using **C programming** for database operations and **LPC2129 microcontroller** for RFID communication via UART.

## How It Works
1. **RFID Communication (LPC2129 - Keil)**
   - The microcontroller reads RFID tags via UART.
   - It sends the RFID data to the C application through socket communication.

2. **Student Database Management (C Application)**
   - The scanned RFID tag is matched with the database.
   - Users can add student details like name and percentage.
   - Existing records can be modified or deleted.

## Project Structure
```
RFID-Based Student Management System
│── keil/              # Embedded firmware for LPC2129
│   ├── RFID.c         # Handles UART communication with RFID reader
│── database/          # C programs for student record management
│   ├── add.c          # Adds student records
│   ├── delete.c       # Deletes student records
│   ├── modify.c       # Modifies student records
│   ├── save.c         # Saves records to file/database
│   ├── show.c         # Displays student records
│   ├── main.c         # Main program handling user menu
│   ├── header.h       # Common header file
│   ├── makefile       # Build automation script
```

## Advantages
✅ **Fast Identification:** RFID allows quick and seamless student identification.
✅ **Automation:** Reduces manual data entry and errors.
✅ **Data Security:** Ensures student information is securely stored and retrieved.
✅ **Scalability:** Can be expanded to manage a larger number of records.
✅ **Integration:** Can be integrated with attendance systems and access control.

## Disadvantages
❌ **Hardware Dependency:** Requires RFID readers and compatible microcontrollers.
❌ **Data Loss Risk:** If not backed up properly, records may be lost due to system failures.
❌ **RFID Cloning Risks:** Unauthorized duplication of RFID tags can be a security concern.

## Conclusion
This project is an efficient and scalable solution for student record management using RFID technology. It demonstrates the power of embedded systems and database management integration, making it suitable for educational institutions and automated identification systems.

---
📌 *For more details and source code, visit the repository:* [RFID-Based Student Management](https://github.com/sibhu-88/practice/tree/main/RFID_SDB)
