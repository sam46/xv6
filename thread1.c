#include"types.h"
#include"user.h"

void f(void) {
  printf(1,"Hello world!\n");
  while(1);
}

int main(int argc, char** argv) {
  thread_create(f);
  printf(1,"Hello from main!\n");
  while(1);
  return 0;
}
