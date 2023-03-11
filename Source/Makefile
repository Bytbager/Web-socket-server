CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFILES = main.c libs/funcs.c
OFILES = main.o funcs.o

serv: compc
	$(CC) $(CFLAGS) -o server $(OFILES)
	./server

compc:
	$(CC) $(CFLAGS) -c $(CFILES)

clang:
	clang-format -i *.c *.h

clean:
	rm -rf *.o server