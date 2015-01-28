#include"types.h"
#include "user.h"

char *hoarequote = "There are two ways of constructing a software design: One way is to make it so simple that there are obviously no deficiencies, and the other way is to make it so complicated that there are no obvious deficiencies. The first method is far more difficult.\n\n- C.A.R. Hoare (British computer scientist, winner of the 1980 Turing Award)\n\n";

int main(int argc, char** argv) {
  printf(1,"First off, printing in regular color.\n");
  printf(1,"Now changing stdout color.\n");
  if(ioctl(1,0,3)<0) // 1 for stdout
  {
    printf(2,"ioctl failed changing color\n");
    exit();
  }
  printf(1,"Printing pretty on stdout.\n");
  printf(2,"This is stderr output - should still be gray.\nTrying something more interesting...\n\n");
  unsigned int i=0;
  unsigned char color=0x01;  
  for(i=0;i<strlen(hoarequote);i++) {
    if(ioctl(2,0,(color%0xe)+1)<0) {
      printf(2,"Failed setting color for stderr.\n");
      exit();    
    }
    printf(2,"%c",hoarequote[i]&0xff);
    color++;
  }

  ioctl(2,0,0x7);
  ioctl(1,0,0x7);
  printf(1,"stdout should now be gray again\n");
  printf(2,"stderr should now be gray again\n");

  if(ioctl(1,1,0x1)<0) {
    printf(1,"ioctl to set global console color failed\n");
    exit();
  }
  printf(1,"Try typing something, it ought to come out colored: ");
  char buf[100];
  gets(buf,100);

  if(ioctl(1,1,0x7)<0) {
    printf(1,"ioctl to set global console color failed\n");
    exit();
  }
  buf[strlen(buf)-1]=0;
  printf(1,"You typed '%s'. Try typing something gray: ",buf);
  gets(buf,100);
  
  printf(1,"Ok, was that gray? In that case, we're done here. \n\nNow try your hand on the ");
  char *graphics="graphics";
  for(i=0;i<strlen(graphics);i++) {
    ioctl(1,0,(color%0xe)+1);
    color++;
    printf(1,"%c",graphics[i]);
  }
  ioctl(1,0,0x7);
  printf(1," driver.\n");

  exit();
  return 0;
}


