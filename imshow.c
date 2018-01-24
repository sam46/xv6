#include"types.h"
#include "user.h"
#include "fcntl.h"


int main(int argc, char** argv) {
  int fd;
  if( (fd = open("display",O_WRONLY)) == 0) {
    exit();
  }

  int img;
  if( (img = open("cover.raw",0)) == 0) {
    exit();
  }  

  // switch modes to VGA 0x13
  if(ioctl(fd,1,0x13) < 0) {
    printf(2,"error: ioctl to switch to VGA mode failed.\n");
    exit();
  }

  int k;
  char buf[1000];
  for(k=0;k<64;k++) {
    int readbytes = read(img,buf,1000);
    if(readbytes!=1000) {
      printf(1,"Huh, only read %d bytes from file\n",readbytes);
    }
  
    int wrotebytes = write(fd,buf,1000);   
    if(wrotebytes!=1000) {
      printf(1,"Huh, only wrote %d bytes to display\n",wrotebytes);
    }
  }

  sleep(100);

  int beats;
  for(beats=0;beats<8;beats++) {

    int fade;
    for(fade=63;fade>0;fade-=3) {
      
      // the value is a 32-bit struct containing (palette#, R, G, B)
      if(ioctl(fd,2,0x0f<<24 | 63 << 16 | fade << 8 | fade ) < 0) {
        printf(2,"Error setting palette color.\n");
      }
      sleep(1);
    }
    for(fade=0;fade<63;fade+=3) {
      if(ioctl(fd,2,0x0f<<24 | 63 << 16 | fade << 8 | fade ) < 0) {
        printf(2,"Error setting palette color.\n");
      }
      sleep(1);
    }

    if(ioctl(fd,2,0x0f<<24 | 63 << 16 | 63 << 8 | 63 ) < 0) {
      printf(2,"Error setting palette color.\n");
    }

    if(beats%2)
      sleep(100);
    else
      sleep(10);    
  }

  // switch back to text
  if(ioctl(fd,1,0x3) < 0) {
    printf(2,"error: ioctl to restore screen to text failed.\n");
    exit();
  }

  exit();
  return 0;
}
