.org 0x7c00
.code16
.globl start
start:
_start:
	movb $0x0e,%ah
        movb $'A',%al
	movb $0,%bh
	movb $7,%bl
	int $0x10

stop:
	jmp start

.org 0x7dfe
 .word 0xAA55
