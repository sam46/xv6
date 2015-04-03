#include "types.h"
#include "user.h"

int snoozetime = 5;
void dummy() {
  printf(1,"This function is only here so snooze doesn't end up at address 0!\n");
}

void snooze(int signum) {
  printf(1,"Yawn... another %d seconds?\n",snoozetime--);
  if(snoozetime==0) 
    signal(14,0);
  alarm(1);
}

int main(int argc, char** argv) {
  signal(14,snooze);
  alarm(3);
  
  while(1) {
    printf(1,"Still looping...\n");
    sleep(100);
  }
}

