#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DATA {
	double x;
	double y;
} DATA;

int main(int argc, char *argv[])
{
	DATA *data;
	int dataNum;
	char filename[256];
	
	if (argc - 1 != 1) {
		printf("Error.\n");
		exit(1);
	}
	
	strcpy(filename, argv[1]);

	return 0;
}

void readfile(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "r");
	fclose(fp);
}
