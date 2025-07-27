#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: cmdline arg for tabsize
#define TABSIZE 4
#define CHUNK 64000

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


int main() {
	size_t *seclens = malloc(CHUNK);
	char *in  = malloc(CHUNK);
	char *tmp = malloc(CHUNK);
	size_t len = fread(in, 1, CHUNK, stdin);
	size_t seclen;
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
				memset(ttmp + seclen, ' ', seclens[tab] - seclen + TABSIZE);
				ttmp += seclens[tab] + TABSIZE;
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

