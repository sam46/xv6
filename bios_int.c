#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "int32.h"
#include "memlayout.h"

void bios_int(unsigned char intnum, regs16_t* regs) {
  pushcli();

  pte_t original = biosmap();
  int32(intnum,regs);  
  biosunmap(original);

  popcli();
}
