#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void do_grep(regex_t *pat, FILE *src);

int main(int argc, char *argv[])
{
	regex_t pat;
	int err;
	int i;

	if (argc < 2) {
		fputs("no pattern\n", stderr);
		return EXIT_FAILURE;
	}
	
	err = regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
	if (err != 0) {
		char buf[1024];

		regerror(err, &pat, buf, sizeof buf);
		puts(buf);
		return EXIT_FAILURE;
	}

	if (argc == 2) {
		do_grep(&pat, stdin);
	}
	else {
		for (i = 2; i < argc; i++) {
			FILE *f;
			f = fopen(argv[i], "r");
			if (!f) {
				perror(argv[i]);
				return EXIT_FAILURE;
			}
			do_grep(&pat, f);
			fclose(f);
		}
	}
	regfree(&pat);

	return EXIT_SUCCESS;
}

static void do_grep(regex_t *pat, FILE *src)
{
	char buf[4096];

	while (fgets(buf, sizeof buf, src)) {
		if (regexec(pat, buf, 0, NULL, 0) == 0) {
			fputs(buf, stdout);
		}
	}
}
