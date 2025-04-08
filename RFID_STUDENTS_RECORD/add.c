#include "header.h"

#define SCREEN_WIDTH 80 // Define terminal width

/**
 * @brief Adds a new student record to the database.
 * @param ptr Pointer to the head of the linked list.
 */
void add_new_record(SDB **ptr) {
    char choice,i=0;

    do {
        SDB *newRecord = (SDB *)malloc(sizeof(SDB));
	
	while (++i) {
	    SDB *current = *ptr;
	    while (current) {
		if (current->rollno == i) {
		    break;
		}
		current = current->next;
	    }
	    if (current == NULL) {
		newRecord->rollno = i;
		break;
	    }
	}	

        if (!newRecord) {
            printf("\n%*sError: Memory allocation failed.\n", SCREEN_WIDTH / 2 - 15, "");
            return;
        }

        // Get RFID from scanning function
        char *rfid = scanning(*ptr,1);
        if (!rfid) {
            printf("\n%*sError: Failed to scan RFID.\n", SCREEN_WIDTH / 2 - 15, "");
            free(newRecord);
            return;
        }

        strncpy(newRecord->RFID, rfid, sizeof(newRecord->RFID) - 1);
        newRecord->RFID[sizeof(newRecord->RFID) - 1] = '\0'; // Ensure null termination
        free(rfid); // Free dynamically allocated RFID buffer

        // Get user input
        printf("\n%*s+------------------------------------------+\n", SCREEN_WIDTH / 2 - 22, "");
        printf("%*s|          ADD NEW STUDENT RECORD          |\n", SCREEN_WIDTH / 2 - 22, "");
        printf("%*s+------------------------------------------+\n", SCREEN_WIDTH / 2 - 22, "");

        printf("\n%*sEnter your name: ", SCREEN_WIDTH / 2 - 10, "");
        if (!fgets(newRecord->name, sizeof(newRecord->name), stdin)) {
            printf("\n%*sError: Invalid input for name.\n", SCREEN_WIDTH / 2 - 15, "");
            free(newRecord);
            return;
        }
        newRecord->name[strcspn(newRecord->name, "\n")] = '\0'; // Remove trailing newline

        printf("\n%*sEnter your percentage: ", SCREEN_WIDTH / 2 - 14, "");
        while (scanf("%f", &newRecord->percentage) != 1) {
            printf("\n%*sInvalid input. Please enter a valid percentage: ", SCREEN_WIDTH / 2 - 20, "");
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
            newRecord->next = NULL;
            last->next = newRecord;
        }

        // Ask user to add another record
        printf("\n%*sDo you want to add another record? (y/n): ", SCREEN_WIDTH / 2 - 20, "");
        while (scanf(" %c", &choice) != 1 || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            printf("\n%*sInvalid input. Enter 'y' to add another record or 'n' to stop: ", SCREEN_WIDTH / 2 - 25, "");
            while (getchar() != '\n'); // Clear invalid input
        }

        getchar(); // Consume extra newline character

    } while (choice == 'y' || choice == 'Y');
}
