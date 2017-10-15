	.data
data1:	.word	3
	.word	4096
	.word	0xf4c2a
data2:	.word	2147483646
data3:	.word	2147483647
	.text
main:
	la	$15, data2		//00:	lui $15, 0x1000		04:	ori $15, $15, 0x000c
	addiu	$12, $12, -100		//08
	addiu	$14, $14, -1		//0c
	addiu	$13, $13, 0xffff	//10
	addu	$2, $4, $5		//14
	addu	$2, $6, $7		//18
	subu	$9, $3, $2		//1c
cs311:
	and	$11, $11, $0		//20
	addiu	$10, $10, 0x1		//24
	or	$6, $6, $0		//28
	jal	cs312			//2c
cs312:
	lw	$6, 4($15)		//30
	sll	$7, $6, 2		//34
	sw	$7, 8($15)		//38
	srl	$5, $4, 2		//3c
	nor	$5, $5, $0		//40
	sltiu	$9, $10, -4		//44
	beq	$9, $0, cs313		//48
	jr	$31			//4c
cs313:
	lui	$17, 0x1000		//50
	lw	$18, 0($17)		//54
	sltu	$4, $2, $3		//58
	bne	$4, $0, cs314		//5c
	j	cs311			//60
cs314:
	ori	$16, $16, 0xf0f0	//64
