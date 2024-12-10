#You may NOT use any the following instructions in your solution: div, and, or, andi, or ori
.data
    prompt:     .asciiz "Please enter a number: "
    even_msg:   .asciiz "Sum of even numbers is: "
    odd_msg:    .asciiz "Sum of odd numbers is: "
    newline:    .asciiz "\n"

.text
.globl main

main:
    # Initialize even_sum and odd_sum to 0
    li $t0, 0       # $t0 will store the sum of even numbers
    li $t1, 0       # $t1 will store the sum of odd numbers

input_loop:
    # Print prompt message
    li $v0, 4       # System call code for printing string
    la $a0, prompt  # Load address of prompt string
    syscall         # Make system call to print

    # Read integer input from user
    li $v0, 5       # System call code for reading integer
    syscall
    move $t2, $v0   # Store input in $t2

    # Check if input is 0 (exit condition)
    beq $t2, $zero, print_results  # If input is 0, branch to print_results

    # Check if input is negative
    slt $t3, $t2, $zero     # Set $t3 to 1 if input is negative
    beq $t3, $zero, positive_number  # If not negative, proceed as normal
    
    # Make negative number positive for checking even/odd
    sub $t2, $zero, $t2     # $t2 = 0 - $t2 (makes positive)

positive_number:
    # Check if number is even or odd by repeatedly subtracting 2
    move $t4, $t2           # Copy number to work with
    li $t5, 2              # Load 2 for subtraction

check_loop:
    slt $t6, $t4, $t5      # Check if remaining value < 2
    bne $t6, $zero, check_remainder  # If less than 2, check remainder
    sub $t4, $t4, $t5      # Subtract 2
    j check_loop

check_remainder:
    beq $t4, $zero, is_even  # If remainder is 0, number is even
    li $t6, 1
    beq $t4, $t6, is_odd    # If remainder is 1, number is odd

is_even:
    beq $t3, $zero, add_even  # If original number was positive, add to even sum
    sub $t2, $zero, $t2      # Make number negative again
    j add_even

is_odd:
    beq $t3, $zero, add_odd   # If original number was positive, add to odd sum
    sub $t2, $zero, $t2       # Make number negative again
    j add_odd

add_odd:
    add $t1, $t1, $t2  # Add input to odd sum
    j input_loop       # Jump back to input_loop

add_even:
    add $t0, $t0, $t2  # Add input to even sum
    j input_loop       # Jump back to input_loop

print_results:
    # Print even sum message
    li $v0, 4          # System call code for printing string
    la $a0, even_msg   # Load address of even_msg string
    syscall            # Make system call to print

    # Print even sum value
    li $v0, 1          # System call code for printing integer
    move $a0, $t0      # Move even sum to $a0 for printing
    syscall            # Make system call to print

    # Print newline
    li $v0, 4          # System call code for printing string
    la $a0, newline    # Load address of newline string
    syscall            # Make system call to print

    # Print odd sum message
    li $v0, 4          # System call code for printing string
    la $a0, odd_msg    # Load address of odd_msg string
    syscall            # Make system call to print

    # Print odd sum value
    li $v0, 1          # System call code for printing integer
    move $a0, $t1      # Move odd sum to $a0 for printing
    syscall            # Make system call to print

    # Exit program
    li $v0, 10         # System call code for program exit
    syscall            # Make system call to exit
