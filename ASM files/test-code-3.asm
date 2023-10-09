lw $t1, 0($zero)
lw $t2, 4($zero)
add $t3, $t1, $t2
add $t3, $t1, $t3
sw $t3, 12($zero)