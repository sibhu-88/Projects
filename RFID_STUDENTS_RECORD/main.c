#include "header.h"

#define SCREEN_WIDTH 80  // Define the width of the terminal screen

int main() {
    char ch;

    do {
        system("clear");
        printf("\n");

        int padding;

        padding = (SCREEN_WIDTH - 31) / 2; // Adjust padding for different lengths
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s|      STUDENT RECORD MENU      |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s| a/A : Add New Record          |\n", padding, "");
        printf("%*s| s/S : Scan the Student        |\n", padding, "");
        printf("%*s| e/E : Exit                    |\n", padding, "");
        printf("%*s+-------------------------------+\n", padding, "");
        printf("%*s Enter Your Choice: ", padding, "");

        scanf(" %c", &ch);
        getchar(); // Consume newline character

        switch (tolower(ch)) {
            case 'a':
                padding = (SCREEN_WIDTH - 20) / 2;
                printf("\n%*s Add your Data :\n\n", padding, "");
                break;
            case 'e':
                padding = (SCREEN_WIDTH - 9) / 2;
                printf("\n%*s Exiting...\n", padding, "");
                exit(0);
            default:
                padding = (SCREEN_WIDTH - 19) / 2;
                printf("\n%*s Invalid option\n", padding, "");
                break;
        }

        padding = (SCREEN_WIDTH - 32) / 2;
        printf("\n%*s Do you want to try again? (y/n): ", padding, "");
        scanf(" %c", &ch);
        getchar(); // Consume newline character
    } while (tolower(ch) == 'y');

    return 0;
}

        print_centered("\t Do you want to stay here? (y/n): ");
        scanf(" %c", &ch);
    } while (tolower(ch) == 'y');
}
