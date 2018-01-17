// hw1: divide two integers

#include "types.h"
#include "user.h"


char buf[1024];
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(1, "usage: x y\n");
		exit();
	}

	printf(1, "%s / %s is %d\n", argv[1],argv[2],atoi(argv[1])/atoi(argv[2]));
	exit();
}