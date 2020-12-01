FLAGS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread
SHELL=/bin/bash

all:	es000_infiniti_thread_senza_join.exe
	
es000_infiniti_thread_senza_join.exe: 	es000_infiniti_thread_senza_join.o
	gcc ${FLAGS} -o es000_infiniti_thread_senza_join.exe es000_infiniti_thread_senza_join.o ${LFLAGS} 

es000_infiniti_thread_senza_join.o:	es000_infiniti_thread_senza_join.c
	gcc -c ${FLAGS} -o es000_infiniti_thread_senza_join.o es000_infiniti_thread_senza_join.c ${LFLAGS} 

.PHONY:	clear

clear:	
	rm *.o *.exe


