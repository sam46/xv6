#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]) {
  printf(1,"Freepages at start: %d\n",freepages());
  void* buf = malloc(10000000);
  memset(buf,0,10000000);
  printf(1,"Freepages after malloc: %d\n",freepages());
  dedup();
  printf(1,"Freepages after dedup: %d\n",freepages());
  memset(buf,1,1000000);
  printf(1,"Freepages after writing a little: %d\n",freepages());
  dedup();
  printf(1,"Freepages after dedup: %d\n",freepages());
  memset(buf+1000000,1,9000000);  
  printf(1,"Freepages after writing the rest: %d\n",freepages());
  dedup();
  printf(1,"Freepages after dedup: %d\n",freepages());
  exit();
}
