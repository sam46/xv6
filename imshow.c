#include"types.h"
#include "user.h"

int main(int argc, char** argv) {
  int fd;
  if( (fd = open("display",0)) == 0) {
    exit();
  }
  
  ioctl(fd,1,0x13);
  sleep(100);
  ioctl(fd,1,0x3);
  exit();
  return 0;
}
