	.data
data1:	.word	1111
data2:	.word	0x2222
	.text
main:
	la	$24, data1
	la	$25, data2
	lw	$8, 0($24)
	addiu	$10, $8, 1234
	lw	$9, 0($25)
	addiu	$11, $9, $10
	addiu	$12, $11, 1992
	addu	$13, $12, $8
	and	$14, $13, $8
	andi	$15, $14, 0xabcd
	addiu	$16, $15, 1988
	nor	$17, $16, $9
	or	$18, $17, $9
	sll	$19, $18, 2
	srl	$20, $19, 1
	subu	$21, $20, $8
	sw	$10, 4($25)
	sw	$11, 8($25)
	sw	$12, 12($25)
	sw	$13, 16($25)
	sw	$14, 20($25)
	sw	$15, 24($25)
	sw	$16, 28($25)
	sw	$17, 32($25)
	sw	$18, 36($25)
	sw	$19, 40($25)
	sw	$20, 44($25)
	sw	$21, 48($25)
