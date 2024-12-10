#include <stdio.h>
#include <stdlib.h>

int main() {
    int repetitions;
    int typo_line;
    char input[100];  // Buffer for input

    do {
        printf("Enter the repetition count for the punishment phrase: "); //Gets punishment phrase
        fgets(input, sizeof(input), stdin);
        repetitions = atoi(input); //Convert input string to integer
        if (repetitions <= 0) {
            printf("You entered an invalid value for the repetition count! Please re-enter:\n");
        }
    } while (repetitions <= 0);

    do {
        printf("Enter the line where you want to insert the typo: ");
        fgets(input, sizeof(input), stdin); //Reads user input into buffer
        typo_line = atoi(input); //converts input string to an integer
        if (typo_line <= 0 || typo_line > repetitions) {   //Check if the input is valid (greater than 0 and less than or equal to repetitions)
            printf("You entered an invalid value for the typo placement! Please re-enter:\n");
        }
    } while (typo_line <= 0 || typo_line > repetitions);

    // Print punishment phrases
    for (int i = 1; i <= repetitions; i++) {
        if (i == typo_line) { //Checks if the current line is the one for the typo
            printf("Cading wiht is C avesone!\n");
        } else {
            printf("Coding with C is awesome!\n");
        }
    }

    return 0;
}