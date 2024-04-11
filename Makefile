CC = gcc
CFLAGS = -std=c89 -Wall -Werror -g -pedantic -DLINUX -D_GNU_SOURCE

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

exe: main.c
	$(CC) $(CFLAGS) $^ -o $@

run: exe
	./exe

clean:
	rm -f *.o a.out
