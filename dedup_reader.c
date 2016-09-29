#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]) {
  printf(1,"Freepages at start: %d\n",freepages());
  int* buf = malloc(10000000);
  memset(buf,0x88,10000000);
  printf(1,"Freepages after malloc: %d\n",freepages());
  dedup();
  for(int i=0;i<10000000/4;i++) {
    if(buf[i] != 0x88888888) {
      printf(2,"Argh, found an incorrect value in memory!\n");
      exit();
    }
  }
  printf(1,"Freepages after: %d\n",freepages());
  exit();
}
