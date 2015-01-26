#include"types.h"
#include "user.h"

int main(int argc, char** argv) {
  printf(1,"Printing regular\n");
  ioctl(1,0,3); // 1 for stdout
  printf(1,"Printing pretty\n");
  exit();
  return 0;
}
