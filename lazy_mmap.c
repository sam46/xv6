#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  printf(1,"About to make first mmap. Next, you should see the first sentence from README\n");
  int fd = open("README",0);  
  char* text = mmap(fd,1);
  text[85]=0;
  if(text!=(void*)0x40000000)
    printf(1,"Returned pointer is %d, should be 1073741824 (0x40000000)\n",text);
  printf(1,"%s\n",text);

  printf(1,"\nSecond mmap coming\n");
  int fd2 = open("LARGE",0);  
  char* text2 = mmap(fd2,1);
  
  text2[71680]=0;
  if(text2!=(void*)0x40001000)
    printf(1,"Returned pointer is %d, should be 1073741824+4069 (0x40001000)\n",text2);
  printf(1,"%s\n",text2+71661);

  printf(1,"Checking that first mmap is still ok, you should see the first sentence from README\n");
  text[85]=0;
  if(text!=(void*)0x40000000)
    printf(1,"Returned pointer is %d, should be 1073741824 (0x40000000)\n",text);
  printf(1,"%s\n",text);

  exit();
}
