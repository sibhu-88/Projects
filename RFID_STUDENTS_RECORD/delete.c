#include "header.h"

#define SCREEN_WIDTH 80 // Define terminal width

void Delete_record(SDB **ptr, char *RFID) {
    if (*ptr == NULL) {
        printf("\n%*sNo records found.\n", SCREEN_WIDTH / 2 - 10, "");
        return;
    }

    SDB *current = *ptr;
    SDB *previous = NULL;

    // Find the record with the matching RFID
    while (current && strncmp(current->RFID, RFID, 12) != 0) {
        previous = current;
        current = current->next;
    }

    // If no matching record is found
    if (!current) {
        printf("\n%*sRecord with RFID %s not found.\n", SCREEN_WIDTH / 2 - 15, "", RFID);
        return;
    }

    // Remove the found node from the linked list
    if (previous == NULL) {
        *ptr = current->next; // Update head if it's the first node
    } else {
        previous->next = current->next; // Bypass the node
    }

    // Free the memory of the deleted node
    free(current);

    printf("\n%*sYour record has been deleted successfully.\n", SCREEN_WIDTH / 2 - 15, "");
    usleep(500000); // Sleep for 0.5 seconds

    // Save updated records
    Save_record(*ptr);
    usleep(50000); // Sleep for 50ms
}
