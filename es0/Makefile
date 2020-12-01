SHELL=/bin/bash
CFLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L

all:	es00000_facile.exe

es00000_facile.exe:	es00000_facile.o
	gcc -o es00000_facile.exe es00000_facile.o ${CFLAGS}  -lm -lpthread

es00000_facile.o:		es00000_facile.c
	gcc -c ${CFLAGS} -o es00000_facile.o  es00000_facile.c 

.PHONY:		clear

clear:	
	rm *.o *.exe

