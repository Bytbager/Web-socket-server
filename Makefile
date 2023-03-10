CC = gcc
CFLAGS = -Wall -Werror -Wextra

serv:
	$(CC) $(CFLAGS) -o server main2.c
	./server

clang:
	clang-format -i *.c *.h