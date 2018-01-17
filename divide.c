// https://github.com/sam46
// hw1: divide two integers

#include "types.h"
#include "user.h"

int getInt(const char* arg) {
	return (arg[0] == '-') ? -atoi(arg+1) : atoi(arg);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(1, "usage: x y\n");
		exit();
	}
	int x = getInt(argv[1]), y = getInt(argv[2]);
	x = (x < 0) ? x*-1 : x;
	y = (y < 0) ? y*-1 : y;

	int f0, f1, f2;
	f0 = x/y;
	f1 = ((10*x)/y)%10;
	f2 = ((100*x)/y)%10;

	char* sign = getInt(argv[1]) * getInt(argv[2]) >= 0 ? "" : "-";
	printf(1, "%s / %s is %s%d.%d%d\n", argv[1], argv[2], sign, f0, f1, f2);
	exit();
}
