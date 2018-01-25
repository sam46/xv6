#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "vga.h"

static struct {
  struct spinlock lock;
  int locking;
} disp;
static ushort *vid = (ushort*)P2V(0xa0000); 
static ushort cur = 0;
#define maxAddress (64000/2)

// #define INPUT_BUF 128
// struct {
//   struct spinlock lock;
//   char buf[INPUT_BUF];
//   uint r;  // Read index
//   uint w;  // Write index
//   uint e;  // Edit index
// } input;


int
displayread(struct file *f, char *dst, int n)
{
  // uint target;
  // int c;

  // target = n;
  // acquire(&input.lock);
  // while(n > 0){
  //   while(input.r == input.w){
  //     if(proc->killed){
  //       release(&input.lock);
  //       ilock(f->ip);
  //       return -1;
  //     }
  //     sleep(&input.r, &input.lock);
  //   }
  //   c = input.buf[input.r++ % INPUT_BUF];
  //   if(c == C('D')){  // EOF
  //     if(n < target){
  //       // Save ^D for next time, to make sure
  //       // caller gets a 0-byte result.
  //       input.r--;
  //     }
  //     break;
  //   }
  //   *dst++ = c;
  //   --n;
  //   if(c == '\n')
  //     break;
  // }
  // release(&input.lock);

  // return target - n;
	return -1;
}

static char vidBuffer[maxAddress*2];
static int curPos; // cursor position
void backupBuffer() { // backup 64000 bytes starting at address KERNELBASE + 0xb8000
	char* loc = (char*)P2V(0xb8000);
	int i;
	for(i = 0; i < maxAddress*2; ++i)
		vidBuffer[i] = loc[i];
}
void restoreBuffer() {
	char* loc = (char*)P2V(0xb8000);
	int i;
	for(i = 0; i < maxAddress*2; ++i)
		loc[i] = vidBuffer[i];
}

int
displayioctl(struct file *f, int param, int value) { 
  if (
  	(param != 1 && param != 2) || 
  	(param == 1 && !(value == 0x3 || value == 0x13))
  ) {
    cprintf("Got unknown DISPLAY ioctl request. %d = %d\n",param,value);
    return -1;
  }

  // acquire(&disp.lock);
  if(param == 1) {
  	if (value == 0x3) { 
  		vgaMode3();
  		showCursor(); // todo: fix: mode switch will show cursor in prev row upon exit
  		setCurPos(curPos);
  		restoreBuffer();
  	} else { 
  		curPos = getCurPos();
	    // curPos += 80 - curPos%80;
  		backupBuffer();
  		vgaMode13();
  	}
	
  }
  else {  // palette
  	int i = value >> 24,
  	r = (value&0x00ff0000) >> 16,
  	g = (value&0x0000ff00) >> 8,
  	b = value&0x000000ff;
  	vgaSetPalette(i,r,g,b);
  }
  // release(&disp.lock);
  return 1;
}

void putPixel(ushort pix, ushort pos, ushort base) {
  vid[(base+pos)%maxAddress] = pix;
}

int
displaywrite(struct file *f, char *buf, int n)
{
  int i;

  acquire(&disp.lock);
  for(i = 0; i < n; i+=2)
  	putPixel(buf[i]|(buf[i+1]<<8), i/2, cur);
  release(&disp.lock);

  // cprintf("wrote %d", n);
  cur += n/2;
  cur = cur % maxAddress;
  return n;
}


void
displayinit() {
  initlock(&disp.lock, "display");
  // initlock(&input.lock, "input");

  devsw[DISPLAY].write = displaywrite;
  devsw[DISPLAY].read = displayread;
  disp.locking = 1;

  // picenable(IRQ_KBD);
  // ioapicenable(IRQ_KBD, 0);
}