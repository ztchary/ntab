#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TABSIZE 4
#define CHUNK 64000 // TODO: fix this

void error(const char *msg) {
	fprintf(stderr, "\x1b[31m[ERR]\x1b[0m %s\n", msg);
	exit(1);
}

// TODO: use strtok instead to remove this
size_t count_tabs(char *in) {
	size_t tabs = 0;
	for (; *in && *in != '\n'; in++) tabs += *in == '\t';
	return tabs;
}

size_t len_next_line(char *in) {
	size_t len = 0;
	for (; in[len] != '\n'; len++);
	return len;
}

size_t len_next_tab(char *in) {
	size_t len = 0;
	for (; in[len] != '\t'; len++);
	return len;
}


int main(int argc, char **argv) {
	size_t *seclens = malloc(CHUNK);
	char *in  = malloc(CHUNK);
	char *tmp = malloc(CHUNK);
	size_t len = fread(in, 1, CHUNK, stdin);
	size_t seclen;
	size_t tabsize = DEFAULT_TABSIZE;
	if (argc > 1) {
		// TODO: better error messages
		if (argc != 3) error("invalid number of arguments");
		if (strcmp("-t", argv[1]) != 0) error("invalid argument");
		tabsize = atoi(argv[2]);
		if (tabsize == 0) error("invalid tabsize");
	}
	in[len++] = '\n';

	for (; *in;) {
		size_t lines = 0;
		size_t tabs = count_tabs(in);

		for (size_t i = 0; i < tabs; i++) seclens[i] = 0;

		for (char *tabp = in; *tabp; tabp += len_next_line(tabp) + 1) {
			size_t ct = count_tabs(tabp);
			if (ct != tabs) break;
			for (size_t tab = 0; tab < tabs; tab++) {
				seclen = len_next_tab(tabp);
				if (seclen > seclens[tab]) seclens[tab] = seclen;
				tabp += seclen + 1;
			}
			lines++;
		}

		for (size_t line = 0; line < lines; line++) {
			char *ttmp = tmp;
			for (size_t tab = 0; tab < tabs; tab++) {
				seclen = len_next_tab(in);
				memcpy(ttmp, in, seclen);
				memset(ttmp + seclen, ' ', seclens[tab] - seclen + tabsize);
				ttmp += seclens[tab] + tabsize;
				in += seclen + 1;
			}
			seclen = len_next_line(in) + 1;
			memcpy(ttmp, in, seclen);
			ttmp[seclen] = 0;
			printf("%s", tmp);
			in += seclen;
		}
	}
}

