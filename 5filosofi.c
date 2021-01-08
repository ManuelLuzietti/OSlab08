#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#define _BSD_SOURCE
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

#define NUMEROFILOFI 5
#define PENSA 0
#define HAFAME 1
#define MANGIA 2

int statoFilosofi[NUMEROFILOFI];
pthread_t th;
pthread_mutex_t mutex;
pthread_cond_t condFilosofi[NUMEROFILOFI];

int indiceDestra(int indice){
    if(indice == 0){
        return NUMEROFILOFI-1;
    } else {
        return (indice - 1) % NUMEROFILOFI;
    }
}

int indiceSinistra(int indice){
    return (indice + 1) % NUMEROFILOFI;
}

int puoMangiare(int indice){
    if((statoFilosofi[indiceDestra(indice)] != MANGIA) &&
        (statoFilosofi[indiceSinistra(indice)] != MANGIA) ){
        return 1;        
    } else {
        return 0;
    }
}

void * filosofo(void *arg);

int main(void){
    pthread_mutex_init(&mutex,NULL);
    intptr_t i;
    for(int i = 0; i < NUMEROFILOFI; i++){
        statoFilosofi[i] = PENSA;
    }
    for(int i=0; i < NUMEROFILOFI; i++){
        pthread_cond_init(&(condFilosofi[i]), NULL);
    }
    for(i = 0; i <NUMEROFILOFI; i++){
        pthread_create(&th,NULL,filosofo,(void*)i);
    }
    pthread_exit(NULL);
}


void * filosofo(void *arg){
    int indice = (intptr_t) arg;
    while(1){
        //pensa
        usleep(3000);
        printf("filosofo %d  sta pensando\n", indice);
        //
        pthread_mutex_lock(&mutex);
        statoFilosofi[indice] = HAFAME;
        if(puoMangiare(indice)){
            statoFilosofi[indice] = MANGIA;
        } else
        {
            pthread_cond_wait(&(condFilosofi[indice]), &mutex);
        }
        pthread_mutex_unlock(&mutex);

        //prendo forche, mangio, rilascio
        printf("filosofo %d  sta prendendo forchette\n", indice);
        printf("filosofo %d  sta mangiando\n", indice);
        printf("filosofo %d  sta posando le forchette\n", indice);

        //torno a pensare e cerco di svegliare vicini se posso 
        pthread_mutex_lock(&mutex);
        statoFilosofi[indice] = PENSA;
        printf("filosofo %d  sta pensando\n", indice);
        if(puoMangiare(indiceDestra(indice))){
            pthread_cond_signal(&(condFilosofi[indiceDestra(indice)]));
            statoFilosofi[indiceDestra(indice)] = MANGIA;
        }
        if(puoMangiare(indiceSinistra(indice))){
            pthread_cond_signal(&(condFilosofi[indiceSinistra(indice)]));
            statoFilosofi[indiceSinistra(indice)] = MANGIA;
        }
        pthread_mutex_unlock(&mutex);

        
    }    
}