GS=-ansi -Wpedantic -Wall -D_THREAD_SAFE -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LFLAGS=-lpthread
SHELL=/bin/bash

all:	es00_infiniti_thread_con_join.exe
	
es00_infiniti_thread_con_join.exe: 	es00_infiniti_thread_con_join.o
	gcc ${FLAGS} -o es00_infiniti_thread_con_join.exe es00_infiniti_thread_con_join.o ${LFLAGS} 

es00_infiniti_thread_con_join.o:	es00_infiniti_thread_con_join.c
	gcc -c ${FLAGS} -o es00_infiniti_thread_con_join.o es00_infiniti_thread_con_join.c ${LFLAGS} 

.PHONY:	clear

clear:	
	rm *.o *.exe



