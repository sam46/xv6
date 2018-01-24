.code16
.globl start
start:
_start:
	movb $0x0e,%ah
        movb thestring,%al
	movb $0,%bh
	movb $7,%bl
	int $0x10

# print to screen
  mov $msg-1, %si
loop:
  add $0x1, %si
  movb (%si), %al
  call print
  cmpb $0x0, %al
  jne  loop
# wait for key:
  movb $0x0, %ah
  int $0x16
# set video mode (vga display)
  movb $0x13, %al
  movb $0x0, %ah
  int $0x10
# read image into memory
disp:  # int13 AH=42h
  movb $0x80, %dl  # disk #1
  xorw %ax, %ax
  movw %ax, %ds
  movb $0x42, %ah
  mov $struct, %si # interrupt call parameters
  int $0x13
  # jmp disp

jmp stop
msg:
    .ascii "\nhttps://github.com/sam46\npress any key to continue...\n\0"
struct: # interrupt call parameters
    .byte 0x10 # struct size
    .byte 0x00 # reserved
    .word 0x007d  # # how many blocks (block is 512 KB): filesize/512
    .word 0x0  # buffer offset
    .word 0xa000 # buffer base
    .quad 0x1 # starting disk block 
jmp stop

print: # pass char to print in %al
  movb $0x0e, %ah
  movb $0x0, %bh
  movb $0x1, %bl
  int $0x10
  ret

stop:
	jmp stop

thestring:
	.string "Hello World"

.org 0x01fe
 .word 0xAA55
