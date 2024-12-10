.data
x:	.word 5
y:	.word 10
m:	.word 15
b:	.word 2

.text
MAIN:	la $t0, x
	lw $s0, 0($t0)		# s0 = x
	la $t0, y
	lw $s1, 0($t0)		# s1 = y
	
	# Prepare to call sum(x)
	addu $a0, $zero, $s0	# Set a0 as input argument for SUM
	jal SUM
	addu $t0, $s1, $s0
	addu $s1, $t0, $v0
	addiu $a0, $s1, 0 
	li $v0, 1		 
	syscall	
	j END
		
SUM: 	# Prologue
		addiu $sp, $sp, -12	# Make space for 3 items
		sw $ra, 8($sp)		# Save return address
		sw $a0, 4($sp)		# Save input argument
		sw $s0, 0($sp)		# Save s0 from MAIN
		
		la $t0, m
		lw $s0, 0($t0)		# s0 = m
		addu $a0, $s0, $a0	# Update a0 for SUB
		jal SUB
		
		# After SUB returns
		lw $a0, 4($sp)		# Restore original input
		addu $v0, $a0, $v0	# Add input to SUB result
		
		# Epilogue
		lw $s0, 0($sp)		# Restore s0
		lw $ra, 8($sp)		# Restore return address
		addiu $sp, $sp, 12	# Restore stack pointer
		jr $ra
		
SUB:	la $t0, b
	addiu $sp, $sp -4
	sw $s0, 0($sp)		# Backup s0 from SUM
	lw $s0, 0($t0)		# s0 = b
	subu $v0, $a0, $s0
	lw $s0, 0($sp)		# Restore s0 from SUM
	addiu $sp, $sp 4
	jr $ra

END:
