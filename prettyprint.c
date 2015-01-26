#include"types.h"
#include "user.h"

int main(int argc, char** argv) {
  printf(1,"Printing regular\n");
  if(ioctl(1,0,3)<0) // 1 for stdout
  {
    printf(2,"ioctl failed changing color\n");
    exit();
  }
  printf(1,"Printing pretty\n");
  exit();
  return 0;
}
