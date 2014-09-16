#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  printf(1,"About to make first mmap. Next, you should see the end of LARGE\n");
  int fd = open("README",0);  
  char* text = mmap(fd,0);
  text[71680]=0;
  if(text!=(void*)0x40000000)
    printf(1,"Returned pointer is %d, should be 1073741824 (0x40000000)\n",text);
  printf(1,"%s\n",text+71661);

  exit();
}
