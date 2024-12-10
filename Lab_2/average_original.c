#include <stdio.h>

/*
 * Read a set of values from the user.
 * Store the sum in the sum variable and return the number of values read.
 */

/* 
 * You CANNOT declare any global variables.
 * DO NOT change the definition of the read_values function when it comes to 
 * adding/removing function parameters, or changing its return type. You may, 
 * however, modify the single function parameter and the body of the function if 
 * you wish. 

 * Use GDB or LLDB to discover and fix errors.
 */



//for no ampersand 
// lldb average_original
// b main
// run
//c 
//bt or backtrace

//reasoning behind error: crashed due to bad access error, access memory it shouldn't have
// the problem is passing input directly into scanf. The scanf needs the memory address of
// where to store the input not the value itself 

//lldb average_original
// b average_original.c: 55   or breakpoint set --line 55 
// run 
// n
// add inputs
// "n" until you get to read_values
// If it says 0 it is not working which you want
// p sum 


int read_values(double sum) {
  int values = 0, input = 0;
  sum = 0;
  printf("Enter input values (enter 0 to finish):\n");
  scanf("%d", &input);
  while(input != 0) {
    values++;
    sum += input;
    scanf("%d", input); //&input for fixed
  }
  return values;
}

int main() {
  double sum = 0;
  int values;
  values = read_values(sum);
  printf("\nAverage: %g\n", sum/values); // Hint: How do we ensure that sum is updated here 
                                         // AFTER read_values() manipulates it?
                                         // Make sure to use GDB or LLDB for this.
  return 0;
}

