//    ./wordsearch puzzle1.txt
//    ./wordsearch puzzle2.txt
//    ./wordsearch puzzle3.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize; // Global variable to store the size of the puzzle

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Add input validation for the word
    int wordLength = strlen(word);
    int isValid = 1;
    for (int i = 0; i < wordLength; i++) {
        // Check if each character is alphabetic (uppercase or lowercase)
        if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))) {
            isValid = 0;
            break;
        }
    }

    // If the word is not valid, print an error message and clean up memory
    if (!isValid) {
        printf("Error: Invalid input. The word should contain only alphabetic characters.\n");
        free(word);
        for (int i = 0; i < bSize; i++) {
            free(*(block + i));
        }
        free(block);
        return 1;
    }
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    // Free allocated memory
    free(word);
    for (int i = 0; i < bSize; i++) {
        free(*(block + i));
    }
    free(block);
    
    return 0;
}

void printPuzzle(char** arr) {
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            // Print each character in the 2D array with a space
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

int isValidMove(int row, int col) {
    return (row >= 0 && row < bSize && col >= 0 && col < bSize);
}

int charEquals(char a, char b) {
    return (a == b) || (a + 32 == b) || (a == b + 32);
}

int searchWord(char** arr, char* word, int row, int col, int index, int** path) {
    // Base case: if we've reached the end of the word, we've found it
    if (*(word + index) == '\0')
        return 1;
    
    // Check if the current position is valid and matches the current letter
    if (!isValidMove(row, col) || !charEquals(*(*(arr + row) + col), *(word + index)))
        return 0;

    // Define all 8 possible directions to move
    int directions[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    
    // Update path with current index
    *(*(path + row) + col) |= (1 << index);
    
    // Loop through all 8 possible directions (diagonal, horizontal, and vertical)
    for (int i = 0; i < 8; i++) {
        // Calculate the new position by adding the direction offsets
        // directions[i][0] contains the row offset (-1, 0, or 1)
        // directions[i][1] contains the column offset (-1, 0, or 1)
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        
        // Recursively search for the next letter in the word
        // Parameters:
        // - arr: the puzzle grid
        // - word: the word we're searching for
        // - newRow, newCol: the next position to check
        // - index + 1: move to the next letter in the word
        // - path: keeps track of the successful path
        // If any direction returns 1, we've found a complete path
        if (searchWord(arr, word, newRow, newCol, index + 1, path))
            return 1;
    }
    
    // Remove current index from path if backtracking
    *(*(path + row) + col) &= ~(1 << index);
    return 0;
}

void searchPuzzle(char** arr, char* word) {
    // Allocate a 2D array to store the path/sequence of found letters
    // Each cell will use bits to mark which position in the word was found there
    int** path = (int**)malloc(bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        // Initialize each row with zeros using calloc
        *(path + i) = (int*)calloc(bSize, sizeof(int));
    }

    // Flag to track if the word was found
    int found = 0;
    
    // Try starting the search from every position in the puzzle
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            // searchWord returns 1 if word is found starting at this position
            if (searchWord(arr, word, i, j, 0, path)) {
                found = 1;
            }
        }
    }

    if (found) {
        printf("Word found!\n");
        printf("Printing the search path:\n");
        // Print the path matrix
        for (int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                if (*(*(path + i) + j) == 0) {
                    // Print 0 for unused positions
                    printf("%-8d", 0);
                } else {
                    int value = 0;
                    // Convert the bit representation back to sequence numbers
                    // For example, if bits 0 and 2 are set, this was the 1st and 3rd letter
                    for (int k = strlen(word) - 1; k >= 0; k--) {
                        if (*(*(path + i) + j) & (1 << k)) {
                            value = value * 10 + (k + 1);
                        }
                    }
                    // Print the sequence number(s) for this position
                    printf("%-8d", value);
                }
            }
            printf("\n");
        }
    } else {
        printf("Word not found!\n");
    }

    // Clean up allocated memory
    for (int i = 0; i < bSize; i++) {
        free(*(path + i));
    }
    free(path);
}

