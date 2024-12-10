        .data
prompt: .asciiz "Please enter a number: "    # Add prompt message
# n:    .word 13                             # Comment out the n declaration

        .text
main:   add     $t0, $0, $zero
        addi    $t1, $zero, 1
        
        # Print prompt
        li      $v0, 4                       # syscall code for print string
        la      $a0, prompt                  # load address of prompt
        syscall
        
        # Read integer input
        li      $v0, 5                       # syscall code for read integer
        syscall
        move    $t3, $v0                     # store input in $t3
        
        # Comment out the old n loading
        # la      $t3, n
        # lw      $t3, 0($t3)
		
fib: 	beq     $t3, $0, finish
	add     $t2,$t1,$t0
	move    $t0, $t1
	move    $t1, $t2
	subi    $t3, $t3, 1
	j       fib
		
finish: addi    $a0, $t0, 0
	li      $v0, 1		
	syscall			
	li      $v0, 10		
	syscall			

