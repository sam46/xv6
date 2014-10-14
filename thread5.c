#include"types.h"
#include"user.h"

int shared = 1;

void f(void) {
  while(1) {
    printf(1,"thread still running \n");
  }
}

int main(int argc, char** argv) {
  thread_create(f);

  int i=10000;
  while(i--);

  exec("thread5_helper",0);
  return 0;
}
