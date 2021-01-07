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

#define NUMEROLETTORI 5
#define NUMEROSCRITTORI 3

pthread_mutex_t mutexVarLettori;
pthread_mutex_t mutexBuffer;
int numeroLettoriLettura = 0;
int buffer = 0;

void * scrittore(void* arg){
    while(1){
        int dato = rand() % 1000;
        pthread_mutex_lock(&mutexBuffer);
        //sezione critica
        buffer = dato;
        printf("scrittore %" PRIiPTR " scrive %d \n", (intptr_t)arg,buffer);
        //sleep(1);
        pthread_mutex_unlock(&mutexBuffer);
    }
}

void * lettore(void* arg){
    while(1){
        int dato;
        pthread_mutex_lock(&mutexVarLettori);
        if(numeroLettoriLettura <= 0){
            pthread_mutex_lock(&mutexBuffer);
        }
        numeroLettoriLettura++;
        pthread_mutex_unlock(&mutexVarLettori);

        //sezione critica
        dato = buffer;
        printf("lettore %" PRIiPTR " legge %d\n", (intptr_t)arg,dato);
        //sleep(1);
        pthread_mutex_lock(&mutexVarLettori);
        numeroLettoriLettura--;
        if(numeroLettoriLettura <= 0){
            pthread_mutex_unlock(&mutexBuffer);
        }
        pthread_mutex_unlock(&mutexVarLettori);
    }
}

int main(void){
    pthread_t th;
    pthread_mutex_init(&mutexVarLettori,NULL);
    pthread_mutex_init(&mutexBuffer,NULL);
    intptr_t i;
    srand((unsigned int)time(NULL));
    for(i=0;i<NUMEROLETTORI;i++){
        pthread_create(&th,NULL,lettore,(void*)i);
    }
    for(i=0;i<NUMEROSCRITTORI;i++){
        pthread_create(&th,NULL,scrittore,(void*)i);
    }
    pthread_exit(NULL);

}