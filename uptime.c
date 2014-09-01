#include"types.h"
#include"user.h"
int main(int argc, char** argv) {

 int hours = uptime()/360000;
 int minutes = (uptime()-hours*3600)/6000;
 int seconds = (uptime()-hours*3600-minutes*60)/100; 
 printf(1,"Uptime %s%d:%s%d:%s%d\n",(hours<10?"0":""),hours,(minutes<10?"0":""),minutes,(seconds<10?"0":""),seconds);
 exit();
 return 0;
}
