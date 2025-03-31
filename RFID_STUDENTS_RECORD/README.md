# RFID-Based Student Record Management System

## Introduction

The RFID-Based Student Record Management System is designed to streamline the process of managing student records using RFID technology. This system allows easy addition, modification, deletion, and retrieval of student information based on their unique RFID tags.

## Features

### RFID Scanning
- Enables automatic identification of students.

### Student Record Management
- Add new student records.
- Modify existing student details.
- Delete student records when necessary.
- Display stored student records.

### File Storage
- Student data is saved in a structured file format.

## System Components

- **RFID Scanner**: Reads the student's RFID tag.
- **Database (Linked List Implementation)**: Stores student records dynamically.
- **File Handling**: Saves and retrieves student records from `student.xls`.
- **User Interface (Terminal-based Menu)**: Provides an interactive way to manage records.

## Implementation Details

### File Structure

- `main.c`: Controls the flow of the program and user interactions.
- `RFID.c`: Handles RFID scanning and processing.
- `add.c`: Contains functions to add new student records.
- `modify.c`: Provides options to modify existing student details.
- `delete.c`: Deletes a student record from the system.
- `show.c`: Displays student records in a formatted manner.
- `save.c`: Saves and loads records from a file.
- `header.h`: Includes function declarations and structure definitions.
- `makefile`: Automates the compilation of the project.

### Student Record Structure

```c
typedef struct StudentDatabase {
    char RFID[13];
    int rollno;
    char name[50];
    float percentage;
    struct StudentDatabase *next;
} SDB;
```

## Workflow

### Scanning a Student's RFID
- Reads RFID and fetches corresponding student data.
- Displays student information if found.

### Adding a Student Record
- Prompts user for student details.
- Assigns a roll number and stores the data.

### Modifying Student Details
- Allows the user to update name or percentage.

### Deleting a Student Record
- Searches for a student using RFID and removes the record.

### Saving & Loading Data
- Automatically saves records after modifications.
- Reads data from `student.xls` during startup.

## Usage

1. Run `make` to compile the project.
2. Execute `./outfile` to start the system.
3. Follow the menu options to manage student records.

## Future Enhancements

- **GUI Integration**: Replace the terminal-based UI with a graphical interface.
- **Database Integration**: Store records in a structured SQL or NoSQL database.
- **Web/Mobile Access**: Provide access through a web portal or mobile app.

## Conclusion

The RFID-Based Student Record Management System provides an efficient way to manage student data using RFID technology. The system ensures quick access, easy modifications, and structured data storage, improving the overall record-keeping process.
