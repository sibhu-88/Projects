#include "header.h"

void Save_record(SDB *ptr) {
    FILE *file = fopen("student.xls", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write header only once
    fprintf(file, "RFID\tRoll.No\tName\tPercentage\n");

    SDB *current = ptr;
    while (current) {
        fprintf(file, "%s\t%d\t%s\t%.1f\n", current->RFID, current->rollno, current->name, current->percentage);
        current = current->next;
    }

    fclose(file);
    printf("%*s File is saving...\n", (80 - 10) / 2, "");
    sleep(1);
}

void read_records_from_file(SDB **ptr) {
    FILE *file = fopen("student.xls", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file 'student.xls'.\n");
        return; // No file, no records
    }

    char line[256];

    // Skip the header line
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        SDB *temp = (SDB *)malloc(sizeof(SDB));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed.\n");
            fclose(file);
            return;
        }

        // Parsing with sscanf to extract data
        if (sscanf(line, "%12s\t%d\t%49[^\t]\t%f", temp->RFID, &temp->rollno, temp->name, &temp->percentage) != 4) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            free(temp);
            continue;
        }

        temp->next = NULL;

        // Add new record to the linked list
        if (*ptr == NULL) {
            *ptr = temp; // First record
        } else {
            SDB *last = *ptr;
            while (last->next) {
                last = last->next;
            }
            last->next = temp; // Link new record
        }
    }

    fclose(file);
}
