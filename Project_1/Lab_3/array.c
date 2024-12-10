#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

int* bubbleSort(int arr[], int n) {
    int temp, i = 0, j = 0;
    int *s_arr = (int *) malloc(n * sizeof(int));

    // Copy arr to s_arr
    for(i = 0; i < n; i++)
        *(s_arr + i) = *(arr + i);

    // Outer loop: iterate through the entire array n-1 times
    for (i = 0; i < n - 1; i++) {
        // Inner loop: compare adjacent elements
        for(j = 0; j < n - 1; j++) {
            // Compares current element with the next element
            if(*(s_arr + j) > *(s_arr + j + 1)) {
                // Swaps elements if they are in the wrong order
                temp = *(s_arr + j + 1);        // Stores the smaller value in temp
                *(s_arr + j + 1) = *(s_arr + j);  // Moves the larger value to the right
                *(s_arr + j) = temp;            // Places the smaller value in the left position
            }
        }
        // After each iteration of the outer loop, the largest unsorted element
        // "bubbles up" to its correct position at the end of the array
    }

    // Comment out the original array notation version
    /*
    // Sorting using array notations
    for (i = 0; i < n - 1; i++) {
        for(j = 0; j < n - 1; j++) {
            if(s_arr[j] > s_arr[j + 1]) {
                temp = s_arr[j + 1];
                s_arr[j + 1] = s_arr[j];
                s_arr[j] = temp;
            }
        }
    }
    */

    return s_arr;
}

void printArray(int arr[], int n) {
    int i = 0;
    printf("[");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

int bSearch(int *arr, int a, int b, int key) {
    // Binary search function. arr is the array, key is the value to search for, a and b are the boundaries of arr to be searched within.
    // You must use pointer notations. i.e. no "[]"
    // Your code goes here:
    
    // Base case: if the search range is invalid, return -1 (not found)
    if (a > b) {
        return -1;
    }

    // Calculate the middle index
    int mid = a + (b - a) / 2;

    // If the middle element is the key, return its index
    if (*(arr + mid) == key) {
        return mid;
    }

    // If the key is smaller than the middle element, search the left half
    if (key < *(arr + mid)) {
        return bSearch(arr, a, mid - 1, key);
    }

    // If the key is larger than the middle element, search the right half
    return bSearch(arr, mid + 1, b, key);
}

int main() {
    int i = 0, size = 0, key = 0, result = 0;
    int *array, *sorted;

    printf("How big is your array?  ");
    while (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid input. Please enter a positive number: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    
    array = (int *) malloc(size * sizeof(int));

    for(i = 0; i < size; i++) {
        int valid_input = 0;
        do {
            printf("Please enter array[%d]:  ", i);
            if (scanf("%d", &array[i]) == 1) {
                valid_input = 1;
            } else {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (!valid_input);
    }

    printf("Please wait while I sort your numbers...\n");
    sorted = bubbleSort(array, size);
    printf("Here is your original array:\n");
    printArray(array, size);
    printf("Here is your SORTED array: \n");
    printArray(sorted, size);


//Test case for wrong number
    if (size > 0) {
        printf("What number are you looking for? ");
        while (scanf("%d", &key) != 1) {
            printf("Invalid input. Please enter a number: ");
            while (getchar() != '\n'); // Clear input buffer
        }
        printf("OK, let me see if I can find a \"%d\" in the array...\n", key);
        result = bSearch(sorted, 0, size-1, key);
        if(result != -1)
            printf("Got it! A \"%d\" is at index %d.\n", key, result);
        else
            printf("I'm sorry, a \"%d\" cannot be found in the array.\n", key);
    } else {
        printf("The array is empty, so we can't search for any numbers.\n");
    }

    // Don't forget to free allocated memory
    free(array);
    free(sorted);

    return 0;
}


