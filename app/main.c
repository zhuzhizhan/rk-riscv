#include <stdio.h>

int main(void)
{
	char a[10] = {10};
	a[1] = 10;
	char b;
	b = a[3];
	if (b== a[1])
		return 1;
	//printf("hello world\n");

	return 0;
}
