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
#define NUMPROD 5
#define NUMCONS 3
#define NUMBUFFER 1

int varCritica = 0;
int var = 0;
pthread_cond_t condCons;
pthread_cond_t condProd;
pthread_mutex_t mutex;
int numBufferPieni = 0;
int numProdWaiting = 0;
int numConsWaiting = 0;
int numProdWaitingAndSignalled = 0;
int numConsWaitingAndSignaled = 0;


void* prod(void *arg){
    srand((unsigned int) time(NULL));
    while(1){
        //produco dato 
        int dato= rand()%1000;
        pthread_mutex_lock(&mutex);
        if(numProdWaitingAndSignalled >= NUMBUFFER-numBufferPieni){
            //quindi se numero di quelli segnalati è maggiore di num buffer liberi 
            numProdWaiting++;
            pthread_cond_wait(&condProd,&mutex);
            numProdWaiting--;
            numProdWaitingAndSignalled--;
        }

        //sezione critica
        varCritica = dato;
        printf("produttore %" PRIiPTR "produce %d \n", (intptr_t)arg,varCritica);

        numBufferPieni++;
        if((numConsWaitingAndSignaled<=numConsWaiting) &&
            (numConsWaitingAndSignaled<=numBufferPieni)){
            numConsWaitingAndSignaled++;
            pthread_cond_signal(&condCons);        
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* cons(void* arg){
    while(1){
        int dato= rand()%1000;
        pthread_mutex_lock(&mutex);
        if(numConsWaiting>=numBufferPieni){
            numConsWaiting++;
            pthread_cond_wait(&condCons,&mutex);
            numConsWaiting--;
            numConsWaitingAndSignaled--;
        }
        //sezione critica
        var = varCritica;
        printf("consumatore %" PRIiPTR " consuma %d\n", (intptr_t) arg, var);
        numBufferPieni--;
        if((numProdWaitingAndSignalled<NUMBUFFER-numBufferPieni) && (numProdWaitingAndSignalled < numProdWaiting)){
            numProdWaitingAndSignalled++;
            pthread_cond_signal(&condProd);
        }
        pthread_mutex_unlock(&mutex);
    }
}



int main(void){
    pthread_t th;
    int rc; //per error correction 
    intptr_t i;
    pthread_cond_init(&condCons,NULL);
    pthread_cond_init(&condProd,NULL);
    pthread_mutex_init(&mutex,NULL);
    for(i=0; i<NUMPROD;i++){
        pthread_create(&th,NULL,prod,(void *)i);
    }
    for(i=0; i<NUMCONS;i++){
        pthread_create(&th,NULL,cons,(void*)i);
    }
    pthread_exit(NULL);
}