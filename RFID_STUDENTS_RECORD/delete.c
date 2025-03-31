#include "header.h"

void Delete_record(SDB **ptr, char *RFID) {
    if (*ptr == NULL) {
        printf("\n\t\t\tNo records found.\n");
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
        printf("\n\t\t\tRecord with RFID %s not found.\n", RFID);
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
    
    printf("\t\t\tYour record has been deleted successfully.\n");
    usleep(500000); // Sleep for 0.5 seconds

    // Save updated records
    Save_record(*ptr);
    usleep(50000); // Sleep for 50ms
}
