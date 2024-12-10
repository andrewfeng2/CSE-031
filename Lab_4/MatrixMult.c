#include <stdio.h>
#include <stdlib.h>

int** matMult(int **a, int **b, int size) {
	// (4) Implement your matrix multiplication here. 
	// You will need to create a new matrix to store the product.
	
	// Allocates memory for the result matrix
	int **result = (int **)malloc(size * sizeof(int *));
	
	// Iterates through rows of the result matrix
	for (int i = 0; i < size; i++) {
		// Allocates memory for each row of the result matrix
		*(result + i) = (int *)malloc(size * sizeof(int));
		
		// Iterates through columns of the result matrix
		for (int j = 0; j < size; j++) {
			// Initializes the current element to 0
			*(*(result + i) + j) = 0;
			
			// Performs dot product of row i from matrix a and column j from matrix b 1st row 1st column
			for (int k = 0; k < size; k++) {
				// Accumulates the product of corresponding elements
				*(*(result + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
			}
		}
	}
	return result;
}

// (2) Implement printArray function
void printArray(int **arr, int n) {
	
	// Iterates through rows of the matrix
	for (int i = 0; i < n; i++) {
		// Iterates through columns of the matrix
		for (int j = 0; j < n; j++) {
			// Prints each element with a space separator
			printf("%d ", *(*(arr + i) + j));
		}
		// Moves to the next line after printing a row
		printf("\n");
	}
	// Prints an extra newline for better formatting
	printf("\n");
}

//funciton for testing for valid input
int getValidInput() {
    int value;
    char check;
    
    // Keep looping until valid input is received
    while (1) {
        // Try to read an integer followed by a character
        if (scanf("%d%c", &value, &check) == 2 && check == '\n') {
            // If successful and the character is a newline, input is valid
            return value;
        } else {
            // If input is invalid, print an error message
            printf("Invalid input. Please enter a number: ");
            
            // Clear the input buffer to prevent infinite loop
            while (getchar() != '\n');
        }
    }
}

int main() {
	int n;
	int **matA, **matB, **matC;
	
	// Get matrix size from user
	printf("Enter the size of the matrices (n x n): ");
	n = getValidInput();
	
	// Ensure n is positive
	while (n <= 0) {
		printf("Invalid size. Please enter a positive number: ");
		n = getValidInput();
	}
	
	// 1) Allocates memory for matA and matB
	matA = (int **)malloc(n * sizeof(int *));
	matB = (int **)malloc(n * sizeof(int *));
	
	// Input values for Matrix A
	printf("Enter values for Matrix A (%d x %d):\n", n, n);
	for (int i = 0; i < n; i++) {
		// Allocate memory for each row of Matrix A
		*(matA + i) = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			// Prompt user for each element of Matrix A
			printf("A[%d][%d]: ", i, j);
			// Use getValidInput() to ensure valid integer input
			*(*(matA + i) + j) = getValidInput();
		}
	}
	
	// Input values for Matrix B
	printf("Enter values for Matrix B (%d x %d):\n", n, n);
	for (int i = 0; i < n; i++) {
		// Allocate memory for each row of Matrix B
		*(matB + i) = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			// Prompt user for each element of Matrix B
			printf("B[%d][%d]: ", i, j);
			// Use scanf() to read input (Note: This doesn't validate input like getValidInput())
			scanf("%d", *(matB + i) + j);
		}
	}

	// (3) Call printArray to print out the 2 arrays here.
	printf("Matrix A:\n");
	printArray(matA, n);
	printf("Matrix B:\n");
	printArray(matB, n);
	
	// ->(5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);
	
	// ->(6) Call printArray to print out resulting array here.
	printf("Result Matrix C (A * B):\n");
	printArray(matC, n);

	// Free allocated memory
	for (int i = 0; i < n; i++) {
		free(*(matA + i));
		free(*(matB + i));
		free(*(matC + i));
	}
	free(matA);
	free(matB);
	free(matC);

	return 0;
}