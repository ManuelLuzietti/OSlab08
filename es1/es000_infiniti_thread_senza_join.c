#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>	/* uintptr_t */
#include <inttypes.h>	/* PRIiPTR */
#include <errno.h>

#define SIZE 100

void * funz(void *arg){
    printf("%" PRIiPTR "\n", (intptr_t)arg);
    pthread_exit(NULL);
}

void main(){
    intptr_t t=0;
    pthread_t tid;
    char buff[SIZE];
    while(1){
        int err = pthread_create(&tid,NULL,funz,(void*)t);
        if(err){
            strerror_r(err,buff,SIZE);
            puts(buff);
            exit(-1);
        }
        t++;
    }
    pthread_exit(NULL);
}
