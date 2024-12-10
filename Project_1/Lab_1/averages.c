#include <stdio.h>
#include <stdlib.h> //library for memory allocaiton, process contorl

// Function to calculate the sum of digits of a number
int sum_of_digits(int num) {
    int sum = 0;
    // Take absolute value (handle negative numbers)
    for (num = abs(num); num > 0; num /= 10) {
        sum += num % 10;  // Add the rightmost digit to sum
        // num /= 10 removes the rightmost digit for the next iteration
    }
    return sum;
}

int main() {
    int count = 0, even_count = 0, odd_count = 0;
    double even_sum = 0, odd_sum = 0, input;

    while (1) {  // Infinite loop, broken when input is 0
        count++;  // Increment count before using it
        printf("Enter the %d%s value: ", count, 
               // Ternary operators (alternative to if else) to determine correct suffix
               (count % 10 == 1 && count % 100 != 11) ? "st" :  // e.g., 1st, 21st, 31st, but not 11th
               (count % 10 == 2 && count % 100 != 12) ? "nd" :  // e.g., 2nd, 22nd, 32nd, but not 12th
               (count % 10 == 3 && count % 100 != 13) ? "rd" :  // e.g., 3rd, 23rd, 33rd, but not 13th
               "th");  // Default case for all other numbers
        
        // Reads input check for validity
        if (scanf("%lf", &input) != 1) {  // scanf returns number of successfully read items
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer to prevent infinite loop
            count--;  // Decrement count to retry this number
            continue;  // Skip rest of loop and start over
        }

        // Check for termination condition
        if (input == 0) break;  // Exit loop if input is 0

        // Calculate sum of digits and categorize input
        int digit_sum = sum_of_digits((int)input);
        if (digit_sum % 2 == 0) {  // Check if sum of digits is even
            even_sum += input;
            even_count++;
        } else {  // If sum of digits is odd
            odd_sum += input; //Add the current input to the sum of odd inputs 
            odd_count++; //Incrment the count of odd inputs
        }
    }

    // Print results
    if (count == 1) {  // If only 0 was entered
        printf("There is no average to compute.\n");
    } else {
        // Print average for numbers with even digit sum, if any
        if (even_count > 0) {
            printf("Average of input values whose digits sum up to an even number: %.2f\n", even_sum / even_count);
        }
        // Print average for numbers with odd digit sum, if any
        if (odd_count > 0) {
            printf("Average of input values whose digits sum up to an odd number: %.2f\n", odd_sum / odd_count);
        }
    }

    return 0;  // Indicate successful program execution
}
