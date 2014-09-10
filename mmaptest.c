#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  printf(1,"About to mmap\n");
  printf(1,"mmap result is %d\n",mmap(1));
  exit();
}
