#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20

struct marks {
    int sub1;
    int sub2;
    int sub3;
    int total;
    int percentage;
};

typedef struct student {
    int id;
    char name[MAX_NAME_LENGTH];
    struct marks mark;
    struct student *next;  // Corrected typo (next instead of nxt)
} Student;

// Function prototypes (declared before main)
void create_student_list(Student **head_ptr);
void display_student_data(Student *head);
void calculate_marks(Student *student);
int get_valid_int(const char *prompt);  // Function to get valid integer input

int main() {
    Student *head = NULL;  // Initialize head of the linked list

    int choice;
    char option;

    do {
        printf("\nStudent Management System\n");
        printf("1) Add Student Data\n");
        printf("2) Display Student Data\n");
        printf("3) Exit\n");

        choice = get_valid_int("Enter your choice: ");

        switch (choice) {
            case 1:
                create_student_list(&head);
                break;
            case 2:
                display_student_data(head);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &option);  // Use space before %c to avoid issues
    } while (option == 'y' || option == 'Y');

    // Free memory allocated for the linked list (optional)
    Student *temp = head;
    while (temp != NULL) {
        Student *next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}

void create_student_list(Student **head_ptr) {
    Student *new_student = (Student *)malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Student Details:\n");
    printf("ID: ");
    new_student->id = get_valid_int("Enter ID: ");

    printf("Name: ");
    scanf(" %[^\n]",new_student->name);
    
    printf("Marks:\n");
    new_student->mark.sub1 = get_valid_int("Enter marks for Subject 1: ");
    new_student->mark.sub2 = get_valid_int("Enter marks for Subject 2: ");
    new_student->mark.sub3 = get_valid_int("Enter marks for Subject 3: ");

    calculate_marks(new_student);  // Calculate total and percentage

    // Insert the new student at the beginning of the list
    new_student->next = *head_ptr;
    *head_ptr = new_student;
}

void calculate_marks(Student *student) {
    student->mark.total = student->mark.sub1 + student->mark.sub2 + student->mark.sub3;
    student->mark.percentage = (student->mark.total * 100) / 300;
}

void display_student_data(Student *head) {
    if (head == NULL) {
        printf("No student data found.\n");
        return;
    }

    printf("\n\t\tStudent Data:\n");
    printf("\tID\tNAME\t\tSUB1\tSUB2\tSUB3\tTOTAL\tPERSENTAGE\n");
    while (head != NULL) {
        printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%d%%\n",
               head->id, head->name, head->mark.sub1, head->mark.sub2,
               head->mark.sub3, head->mark.total, head->mark.percentage);
        head = head->next;
    }
}

// Definition of get_valid_int function
int get_valid_int(const char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            return value;
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            fflush(stdin);  // Clear the input buffer
        }
    }
}
