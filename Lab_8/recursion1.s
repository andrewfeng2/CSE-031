.data
    # Define the string that will prompt the user for input
    prompt: .asciiz "Please enter a number: "

.text
.globl main

main:
    # Print the prompt message to console
    li $v0, 4           # System call code 4 for printing string
    la $a0, prompt      # Load address of prompt into $a0
    syscall
    
    # Get integer input from user
    li $v0, 5           # System call code 5 for reading integer
    syscall             # Result will be stored in $v0
    
    # Prepare for function call
    move $a0, $v0       # Move input number to $a0 as argument for recursion
    
    # Call the recursive function
    jal recursion       # Jump and link to recursion function
    
    # Print the result returned from recursion
    move $a0, $v0       # Move result to $a0 for printing
    li $v0, 1           # System call code 1 for printing integer
    syscall
    
    # Print newline character for clean output
    li $a0, 10          # ASCII code 10 = newline character
    li $v0, 11          # System call code 11 for printing character
    syscall
    
    # Terminate program
    li $v0, 10          # System call code 10 for exit
    syscall

recursion:
    # Setup stack frame to store return address and saved registers
    addi $sp, $sp, -16  # Allocate space for 4 words on stack 
    sw $ra, 12($sp)     # Save return address
    sw $s0, 8($sp)      # Save $s0 (will hold input value m)
    sw $s1, 4($sp)      # Save $s1 (will hold first recursive result)
    sw $fp, 0($sp)      # Save frame pointer (added)
    move $fp, $sp       # Set up frame pointer (added)
    
    # Save input parameter
    move $s0, $a0       # Save input value m in $s0
    
    # Handle base cases:
    # This function implements the following logic:
    # if m == -1: return 3
    # if m == -2: return 1
    # if m < -2: return 2
    # else: return recursion(m-2) + recursion(m-3) + m
    
    # Check first base case: m == -1
    li $t0, -1
    beq $s0, $t0, return_3    # If m == -1, return 3
    
    # Check remaining base cases
    li $t0, -2
    bgt $s0, $t0, recursive_case    # If m > -2, do recursive case
    
    # Handle m <= -2 cases
    blt $s0, $t0, return_2    # If m < -2, return 2
    li $v0, 1                 # If m == -2, return 1
    j recursion_end
    
return_2:
    li $v0, 2                 # Return value 2 for m < -2
    j recursion_end
    
return_3:
    li $v0, 3                 # Return value 3 for m == -1
    j recursion_end
    
recursive_case:
    # Calculate recursion(m-3)
    addi $a0, $s0, -3        # Prepare m-3 as argument
    jal recursion            # First recursive call
    move $s1, $v0            # Save result of recursion(m-3)
    
    # Calculate recursion(m-2)
    addi $a0, $s0, -2        # Prepare m-2 as argument
    jal recursion            # Second recursive call
    
    # Calculate final result: recursion(m-2) + recursion(m-3) + m
    add $v0, $v0, $s1        # Add result of recursion(m-3)
    add $v0, $v0, $s0        # Add original input value m
    
recursion_end:
    # Restore saved registers and return address
    lw $fp, 0($sp)      # Restore frame pointer (added)
    lw $s1, 4($sp)      # Restore $s1
    lw $s0, 8($sp)      # Restore $s0
    lw $ra, 12($sp)     # Restore return address
    addi $sp, $sp, 16   # Deallocate stack space (adjusted)
    
    jr $ra              # Return to caller