#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bufsize 256

typedef struct DATA {
	double x;
	double y;
} DATA;

void count_data_num(char *filename, int *dataNum);
void read_data(char *filename, DATA *data, int *dataNum);
void lsm(DATA *data, int *dataNum);

int main(int argc, char *argv[])
{
	DATA *data;
	int dataNum;
	char filename[256];
	
	if (argc - 1 != 1) {
		printf("Error.\n");
		printf("input filename.\n");
		exit(1);
	}
	
	strcpy(filename, argv[1]);

	count_data_num(filename, &dataNum);

	data = (DATA *)malloc(sizeof(DATA) * dataNum);

	read_data(filename, data, &dataNum);
	for (int i = 0; i < dataNum; i++) {
		printf("[%d]:x = %lf, y = %lf\n", i, data[i].x, data[i].y);
	}

	lsm(data, &dataNum);

	free(data);
	return 0;
}

void count_data_num(char *filename, int *dataNum)
{
	FILE *fp;
	char buf[bufsize];
	int line = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error.\n");
		printf("Can't open file.\n");
		exit(1);
	}

	while (fgets(buf, bufsize, fp) != NULL) line++;
	*dataNum = line;
	
	fclose(fp);
}

void read_data(char *filename, DATA *data, int *dataNum)
{
	FILE *fp;
	
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error.\n");
		printf("Can't open file.\n");
		exit(1);
	}

	for (int i = 0; i < *dataNum; i++) {
		fscanf(fp, "%lf", &data[i].x);
		fscanf(fp, "%lf", &data[i].y);
	}

	fclose(fp);
}

void lsm(DATA *data, int *dataNum)
{
	double array1[2][2] = {{0, 0}, {0, 0}};
	double array2[2] = {0, 0};
	double resultX = 0, resultY = 0;
	
	for (int i = 0; i < *dataNum; i++) {
		array1[0][0] += data[i].x * data[i].x;
		array1[0][1] = array1[1][0] += data[i].x;

		array2[0] += data[i].x * data[i].y;
		array2[1] += data[i].y;
	}
	array1[1][1] = *dataNum;

	resultX = (array1[1][1] * array2[0] - array1[0][1] * array2[1]) / (array1[0][0] * array1[1][1] - array1[0][1] * array1[1][0]);
	resultY = (array1[1][0] * array2[0] * -1 +  array1[0][0] * array2[1]) / (array1[0][0] * array1[1][1] - array1[0][1] * array1[1][0]);
	
	printf("\n");
	printf("a = %lf, b = %lf\n", resultX, resultY);
}
