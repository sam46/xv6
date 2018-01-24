#rm hw2.o
#rm hw2linked.o
#rm hw2
as hw2.s -o hw2.o
ld --Ttext=0x7c00 -e start hw2.o -o hw2linked.o
#ld -Tdata=0x7a00 -Ttext=0x7c00 -e start hw2.o -o hw2linked.o
objcopy -O binary hw2linked.o hw2
dd if=hw2 of=bsdisk.img bs=512
dd if=sam46.raw of=bsdisk.img bs=512 oflag=append conv=notrunc
qemu-system-i386 bsdisk.img

