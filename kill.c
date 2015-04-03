#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc < 3){
    printf(2, "usage: kill pid signal\n");
    exit();
  }
  kill(atoi(argv[1]),atoi(argv[2]));
  exit();
}
