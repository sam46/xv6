#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "fs.h"
#include "file.h"
#include "fcntl.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

// implementation of mmap syscall: mmap(file, flag)
// flag: 0 eager, 1 lazy 
int sys_mmap() {
  /*
    my implementation uses a whole pagesize even if file's size is smaller.
    so a file will always take up a multiple of PGSIZE in memory!! (whether using eager or lazy)
  */

  int fd;
  struct file *f;
  int flags;
  argfd(0,&fd,&f);
  argint(1,&flags);
  if(fd < 0 || flags < 0 ||  flags > 1) {
    cprintf("mmap error. invalid parameters\n");
    return -1;
  }

  cprintf("mmapping fd %d with %s\n",fd,(flags==0?"eager":"lazy"));

  if(flags == 0) { // eager
    pde_t* pgdir = proc->pgdir;
    char * mem;

    uint oldsz = proc->mmap_sz + MMAP_BASE; // pointer to last (accessible) byte in mmap region (currently, not absolutely)
    uint fsz =  PGROUNDUP(oldsz + f->ip->size);
    uint newsz = oldsz; 

    uint a = PGROUNDUP(oldsz); // pointer to current page (0th byte)
    cprintf("  a %d\n",a);
    cprintf("  fsz %d\n",fsz);
    cprintf("  oldsz %d\n",oldsz);    
    cprintf("  newsz %d\n",newsz);

    for(; a < fsz; a += PGSIZE, newsz += PGSIZE) {
      mem = kalloc(); // reserve a physical page. will give back a virtual address such that v2p(mem) is the 0th byte of the just-reserved physical page
      if(mem == 0) { // todo: handle
        cprintf("mmap out of memory\n");
        // deallocuvm(pgdir, newsz, oldsz); wroooong. need a custom one
        return -1;
      }
      memset(mem, 0, PGSIZE); // clear it with zeros
      mappages(pgdir, (char*)a, PGSIZE, v2p(mem), PTE_W|PTE_U); // map virtual page beginning at 'a' to physical page reserved by 'mem'. 
      // now both 'a' and 'mem' point to same physical location? I get same memory contents at both locations (using gdb), so yes. but why?

      cprintf("v2p of mem %d%\n", v2p((void*)mem));
      cprintf("v2p of a %d%\n", v2p((void*)a));
      cprintf("allocated %d\n\n",newsz-oldsz+PGSIZE);
      readi(f->ip, (char*)a, newsz-oldsz, PGSIZE); // read from file PAGESIZE bytes into our newly allocated page. if we replace 'a' with 'mem' this still works!! why?
    }
    cprintf("process (pid=%d) mmap region grew from %d to %d bytes\n", proc->pid, proc->mmap_sz, newsz-MMAP_BASE);
    proc->mmap_sz = newsz-MMAP_BASE; // update mmap reserved size for this process. 
    switchuvm(proc);
    return oldsz; // memory address which is = to old proc->mmap_sz + MMAP_BASE. this is where the file content reside at in memory
  }

  else if(flags == 1) { // lazy
    uint oldsz = proc->mmap_sz + MMAP_BASE; // pointer to last (accessible) byte in mmap region (currently, not absolutely)
    // make a new lazy-mmap job
    struct mmap_job *job = &(proc->mmjobs[proc->mmjobs_count]);
    proc->mmjobs_count++; 
    job->beg = (char*) proc->mmap_sz + MMAP_BASE; // inclusive
    job->end = (char*) PGROUNDUP((uint) (job->beg + f->ip->size)); // exclusive
    job->fd = fd;
    job->f = f;
    proc->mmap_sz += (uint) (job->end - job->beg); // reserve mmap-region space, but don't allocate or map yet
    
    /* reset is handled by sys_lazymm() 
    which wil be called by trap.c on pagefault */

    return oldsz; // we promise to load file into this virtual address
  }

  return -1;
}

// check if addr is referring to (lazily) mmaped file,  
// if so, actually load the file (or a chunk of it)
// and add this addr (or the page it's in) to page table.
int
sys_lazymm(char* addr) {
  cprintf("requested lazy-mmaped address (0x%x)\n",(uint) addr);

  int found = 0;
  int i;
  struct mmap_job *job; // check if the address lies within a promised lazy-mmap region
  for (i=0; i < proc->mmjobs_count; ++i) {
    job = &proc->mmjobs[i];
    if (addr >= job->beg && addr < job->end) {
      found = 1;
      break;
    }
  }
  if (found == 0)
    return -1; // nope, the addr isn't referring to mmaped file. probably process misbehaved

  struct file *f = job->f;
  pde_t* pgdir = proc->pgdir;

  uint a = PGROUNDDOWN((uint) addr); 
  char * mem = kalloc();
  if (mem == 0) { // todo: handle
    cprintf("lazy mmap out of memory\n");
    // deallocuvm(pgdir, newsz, oldsz); wroooong. need a custom one. 
    return -1;
  }

  memset(mem, 0, PGSIZE); // clear it with zeros
  mappages(pgdir, (char*)a, PGSIZE, v2p(mem), PTE_W|PTE_U);
  // cprintf("v2p of mem %d\n", v2p((void*)mem));
  // cprintf("v2p of a %d\n", v2p((void*)a));
  // cprintf("allocated %d\n\n",newsz-oldsz+PGSIZE);
  // cprintf("file offset = %d\n",  (uint) ((char*)a - job->beg));
  readi(f->ip, (char*)a, (char*)a - job->beg, PGSIZE); // read from file PAGESIZE bytes into our newly allocated page. if we replace 'a' with 'mem' this still works!! why?
  // switchuvm(proc);

  return 1; // cool
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
