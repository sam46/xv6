#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[]) {
  printf(1,"Freepages at start: %d\n",freepages());
  char* buf = malloc(10000000);
  memset(buf,0,10000000);
  printf(1,"Freepages after malloc: %d\n",freepages());
  dedup();
  printf(1,"Freepages after dedup: %d\n",freepages());
  memset(buf,1,1000000);
  printf(1,"Freepages after writing a little: %d\n",freepages());
  dedup();

  for(int i=0;i<1000000;i++) {
    if(buf[i]!=1) {
      printf(1,"Uh-oh! Found some junk in my frunk!\n");
      exit();
    }
  }
  for(int i=1000000;i<10000000;i++) {
    if(buf[i]) {
      printf(1,"Uh-oh! Found some junk in my trunk!\n");
      exit();
    }
  }
  
  printf(1,"Freepages after dedup: %d\n",freepages());
  memset(buf+1000000,1,9000000);  
  printf(1,"Freepages after writing the rest: %d\n",freepages());
  dedup();
  printf(1,"Freepages after dedup: %d\n",freepages());
  exit();
}
