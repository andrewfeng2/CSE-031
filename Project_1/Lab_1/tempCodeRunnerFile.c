#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_valid_input(const char* prompt, int min, int max) {
    char input[100];
    int value;

    do {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        value = atoi(input);
        if (value < min || value > max) {
            printf("You entered an invalid value! Please re-enter.\n");
        }
    } while (value < min || value > max);

    return value;
}

int main() {
    int repetitions = get_valid_input("Enter the repetition count for the punishment phrase: ", 1, INT_MAX);
    int typo_line = get_valid_input("Enter the line where you want to insert the typo: ", 1, repetitions);

    // Print punishment phrases
    for (int i = 1; i <= repetitions; i++) {
        if (i == typo_line) {
            printf("Cading wiht is C avesone!\n");
        } else {
            printf("Coding with C is awesome!\n");
        }
    }

    return 0;
}