# RFID-Based Student Record Management System

## Overview
The **RFID-Based Student Record Management System** is designed to efficiently manage student information using RFID technology. This system enables quick and accurate retrieval, modification, and storage of student records, reducing manual data entry efforts.

## Features
- **RFID Scanning**: Uses RFID to uniquely identify students.
- **Add Student Records**: Allows new student details to be added.
- **Modify Records**: Update student details such as name and percentage.
- **Delete Records**: Remove student records from the database.
- **Search and Display**: Retrieve student records using RFID.
- **File Storage**: Saves and loads records from a file (`student.xls`).

## Implementation
The project consists of multiple modules:
- **`main.c`**: Handles the user interface and menu navigation.
- **`RFID.c`**: Handles RFID scanning operations.
- **`add.c`**: Adds new student records.
- **`modify.c`**: Modifies existing student details.
- **`delete.c`**: Deletes student records.
- **`show.c`**: Displays student information.
- **`save.c`**: Handles file operations (saving and loading data).
- **`header.h`**: Contains shared definitions and function prototypes.

## How to Compile & Run
1. Compile using the provided `makefile`:
   ```sh
   make
   ```
2. Run the program:
   ```sh
   ./outfile
   ```

## Future Enhancements
- Implement a GUI for better user experience.
- Add authentication to restrict access.
- Integrate with cloud storage for remote access.

## Author
**Siva Prabhu V**
