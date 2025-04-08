#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/**
 * @brief Structure to store student database information.
 */
typedef struct SDB {
    char RFID[13];         ///< Student's RFID (12 characters + null terminator)
    int rollno;            ///< Unique roll number
    char name[50];         ///< Student's name
    float percentage;      ///< Student's academic percentage
    struct SDB *next;      ///< Pointer to next record (for linked list)
} SDB;

/* Function Declarations */

/** 
 * @brief Scans and returns the RFID from the scanner. 
 * @return Pointer to dynamically allocated RFID string.
 */
char *scanning(SDB *ptr,int flag);

/** 
 * @brief Adds a new student record to the database.
 * @param ptr Pointer to the head of the student database list.
 */
void add_new_record(SDB **ptr);

/**
 * @brief Displays a specific student's details based on RFID.
 * @param ptr Pointer to the head of the student database list.
 * @param RFID The RFID of the student to be displayed.
 * @return 1 if student found, 0 otherwise.
 */
int display_student_list(SDB *ptr, char *RFID);

/**
 * @brief Displays the entire student database.
 * @param ptr Pointer to the head of the student database list.
 */
void display_students_list(SDB *ptr);

/**
 * @brief Fetches and displays student details based on RFID.
 * @param ptr Pointer to the head of the student database list.
 * @param RFID The RFID of the student.
 */
void student(SDB **ptr, char *RFID);

/**
 * @brief Modifies an existing student record based on RFID.
 * @param ptr Pointer to the head of the student database list.
 * @param RFID The RFID of the student whose record needs modification.
 */
void Modify_record(SDB **ptr, char *RFID);

/**
 * @brief Deletes a student record based on RFID.
 * @param ptr Pointer to the head of the student database list.
 * @param RFID The RFID of the student to be deleted.
 */
void Delete_record(SDB **ptr, char *RFID);

/**
 * @brief Saves the current student database to a file.
 * @param ptr Pointer to the head of the student database list.
 */
void Save_record(SDB *ptr);

/**
 * @brief Reads student records from a file and loads them into memory.
 * @param ptr Pointer to the head of the student database list.
 */
void read_records_from_file(SDB **ptr);

/**
 * @brief Prints a given string in a centered format.
 * @param str The string to be printed.
 */
void print_centered(const char *str);

#endif // HEADER_H
