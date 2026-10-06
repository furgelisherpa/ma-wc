CFLAGS = -Wall -Wextra -pedantic

ma-wc: ma-wc.c
	$(CC) $(CFLAGS) -o ma-wc ma-wc.c

.PHONY: run

run: ma-wc
	./ma-wc
