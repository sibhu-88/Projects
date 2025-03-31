#include "header.h"

/**
 * @brief Adds a new student record to the database.
 * @param ptr Pointer to the head of the linked list.
 */
void add_new_record(SDB **ptr) {
    char choice;

    do {
        SDB *newRecord = (SDB *)malloc(sizeof(SDB));
        if (!newRecord) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return;
        }

        // Get RFID from scanning function
        char *rfid = scanning();
        if (!rfid) {
            fprintf(stderr, "Error: Failed to scan RFID.\n");
            free(newRecord);
            return;
        }
        strncpy(newRecord->RFID, rfid, sizeof(newRecord->RFID) - 1);
        newRecord->RFID[sizeof(newRecord->RFID) - 1] = '\0'; // Ensure null termination
        free(rfid); // Free dynamically allocated RFID buffer

        // Get user input
        printf("\t Enter Your Name: ");
        if (scanf(" %[^\n]", newRecord->name) != 1) {
            fprintf(stderr, "Error: Invalid input for name.\n");
            free(newRecord);
            return;
        }

        printf("\t Enter Your Percentage: ");
        while (scanf("%f", &newRecord->percentage) != 1) {
            printf("Invalid input. Please enter a valid percentage: ");
            while (getchar() != '\n'); // Clear invalid input
        }

        // Assign roll number and link to the list
        if (*ptr == NULL) {
            newRecord->rollno = 1;
            newRecord->next = NULL;
            *ptr = newRecord;
        } else {
            SDB *last = *ptr;
            while (last->next) {
                last = last->next;
            }
            newRecord->rollno = last->rollno + 1;
            newRecord->next = NULL;
            last->next = newRecord;
        }

        // Ask user to add another record
        printf("\t Do you want to add another record? (y/n): ");
        while (scanf(" %c", &choice) != 1 || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            printf("Invalid input. Enter 'y' to add another record or 'n' to stop: ");
            while (getchar() != '\n'); // Clear invalid input
        }

    } while (choice == 'y' || choice == 'Y');
}
