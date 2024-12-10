.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "

error_msg1: .asciiz "Error: Number of assignments must be between 1 and 25\n"
error_msg2: .asciiz "Error: Scores must be between 0 and 100\n"
error_msg3: .asciiz "Error: Invalid number of scores to drop\n"
error_msg4: .asciiz "Error: Cannot drop all scores (division by zero)\n"


.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	move $s0, $v0	# $s0 = numScores
	
	# Add bounds checking
	blez $s0, invalid_input    # if numScores <= 0, error
	li $t0, 25
	bgt $s0, $t0, invalid_input # if numScores > 25, error
	
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	
	# Add bounds checking for scores
	bltz $v0, invalid_score    # if score < 0, error
	li $t2, 100
	bgt $v0, $t2, invalid_score # if score > 100, error
	
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	move $a1, $v0
	
	# Add bounds checking
	blez $a1, invalid_drop    # if drop < 0, error
	beqz $s0, invalid_drop    # if numScores is 0, error
	bge $a1, $s0, zero_avg    # Changed: if drop >= numScores, show 0 average instead of error
	j continue

# Add new label for zero average case
zero_avg:
	# Print average message
	li $v0, 4
	la $a0, str5
	syscall
	
	# Print zero
	li $v0, 1
	li $a0, 0
	syscall
	
	# Print newline
	li $v0, 11
	li $a0, 10
	syscall
	
	j exit_program    # Exit after showing zero average

continue:
	sub $a1, $s0, $a1   # numScores - drop
	move $a0, $s2
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it
	div $v0, $a1        # Divide sum by number of scores (not dropped)
	mflo $t0            # Get quotient (rounded down)
	
	# Print average message
	li $v0, 4
	la $a0, str5
	syscall
	
	# Print average
	li $v0, 1
	move $a0, $t0
	syscall
	
	# Print newline
	li $v0, 11
	li $a0, 10
	syscall
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	addi $sp, $sp 12
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
	# Save $ra and base address
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)      # Save original base address
	
	move $t0, $0        # Initialize counter i = 0
print_loop:
	beq $t0, $a1, print_done    # If i == size, exit loop
	
	# Print number
	sll $t1, $t0, 2     # t1 = i * 4
	lw $t2, 4($sp)      # Reload base address
	add $t1, $t1, $t2   # t1 = base address + offset
	lw $a0, 0($t1)      # Load number to print
	li $v0, 1           # Print integer syscall
	syscall
	
	# Print space
	li $v0, 11          # Print character syscall
	li $a0, 32          # ASCII for space
	syscall
	
	addi $t0, $t0, 1    # i++
	j print_loop
	
print_done:
	# Print newline
	li $v0, 11          # Print character syscall
	li $a0, 10          # ASCII for newline
	syscall
	
	# Restore registers
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Need to save $ra since we might call other functions
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Initialize sorted array first
	move $t0, $0        # i = 0
init_loop:
	beq $t0, $a0, outer_loop_start    # if i == size, start sorting
	sll $t1, $t0, 2     # t1 = i * 4
	la $t2, orig
	la $t3, sorted
	add $t2, $t2, $t1   # Address in orig
	add $t3, $t3, $t1   # Address in sorted
	lw $t4, 0($t2)      # Load from orig
	sw $t4, 0($t3)      # Store in sorted
	addi $t0, $t0, 1    # i++
	j init_loop

outer_loop_start:
	move $t0, $0        # i = 0
outer_loop:
		beq $t0, $a0, sort_done    # if i == size, done
		
		move $t1, $t0       # maxIndex = i
		addi $t2, $t0, 1    # j = i + 1
		
inner_loop:
		beq $t2, $a0, swap  # if j == size, do swap
		
		# Load sorted[maxIndex] and sorted[j]
		sll $t3, $t1, 2     # t3 = maxIndex * 4
		sll $t4, $t2, 2     # t4 = j * 4
		la $t5, sorted      # Load sorted base address (changed from orig)
		add $t3, $t3, $t5   # t3 = address of sorted[maxIndex]
		add $t4, $t4, $t5   # t4 = address of sorted[j]
		lw $t6, 0($t3)      # t6 = sorted[maxIndex]
		lw $t7, 0($t4)      # t7 = sorted[j]
		
		# if sorted[j] > sorted[maxIndex], update maxIndex
		ble $t7, $t6, skip_update
		move $t1, $t2       # maxIndex = j
skip_update:
		addi $t2, $t2, 1    # j++
		j inner_loop
		
swap:
		# Swap sorted[i] and sorted[maxIndex]
		sll $t3, $t0, 2     # t3 = i * 4
		sll $t4, $t1, 2     # t4 = maxIndex * 4
		la $t5, sorted      # Changed from orig to sorted
		add $t3, $t3, $t5   # Address of sorted[i]
		add $t4, $t4, $t5   # Address of sorted[maxIndex]
		lw $t6, 0($t3)      # t6 = sorted[i]
		lw $t7, 0($t4)      # t7 = sorted[maxIndex]
		sw $t7, 0($t3)      # sorted[i] = sorted[maxIndex]
		sw $t6, 0($t4)      # sorted[maxIndex] = temp
		
		addi $t0, $t0, 1    # i++
		j outer_loop
		
sort_done:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
	# Base case: if size <= 0, return 0
	blez $a1, sum_base_case
	
	# Save registers
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	
	# Recursive case
	addi $a1, $a1, -1   # size - 1
	jal calcSum         # Recursive call
	
	# Restore registers
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	lw $a1, 8($sp)
	addi $sp, $sp, 12
	
	# Add current element (changed to start from beginning)
	addi $t0, $a1, -1   # t0 = size - 1
	sll $t0, $t0, 2     # t0 = (size-1) * 4
	add $t0, $a0, $t0   # t0 = address of current element
	lw $t1, ($t0)       # t1 = current element
	add $v0, $v0, $t1   # Add to sum
	jr $ra
	
sum_base_case:
	li $v0, 0           # Return 0
	jr $ra
	

exit_program:
	li $v0, 10
	syscall
	

# Add new error handlers
invalid_input:
	li $v0, 4
	la $a0, error_msg1    # You'll need to add this to .data
	syscall
	j exit_program

invalid_score:
	li $v0, 4
	la $a0, error_msg2    # You'll need to add this to .data
	syscall
	j exit_program

invalid_drop:
	li $v0, 4
	la $a0, error_msg3    # You'll need to add this to .data
	syscall
	j exit_program

division_by_zero:
	li $v0, 4
	la $a0, error_msg4    # You'll need to add this to .data
	syscall
	j exit_program

