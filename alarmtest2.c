#include "types.h"
#include "user.h"

int main(int argc, char** argv) {

  signal(14,(void(*)(int))1); // ignore alarm signal this time
  alarm(2);
  int i=5;
  while(i--) {
    printf(1,"Still looping... %d\n",i);
    sleep(100);
  }

  signal(14,0); // stop ignoring alarms
  alarm(5); //

  while(1) {
    printf(1,"Still waiting for that alarm... \n");
    sleep(100);
  }
}

