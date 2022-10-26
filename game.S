  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  
  .globl delay
  delay: 
# ms = $t0
# i = $t1

	move $t0, $a0 #"laddar upp ms"
	
	while:
		li $t1, 0
		ble $t0, 0, exit
		nop
		addi $t0, $t0, -1
		
		for:
		bgt $t1, 4000, while #konstanten här är den som ska ändras, högre ger längre tid
		nop
		addi $t1, $t1, 1
		
		j for
		nop
	#j while
	
	exit:
jr $ra
nop

.globl hexasc
hexasc: 


	andi $t1, $a0, 0xf
	li  $t4, 10 
	slt $t2, $t1, $t4
	beq $t2, $0, numeric     #1 sant 0 falskt #hoppar till numeric om detta är falskt
	nop
	add $v0, $t1, 0x30
	jr $ra
	nop
numeric: 
	add $v0, $t1, 0x37
	
	jr $ra
	nop
	
.globl time2string
 time2string:

	PUSH $ra
	PUSH $a0
        andi $a0, $a1, 0xf
        nop
        jal hexasc
        nop
        POP $a0
        sb $v0, 4($a0)

	PUSH $a0
	srl $a1, $a1, 4
        andi $a0, $a1, 0xf
        nop
        jal hexasc
        nop
        POP $a0
        sb $v0, 3($a0)
        
        addi $t3,$0, 0x3A
        sb $t3, 2($a0)
        
        PUSH $a0
	srl $a1, $a1, 4
        andi $a0, $a1, 0xf
        nop
        jal hexasc
        nop
        POP $a0
        sb $v0, 1($a0)
        
        PUSH $a0
	srl $a1, $a1, 4
        andi $a0, $a1, 0xf
        nop
        jal hexasc
        nop
        POP $a0
        sb $v0, 0($a0)
        
     	addi $t3,$0, 0x00
        sb $t3, 5($a0)
        
        POP $ra
	jr $ra
	nop
	
	
