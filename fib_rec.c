#include <stdio.h>

int func_r(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return func_r(n - 1) + func_r(n - 2);
}

int main(void)
{
	printf("%d\n", func_r(6));

	return 0;
}
