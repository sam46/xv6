#include"types.h"
#include"user.h"

int shared = 1;
uint limit = 345873;

void f(void) {
  limit = limit*9987998 % 1238979;
  uint mylimit = limit;
  int i=0;
  while(i<mylimit) { 
    i++;
    shared++;
  }
  printf(1,"Done looping %d\n",mylimit);

}

int main(int argc, char** argv) {

  int threadids[50];
  int thread;
  for(thread=0;thread<50;thread++) {
    threadids[thread]=thread_create(f);
  }

  printf(1,"Done creating\n");

  for(thread=0;thread<50;thread++) {
    thread_join(threadids[thread]);
    printf(1,"Joined %d, shared is now %d\n",thread,shared);
  }  
  
  printf(1,"Main is done!\n"); 

  exit();
  return 0;
}
