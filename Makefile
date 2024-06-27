CFLAGS=-ggdb -Wall -Wextra -Werror

linked_arena: main.c linked_arena.h
	gcc $(CFLAGS) -o linked_arena main.c
