#include"types.h"
#include"user.h"

int shared = 1;

void f(void) {
  while(shared<10000000) shared++;
  printf(1,"Done looping\n");
}

int main(int argc, char** argv) {
  int t = thread_create(f);
  thread_join(t);
  printf(1,"shared = %d\n",shared);

  exit();
  return 0;
}
