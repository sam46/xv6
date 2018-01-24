#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  printf(1,"About to mmap\n");
  int fd = open("README",0);
  char* text = mmap(fd,0);
  printf(1,"mmap result is %s\n",text);
  exit();
}
