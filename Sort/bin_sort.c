#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define N 10

void f4(int a[], int n);
void f5(int a[], int c[], int n);

int main(void)
{
	int a[N] = {3, 5, 2, 1, 3, 1, 5, 5, 5, 0};

	f4(a, N);

	return 0;
}

void f4(int a[], int n)
{
	int i;
	int *c = (int *)malloc(sizeof(int) * (MAX + 1));

	for (i = 0; i < MAX + 1; i++)
		c[i] = 0;

	for (i = 0; i < n; i++)
		c[a[i]]++;

	f5(a, c, n);

	free(c);
}

void f5(int a[], int c[], int n)
{
	int i;
	int ans[n];

	for (i = 0; i < n; i++)
		ans[i] = 0;

	for (i = 1; i < MAX + 1; i++) {
		c[i] = c[i] + c[i - 1];
	}
	

	for (i = 0; i < n; i++) {
		ans[--c[a[i]]] = a[i];
	}

	for (i = 0; i < n; i++)
		printf("ams[%d]:%d\n", i, ans[i]);
}
