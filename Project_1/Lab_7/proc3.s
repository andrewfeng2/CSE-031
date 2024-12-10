.data
str1: .asciiz "p + q: "
str2: .asciiz "\n"

.text
.globl main

# main function
main: 
    # Prologue
    addiu $sp, $sp, -16    # Make space for 4 words
    sw $ra, 12($sp)        # Save return address
    sw $s0, 8($sp)         # Save s0 (will stores x)
    sw $s1, 4($sp)         # Save s1 (will store y)
    sw $s2, 0($sp)         # Save s2 (will storez)

    # Initialize x, y, z
    li $s0, 2              # x = 2
    li $s1, 4              # y = 4
    li $s2, 6              # z = 6

    # Prepare arguments for foo(x, y, z)
    move $a0, $s0          # m = x (first argument = x)
    move $a1, $s1          # n = y (Second argument =y )
    move $a2, $s2          # o = z (Thrid argument = z)
    
    jal foo                # Call foo function 

    # Calculate z = x + y + z + foo(x,y,z)
    add $t0, $s0, $s1      # t0 = x + y
    add $t0, $t0, $s2      # t0 += original z
    add $t0, $t0, $v0      # t0 += result from foo
    move $s2, $t0          # (store final result in z)

    # Print final result
    li $v0, 1              #system call code for print integer
    move $a0, $s2          # Load value to print 
    syscall                # Print the integer

    # Print newline
    li $v0, 4
    la $a0, str2
    syscall

    # Epilogue
    lw $s2, 0($sp)
    lw $s1, 4($sp)
    lw $s0, 8($sp)
    lw $ra, 12($sp)
    addiu $sp, $sp, 16      # Deallocate stack space
    
    li $v0, 10            # Exit program
    syscall

# foo function 
foo:
    # Prologue
    addiu $sp, $sp, -24   # Increase space to 24 bytes (6 words)
    sw $ra, 20($sp)       # Save return address
    sw $s0, 16($sp)       # Save s0 (will store p)
    sw $s1, 12($sp)       # Save s1 (will store q)
    sw $a0, 8($sp)        # Save argument m
    sw $a1, 4($sp)        # Save argument n
    sw $a2, 0($sp)        # Save argument o

    # First bar call: bar(m + o, n + o, m + n)
    add $t0, $a0, $a2     # t0 = m + o
    add $t1, $a1, $a2     # t1 = n + o
    add $t2, $a0, $a1     # t2 = m + n
    
    move $a0, $t0         # Set up args for bar
    move $a1, $t1
    move $a2, $t2
    jal bar
    move $s0, $v0         # p = result of first bar call

    # Second bar call: bar(m - o, n - m, n + n)
    lw $t0, 8($sp)        # Restore original m
    lw $t1, 4($sp)        # Restore original n
    lw $t2, 0($sp)        # Restore original o
    
    sub $t3, $t0, $t2     # t3 = m - o
    sub $t4, $t1, $t0     # t4 = n - m
    add $t5, $t1, $t1     # t5 = n + n

    move $a0, $t3         # Set up args for bar
    move $a1, $t4
    move $a2, $t5
    jal bar
    move $s1, $v0         # q = result of second bar call

    # Print "p + q: "
    li $v0, 4
    la $a0, str1
    syscall

    # Print p + q
    add $t0, $s0, $s1     # t0 = p + q
    li $v0, 1
    move $a0, $t0
    syscall

    # Print newline
    li $v0, 4
    la $a0, str2
    syscall

    # Return p + q
    add $v0, $s0, $s1

    # Epilogue
    lw $ra, 20($sp)
    lw $s0, 16($sp)
    lw $s1, 12($sp)
    addiu $sp, $sp, 24
    jr $ra

# bar funciton
bar:
    # No prologue needed as we don't use any saved registers
    sub $t0, $a1, $a0     # t0 = b - a
    sllv $v0, $t0, $a2    # v0 = (b - a) << c (left shift by c units)
    jr $ra


# Initializes three variables (x=2, y=4, z=6)
# Calls function foo(x,y,z) which:
# Calls bar(m+o, n+o, m+n) and stores result in p
# Calls bar(m-o, n-m, n+n) and stores result in q
# Prints "p + q: " followed by the sum of p and q
# Returns p + q
# Updates z with x + y + z + foo(x,y,z)