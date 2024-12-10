.data
    prompt: .asciiz "Please enter a number: "

.text
.globl main

main:
    # Print prompt
    li $v0, 4
    la $a0, prompt
    syscall
    
    # Read integer
    li $v0, 5
    syscall
    
    # Move input to $a0 for recursion function
    move $a0, $v0
    
    # Call recursion function
    jal recursion
    
    # Print result
    move $a0, $v0
    li $v0, 1
    syscall
    
    # Print newline
    li $a0, 10
    li $v0, 11
    syscall
    
    # Exit program
    li $v0, 10
    syscall

recursion:
    # Save return address and s registers
    addi $sp, $sp, -12
    sw $ra, 8($sp)
    sw $s0, 4($sp)
    sw $s1, 0($sp)
    
    # Save m in s0
    move $s0, $a0
    
    # Check if m == -1
    li $t0, -1
    beq $s0, $t0, return_3
    
    # Check if m <= -2
    li $t0, -2
    bgt $s0, $t0, recursive_case
    
    # Handle m <= -2 cases
    blt $s0, $t0, return_2
    li $v0, 1        # return 1 when m == -2
    j recursion_end
    
return_2:
    li $v0, 2
    j recursion_end
    
return_3:
    li $v0, 3
    j recursion_end
    
recursive_case:
    # First recursive call: recursion(m-3)
    addi $a0, $s0, -3
    jal recursion
    move $s1, $v0    # save result
    
    # Second recursive call: recursion(m-2)
    addi $a0, $s0, -2
    jal recursion
    
    # Calculate final result: recursion(m-2) + recursion(m-3) + m
    add $v0, $v0, $s1    # Add recursion(m-3)
    add $v0, $v0, $s0    # Add m
    
recursion_end:
    # Restore registers
    lw $s1, 0($sp)
    lw $s0, 4($sp)
    lw $ra, 8($sp)
    addi $sp, $sp, 12
    
    jr $ra