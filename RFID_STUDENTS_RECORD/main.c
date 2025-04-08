#include "header.h"

#define SCREEN_WIDTH 80 // Define the terminal screen width

int main() {
    char ch;
    char rfid[256];
    SDB *hptr = NULL;
    read_records_from_file(&hptr);

    do {
        system("clear");
        printf("\n");

        int padding = (SCREEN_WIDTH - 31) / 2;
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s|      STUDENT RECORD MENU      |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s| a/A : Add New Record          |\n", padding, "");
        printf("%*s| s/S : Scan the student        |\n", padding, "");
        printf("%*s| e/E : Exit                    |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s Enter Your Choice: ", padding, "");

        scanf(" %c", &ch);
        getchar(); // Consume newline character

        switch (tolower(ch)) {
            case 's':
                strncpy(rfid, scanning(hptr,0), 13);
                rfid[12] = '\0';
                printf("%*sRFID - %s\n", (SCREEN_WIDTH - 20) / 2, "", rfid);
                sleep(1);
                student(&hptr, rfid);
                break;
            case 'a':
                printf("\n%*s Add your Data :\n\n", (SCREEN_WIDTH - 20) / 2, "");
                add_new_record(&hptr);
                display_students_list(hptr);
                break;
            case 'e':
                Save_record(hptr);
                usleep(50000);
                printf("\n%*s Exiting...\n", (SCREEN_WIDTH - 10) / 2, "");
                exit(0);
            default:
                printf("\n%*s Invalid option\n", (SCREEN_WIDTH - 20) / 2, "");
                break;
        }

        printf("\n%*s Do you want to try again? (y/n): ", (SCREEN_WIDTH - 32) / 2, "");
        scanf(" %c", &ch);
        getchar(); // Consume newline character
    } while (tolower(ch) == 'y');

    return 0;
}

void student(SDB **ptr, char *rfid) {
    char ch;
    do {
        if (*ptr == NULL) {
            printf("\n%*s No records found.\n", (SCREEN_WIDTH - 20) / 2, "");
            return;
        }
        system("clear");
        if (display_student_list(*ptr, rfid) != 1) return;

        int padding = (SCREEN_WIDTH - 31) / 2;
        printf("\n%*s+-------------------------------+\n", padding, "");
        printf("%*s|      STUDENT RECORD MENU      |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s| m/M : Modify A Record         |\n", padding, "");
        printf("%*s| d/D : Delete A Record         |\n", padding, "");
        printf("%*s| e/E : Exit                    |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s Enter Your Choice: ", padding, "");

        scanf(" %c", &ch);
        getchar(); // Consume newline character

        switch (tolower(ch)) {
            case 'm':
                printf("%*s Modify A Record\n", (SCREEN_WIDTH - 20) / 2, "");
                Modify_record(ptr, rfid);
                system("clear");
                display_student_list(*ptr, rfid);
                break;
            case 'd':
                printf("%*s Delete A Record\n", (SCREEN_WIDTH - 20) / 2, "");
                Delete_record(ptr, rfid);
                break;
            case 'e':
                Save_record(*ptr);
                usleep(50000);
                printf("%*s Exiting...\n", (SCREEN_WIDTH - 10) / 2, "");
                return;
            default:
                printf("%*s Invalid option\n", (SCREEN_WIDTH - 20) / 2, "");
                break;
        }

        printf("%*s Do you want to stay here? (y/n): ", (SCREEN_WIDTH - 32) / 2, "");
        scanf(" %c", &ch);
        getchar(); // Consume newline character
    } while (tolower(ch) == 'y');
	Save_record(*ptr);
        usleep(50000);
}
