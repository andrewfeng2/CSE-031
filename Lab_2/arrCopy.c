#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int size; // Variable to record size of original array arr
int evenCount = 0, oddCount = 0; // Variables to record sizes of new arrays arr_even and arr_odd
int *arr; // Dynamically allocated original array with #elements = size
int *arr_even;  // Dynamically allocated array with #elements = #even elements in arr (evenCount)
int *arr_odd;   // Dynamically allocated array with #elements = #odd elements in arr (oddCount)
char *str1 = "Original array's contents: ";
char *str2 = "Contents of new array containing even elements from original: ";
char *str3 = "Contents of new array containing odd elements from original: ";

/*
 * DO NOT change the definition of the printArr function when it comes to 
 * adding/removing/modifying the function parameters, or changing its return 
 * type. 
 */
void printArr(int *a, int size, char *prompt){
    printf("%s", prompt); //pirnts prompt message
    if (size == 0) { //Checks to see if array is empty
        printf("empty\n");
    } else {
        // if not then iterate through array and print each element 
        for (int i = 0; i < size; i++) {
            printf("%d ", *(a + i)); //prints each element 
        }
        printf("\n");
    }
}

/* 
 * DO NOT change the definition of the arrCopy function when it comes to 
 * adding/removing/modifying the function parameters, or changing its return 
 * type. 
 */
void arrCopy(){
    // Initializes counters for even and odd arrays
    int i, evenIndex = 0, oddIndex = 0;

    //Iterates thorugh original array
    for (i = 0; i < size; i++) {
       
        if (*(arr + i) % 2 == 0) {  //This code checks if it is even
            *(arr_even + evenIndex) = *(arr + i); //If even, it copies arr_even and incraments evenIndex
            evenIndex++;
        } else {
            //If odd, copies arr_odd and incrmemnts oddIndex 
            *(arr_odd + oddIndex) = *(arr + i);
            oddIndex++;
        }
    }
}

int main(){
    int i;
    printf("Enter the size of array you wish to create: ");
    scanf("%d", &size);

    // Dynamically allocate memory for arr (of appropriate size)
    arr = (int *)malloc(size * sizeof(int));

    // Ask user to input content of arr and compute evenCount and oddCount
    for (i = 0; i < size; i++) {
        printf("Enter array element #%d: ", i + 1);
        scanf("%d", arr + i);
        if (*(arr + i) % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    // Dynamically allocate memory for arr_even and arr_odd (of appropriate size)
    arr_even = (int *)malloc(evenCount * sizeof(int));
    arr_odd = (int *)malloc(oddCount * sizeof(int));

/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/

	// Print original array
    printArr(arr, size, str1);

	/// Copy even elements of arr into arr_even and odd elements into arr_odd
    arrCopy();

    // Print new array containing even elements from arr
    printArr(arr_even, evenCount, str2);

    // Print new array containing odd elements from arr
    printArr(arr_odd, oddCount, str3);

    printf("\n");

    return 0;
}