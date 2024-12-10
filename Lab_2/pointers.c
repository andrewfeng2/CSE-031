#include <stdio.h>
int main() {
    int x=0, y=0, *px, *py;
    int arr[10]={0};

    // Print the values of x, y, and arr[0]
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    printf("arr[0]: %d\n", arr[0]);


    // Print addresses of x and y
    printf("Address of x: %p\n", (void*)&x);
    printf("Address of y: %p\n", (void*)&y);


    px=&x;
    py=&y;

    printf("Value of px: %p, Address of px: %p\n", (void*)px, (void*)&px);
    printf("Value of py: %p, Address of py: %p\n", (void*)py, (void*)&py);

    // Print contents of arr using pointer arithmetic
    for (int i = 0; i < 10; i++) {
        printf("arr[%d]: %d\n", i, *(arr + i)); // Accessing array using pointer
    }


    printf("Address of arr: %p\n", (void*)arr); // Address of the array
    printf("Address of first element (arr[0]): %p\n", (void*)&arr[0]); // Address of the first element

     if ((void*)arr == (void*)&arr[0]) {
        printf("arr points to the address of arr[0].\n");
    } else {
        printf("arr does not point to the address of arr[0].\n");
    }

    return 0;
}