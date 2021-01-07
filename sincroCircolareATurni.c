#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
//#include "DBGpthread.h"
//#include "printerror.h"
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <pthread.h>
#include <inttypes.h>

pthread_t th;
pthread_mutex_t mutex;
pthread_cond_t cond;
int turno = 0;
int varProtetta = 0;

void * function(void* arg){
    intptr_t mioTurno = (intptr_t)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        while(mioTurno != turno){
            pthread_cond_wait(&cond,&mutex);
            if(mioTurno!=turno){
                pthread_cond_signal(&cond);
            }
        }
        //sezione critica
        varProtetta += 1;
        printf("turno %" PRIiPTR " \n" , mioTurno);
        //fine sezione critica
        turno = (turno +1 )%3;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}

void main(void){

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    for(intptr_t i=0;i<3; i++){
        pthread_create(&th,NULL,function,(void *)i);
    }
    pthread_exit(NULL);
    
}