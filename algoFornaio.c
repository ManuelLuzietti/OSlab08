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
pthread_mutex_t mutexDistrBiglietti;
pthread_mutex_t mutexTurno;
pthread_cond_t cond;

int bigliettoGlog = 0;
int bigliettoSulDiplay = 0;
void * function(void* arg){
    int biglietto;
    while(1){
        pthread_mutex_lock(&mutexDistrBiglietti);
        biglietto = bigliettoGlog;
        bigliettoGlog++;
        pthread_mutex_unlock(&mutexDistrBiglietti);

        printf("cliente %d aspetta il suo turno \n", biglietto);

        pthread_mutex_lock(&mutexTurno);
        while(bigliettoSulDiplay != biglietto){
            pthread_cond_wait(&cond,&mutexTurno);
        }
        printf("si serve il cliente %d \n" , biglietto);
        bigliettoSulDiplay++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutexTurno);

    }
}
void main(void){
    pthread_mutex_init(&mutexDistrBiglietti,NULL);
    pthread_mutex_init(&mutexTurno,NULL);
    pthread_cond_init(&cond,NULL);
    while(1){
        pthread_create(&th,NULL,function,NULL);
    }
}