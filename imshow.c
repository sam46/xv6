#include"types.h"
#include "user.h"

char buf[64000];

int main(int argc, char** argv) {
  int fd;
  if( (fd = open("display",0)) == 0) {
    exit();
  }

  int img;
  if( (img = open("cover.raw",0)) == 0) {
    exit();
  }  
  int readbytes = read(img,buf,64000);
  if(readbytes!=64000) {
    printf(1,"Huh, only read %d bytes from file\n",readbytes);
  }

  // switch modes to VGA 0x13
  ioctl(fd,1,0x13);  
  
  int wrotebytes = write(fd,buf,64000);
  sleep(100);

  // switch back to text
  ioctl(fd,1,0x3);

  if(wrotebytes!=64000) {
    printf(1,"Huh, only wrote %d bytes to display\n",wrotebytes);
  }
  exit();
  return 0;
}
