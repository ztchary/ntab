CC=cc
CFLAGS=-Wall -Werror

ntab: ntab.c
	$(CC) $(CFLAGS) -o ntab ntab.c
