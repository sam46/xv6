#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
  alarm(3);
  while(1) {
    printf(1,"Still looping...\n");
    sleep(500);
  }
}

