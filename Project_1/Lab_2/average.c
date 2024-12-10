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

// lldb average
// breakpoint set --line 38
// run
// n
// p sum 
int read_values(double *sum) {
  int values = 0;
  double input = 0; //truned input into double for better percision
  *sum = 0; //made sum a pointer
  printf("Enter input values (enter 0 to finish):\n");
  scanf("%lf", &input);
  while(input != 0) {
    values++;
    *sum += input;
    scanf("%lf", &input); //changed to %lf and reference pointer for input
  }
  return values;
}

int main() {
  double sum = 0;
  int values;
  values = read_values(&sum); //pass sum by reference instead of by value
  printf("\nAverage: %g\n", sum/values);
  return 0;
}

