#include "types.h"
#include "user.h"

void hello(int);

int main(int argc, char** argv) {
  signal(2,hello);
  while(1) {
    printf(1,"Hello, still looping!\n");
    sleep(100);
  }
}

void hello(int signum) {
  printf(1,"Nuh-uh, I'm a non-preemptable hello loop!\n");
}

