#include"types.h"
#include"user.h"

int shared = 1;

int main(int argc, char** argv) {
  int i=1000;
  while(i--)
    printf(1,"thread5_helper now running instead, finishing in %d.\n",i);
  exit();
  return 0;  
}
