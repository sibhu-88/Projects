#include "header.h"

#define HEADER_ROW "\t+--------------+---------+---------------------+-------------+\n"
#define STUDENT_HEADER "\t| RFID         | Roll.No | Name                | Percentage  |\n"

void display_students_list(SDB *ptr) {
    if (!ptr) {
        printf("\n\tNo records found.\n");
        return;
    }

    printf("\n%s", HEADER_ROW);
    printf("\t|                 STUDENTS LIST                              |\n");
    printf("%s", HEADER_ROW);
    printf("%s", STUDENT_HEADER);
    printf("%s", HEADER_ROW);

    while (ptr) {
        printf("\t| %-12s | %-7d | %-19s | %-11.2f |\n", 
                ptr->RFID, ptr->rollno, ptr->name, ptr->percentage);
        ptr = ptr->next;
    }
    printf("%s\n", HEADER_ROW);
}

int display_student_list(SDB *ptr, char *RFID) {
    if (!ptr) {
        printf("\n\tNo records found.\n");
        return 0;
    }

    while (ptr) {
        if (strncmp(ptr->RFID, RFID, 12) == 0) {
            printf("\n%s", HEADER_ROW);
            printf("\t|               STUDENT RECORD                |\n");
            printf("%s", HEADER_ROW);
            printf("\t| Roll.No | Name                | Percentage  |\n");
            printf("%s", HEADER_ROW);
            printf("\t| %-7d | %-21s | %-11.2f |\n", 
                    ptr->rollno, ptr->name, ptr->percentage);
            printf("%s\n", HEADER_ROW);
            return 1; // Found
        }
        ptr = ptr->next;
    }

    printf("\n\n\tNo matching records found for RFID: %s \n\n", RFID);
    return 0;
}
