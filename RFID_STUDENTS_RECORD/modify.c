#include "header.h"

#define SCREEN_WIDTH 80 // Define terminal screen width

void Modify_record(SDB **ptr, char *RFID) {
    int percentage;
    char op, name[50];
    
    system("clear");
    
    if (*ptr == NULL) {
        printf("\n%*sNo records found.\n", SCREEN_WIDTH / 2, "");
        return;
    }

    if (display_student_list(*ptr, RFID) != 1) return;

    printf("\n%*s+--------------------------------------------+\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*s|        MODIFY OPTIONS MENU                 |\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*s+--------------------------------------------+\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*s| N/n : Name                                 |\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*s| P/p : Percentage                           |\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*s+--------------------------------------------+\n", SCREEN_WIDTH / 2 - 22, "");
    printf("%*sEnter Your Choice: ", SCREEN_WIDTH / 2 - 11, "");

    scanf(" %c", &op);

    SDB *current = *ptr;
    while (current != NULL && strncmp(current->RFID, RFID, 12) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\n%*sRecord not found.\n", SCREEN_WIDTH / 2, "");
        return;
    }

    switch (tolower(op)) {
        case 'n':
            printf("\n%*sEnter your name: ", SCREEN_WIDTH / 2 - 9, "");
            scanf(" %[^\n]", name);
            strcpy(current->name, name);
            break;

        case 'p':
            printf("\n%*sEnter your percentage: ", SCREEN_WIDTH / 2 - 14, "");
            while (scanf("%d", &percentage) != 1) {
                printf("\n%*sInvalid input. Please enter a valid percentage: ", SCREEN_WIDTH / 2 - 24, "");
                while (getchar() != '\n'); // Clear the input buffer
            }
            current->percentage = percentage;
            break;

        default:
            printf("\n%*sInvalid option selected.\n", SCREEN_WIDTH / 2, "");
            return;
    }

    printf("\n%*sRecord updated successfully.\n", SCREEN_WIDTH / 2, "");
    sleep(1);
}
