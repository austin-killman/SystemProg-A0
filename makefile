CC = gcc

CFLAGS += -std=gnu11
CFLAGS += -Wall -Werror

main: main.c
	${CC} ${CFLAGS} -o main main.c