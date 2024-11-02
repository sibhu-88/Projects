---

# Student Database Management System

## Project Overview

The **Student Database Management System** is a C-based application that allows users to efficiently manage student records, providing functionalities to add, modify, delete, and display student data. The system is built using dynamic memory management with linked lists, making it scalable for handling varying numbers of records.

## Features

- **Add New Record**: Add a new student's roll number, name, and percentage to the database.
- **Delete Record**: Remove a student's record by roll number or name.
- **Modify Record**: Modify existing student data (roll number, name, or percentage).
- **Search Record**: Search for students by roll number, name, or percentage.
- **Display Records**: Display all student records stored in the database.
- **Sort Records**: Sort records by name or percentage.
- **Reverse List**: Reverse the order of student records in the list.
- **Delete All Records**: Clear the entire database.
- **Save Records**: Save student records to a file for future access.
- **Exit**: Exit the system, with options to save changes before quitting.

## Project Structure

The project consists of multiple files for modular development:

- **`main.c`**: Contains the main logic and user interface.
- **` header.h`**: Header file containing function prototypes and data structure definitions.
- **` add.c`**: Code for adding new student records to the database.
- **`delete.c`**: Handles the deletion of student records.
- **` save.c`**: Implements functionality for saving the student records to an external file.
- **`show.c`**: Displays the list of student records stored.
- **`modifi.c`**: Handles the modification of existing student records.
- **`makefile`**: Automates the compilation and linking of project files.

## File Breakdown

### `main.c`
- Contains the main function, and handles the menu and user input.
- Calls appropriate functions for each operation (Add, Delete, Modify, etc.).
- [View the code here](./main.c)

### `header.h`
- Defines the `SDB` structure (Student Database structure).
- Contains all function prototypes.
- [View the code here](./header.h)

### `add.c`
- Functionality to add new student records by inputting roll number, name, and percentage.
- [View the code here](./add.c)

### `delete.c`
- Handles deleting records by either roll number or name.
- [View the code here](./delete.c)

### `save.c`
- Saves the current list of student records to a file (`student.xls`) for future access.
- [View the code here](./save.c)

### `show.c`
- Displays the student list, showing each student's roll number, name, and percentage.
- [View the code here](./show.c)

### `modifi.c`
- Implements the logic for modifying student data (name, roll number, or percentage).
- Contains functions to search and modify records by roll number, name, or percentage.
- [View the code here](./modifi.c)
  
## Key Functions

- **`Add_new_record()`**: Adds a new student record to the database.
- **`Delete_record()`**: Deletes a student record by roll number or name.
- **`Show_list()`**: Displays all student records.
- **`Modify_record()`**: Modifies an existing record (name, roll number, or percentage).
- **`Save_record()`**: Saves the student database to an external file.
- **`Delete_all_record()`**: Clears all records from the database.
- **`Sort_list()`**: Sorts the student records by name or percentage.
- **`Reverse_list()`**: Reverses the order of the student records.
- **`Exit()`**: Exits the application, with options to save before exiting.

## Menu Options

- **Add New Record**: Enter the roll number, name, and percentage to add a new student to the database.
- **Delete Record**: Remove a student’s record by roll number or name.
- **Show List**: Display the list of all students.
- **Modify Record**: Change a student’s roll number, name, or percentage.
- **Save**: Save the current student records to a file.
- **Sort**: Sort the list of students by name or percentage.
- **Reverse**: Reverse the order of the student records.
- **Exit**: Exit the system with an option to save changes.

## Project Workflow

1. **Input Data**: Users can add records with student details (roll number, name, percentage).
2. **Modify & Manage**: Users can easily delete, modify, or search records.
3. **Save Data**: The system allows saving the student records to an external file.
4. **Display & Sort**: Users can view the records sorted by name or percentage.
5. **Exit**: Provides an option to save the records before exiting the program.

## Future Enhancements

- **Advanced Search**: Implement advanced searching based on more criteria.
- **Bulk Import/Export**: Allow users to import/export student records in bulk.
- **Improved UI**: A more intuitive and user-friendly interface.

---