#include "header.h"

void Save_record(SDB *ptr)
{
    FILE *file = fopen("student.xls", "w");
    if (file == NULL)
    {
        perror("Unable to open file");
        return;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "Roll.No\t\tName\t\tPercentage\n");
    }
    SDB *current = ptr;
    while (current != NULL)
    {
        fprintf(file, "%d\t\t%s\t\t%d\n", current->rollno, current->name, current->percentage);
        current = current->next;
    }

    fclose(file);
    sleep(1);
    printf("File Saved successfully..\n");
    sleep(1);
}
