#include "header.h"

void Modify_record(SDB **ptr)
{
    char op;

    menu3();
    scanf(" %c", &op);

    op = tolower(op);

    switch (op)
    {
    case 'r':
        mod_rollno(ptr);
        break;
    case 'n':
        mod_name(*ptr);
        mod_rollno(ptr);
        break;
    case 'p':
        mod_per(*ptr);
        mod_rollno(ptr);
        break;
    }
}

void mod_name(SDB *ptr)
{
    char input_name[20];
    printf("\n\tEnter your name: ");
    scanf(" %[^\n]", input_name);

    for (int i = 0; input_name[i]; i++)
    {
        input_name[i] = tolower(input_name[i]);
    }

    printf("\tRoll.No\t\tName\t\tPercentage\n");

    SDB *current = ptr;
    while (current != NULL)
    {
        char temp_name[20];
        strcpy(temp_name, current->name);
        for (int i = 0; temp_name[i]; i++)
        {
            temp_name[i] = tolower(temp_name[i]);
        }

        if (strcmp(temp_name, input_name) == 0)
        {
            printf("\t%d\t\t%s\t\t%d\n", current->rollno, current->name, current->percentage);
        }
        current = current->next;
    }

    sleep(1);
}

void mod_per(SDB *ptr)
{
    int input_percentage;
    printf("\n\tEnter your percentage: ");
    scanf(" %d", &input_percentage);

    printf("\tRoll.No\t\tName\t\tPercentage\n");
    SDB *current = ptr;
    while (current != NULL)
    {
        if (input_percentage == current->percentage)
        {
            printf("\t%d\t\t%s\t\t%d\n", current->rollno, current->name, current->percentage);
        }
        current = current->next;
    }

    sleep(1);
}

void mod_rollno(SDB **ptr)
{
    int rollno, percentage;
    char op, name[20];

    printf("\n\tEnter your Rollno : ");
    scanf("%d", &rollno);

    SDB *current = *ptr;
    SDB *previous = NULL;

    while (current != NULL && current->rollno != rollno)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL)
    {
        /*if (previous == NULL) {
            *ptr = current->next;
        } else {
            previous->next = current->next;
        }*/
        percentage = current->percentage;
        strcpy(name, current->name);
        menu6();
        scanf(" %c", &op);

        switch (op)
        {
        case 'n':
            printf("Enter your name : ");
            scanf(" %[^\n]", name);
            break;

        case 'p':
            printf("Enter your percentage : ");
            scanf("%d", &percentage);
            break;
        }

        current->percentage = percentage;
        strcpy(current->name, name);

        usleep(500);
        printf("Roll no: %d is Modfified Successfully\n", rollno);
    }
    else
    {
        usleep(500);
        printf("Roll no: %d not found!\n", rollno);
    }

    sleep(1);
}

void menu6()
{
    printf("\t  N/n : Enter Name To Modify\n");
    printf("\t  P/p : Enter Percentage To Modify\n");
    printf("\t  Enter : ");
}
