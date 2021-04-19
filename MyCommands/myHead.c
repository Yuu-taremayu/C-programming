#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s n\n", argv[0]);
		return EXIT_FAILURE;
	}

	do_head(stdin, atol(argv[1]));
	return EXIT_SUCCESS;
}

static void do_head(FILE *f, long nlines)
{
	int c;

	if (nlines <= 0) return;

	while ((c = getc(f)) != EOF) {
		if (putchar(c) < 0) return;
		if (c == '\n') {
			nlines--;
			if (nlines == 0) return;
		}
	}
}
