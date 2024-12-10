.data
prompt: .asciiz "Enter a number: "    # Input prompt
return_msg: .asciiz "Returning "      # Return value message
newline: .asciiz "\n"                 # Newline character

.text
.globl main
main:
	# Print prompt
	li	$v0, 4				# syscall code for print string
	la	$a0, prompt			# load address of prompt
	syscall

	# Read user input
	li	$v0, 5				# syscall code for read integer
	syscall
	move	$a0, $v0			# move input to argument register

	# Call recursion function
	jal	recursion			# jump and link to recursion

	# Print result
	move	$a0, $v0			# save return value before syscall
	li	$v0, 1				# syscall code for print integer
	syscall

	# Exit program
	li	$v0, 10				# syscall code for exit
	syscall

recursion:
	# Setup stack frame
	addi	$sp, $sp, -12		# make room for 3 items
	sw	$ra, 0($sp)			# save return address
	sw	$a0, 4($sp)			# save argument
	sw	$s0, 8($sp)			# save $s0

	# Check for base case -1
	beq	$a0, -1, minus_one
	
	# Check for base case 0
	beq	$a0, $zero, zero

not_zero:
	# First recursive call with (n-1)
	addi	$a0, $a0, -1		# n-1
	jal	recursion
	
	# Save result of first call
	move	$s0, $v0
	
	# Second recursive call with (n-2)
	lw	$a0, 4($sp)			# restore original n
	addi	$a0, $a0, -2		# n-2
	jal	recursion
	
	# Calculate final result
	add	$v0, $s0, $v0		# add results of both calls

	# Print "Returning" message before return
	move	$t0, $v0			# save return value
	li	$v0, 4				# syscall code for print string
	la	$a0, return_msg		# load "Returning " message
	syscall
	move	$a0, $t0			# load return value for printing
	li	$v0, 1				# syscall code for print integer
	syscall
	li	$v0, 4				# syscall code for print string
	la	$a0, newline		# print newline
	syscall
	move	$v0, $t0			# restore return value
	j	end_recur

minus_one:
	li	$v0, 1				# return 1
	j	end_recur

zero:
	li	$v0, 3				# return 3
	j	end_recur

end_recur:
	# Restore stack frame
	lw	$ra, 0($sp)			# restore return address
	lw	$s0, 8($sp)			# restore $s0
	addi	$sp, $sp, 12		# restore stack pointer
	jr	$ra				# return to caller
