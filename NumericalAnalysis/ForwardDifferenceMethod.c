#include <stdio.h>
#include <math.h>

int main(void)
{
	double x = 0;
	double dx = 0.00001;

	double y = 0;

	y = (exp(x + dx) - exp(x)) / dx;

	printf("y = %lf\n", y);
	return 0;
}

