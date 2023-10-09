L1: add $1, $2, $3
L2:	sub $1, $2, $3
	addi $1, $2, 100
	addu $1, $2, $3
	subu $1, $2, $3
	addiu $1, $2, 100
	mul $1, $2, $3
	mult $2, $3
	multu $2, $3
	div $2, $3
	and $1, $2, $3
	or $1, $2, $3
	andi $1, $2, 100
	ori $1, $2, 100
	sll $1, $2, 10
	srl $1, $2, 10
	lw $1, 100 ($2)
	sw $1, 100 ($2)
	lui $1, 100
	mfhi $2
	mflo $2
L3:	beq $1, $2, L1
 	bne $1, $2, L2
	slt $1, $2, $3
	slti $1, $2, 100
	j L1
	jr $1
	jal L3