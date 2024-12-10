.data
n: .word 25
str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to\n"
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"

.text
main:
    # Read integer from user
    li $v0, 5       # syscall code for reading integer
    syscall         # read integer from user input
    move $t0, $v0   # move the input to $t0 for later use

    # Load n into $t1
    lw $t1, n

    # Compare if user input is equal to n
    beq $t0, $t1, equal    # if equal, branch to equal case
    
    # Compare if user input is less than n
    slt $t2, $t0, $t1      # set $t2 to 1 if $t0 < $t1, else 0
    beq $t2, $zero, greater # if not less than, must be greater
    
    # Less than case
    li $v0, 4
    la $a0, str1
    syscall
    j exit

equal:
    # Equal case (will show less than or equal)
    li $v0, 4
    la $a0, str2
    syscall
    j exit

greater:
    # Greater than case
    li $v0, 4
    la $a0, str3
    syscall

exit:
    # Exit program
    li $v0, 10
    syscall
