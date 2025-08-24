CC=cc
CFLAGS=-Wall -Werror

ntab: ntab.c
	$(CC) $(CFLAGS) -o ntab ntab.c

install: ntab:
	install -m 755 ntab /usr/bin

