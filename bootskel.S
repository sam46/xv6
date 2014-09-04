.code16
.globl start
start:
_start:
	movb $0x0e,%ah
        movb thestring,%al
	movb $0,%bh
	movb $7,%bl
	int $0x10

stop:
	jmp start

thestring:
	.string "Hello World"

.org 0x01fe
 .word 0xAA55
