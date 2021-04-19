#include <stdlib.h>
#include <stdio.h>

/* include for open() */
#include <sys/stat.h>
#include <fcntl.h>

/* include for read(), write() and close() */
#include <unistd.h>
#include <sys/types.h>

static void do_cat(FILE *f);

int main(int argc, char *argv[])
{
	int i;

	if (argc == 1) {
		do_cat(stdin);
	}
	else {
		for (i = 1; i < argc; i++) {
			FILE *f;

			f = fopen(argv[i], "r");
			if (f == NULL) {
				perror(argv[i]);
				exit(1);
			}
			do_cat(f);
			fclose(f);
		}
	}
	exit(0);
}

/* ?? */
#define BUFFER_SIZE 2048

/* do cat */
static void do_cat(FILE *f)
{
	int c;

	while ((c = fgetc(f)) != EOF) {
		if (putchar(c) < 0) exit(1);
	}
}
