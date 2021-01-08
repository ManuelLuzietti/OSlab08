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
    while( 1 )  {
		int num=0;
		/* attendo 1/4 di sec */
		usleep( 25000);
		
		printf("stato: \t 0 %d \t 1 %d \t 2 %d \t 3 %d \t 4 %d\n", 
			statoFilosofi[0],
			statoFilosofi[1],
			statoFilosofi[2],
			statoFilosofi[3],
			statoFilosofi[4]
			);
		
		for( i=0; i< NUMEROFILOFI; i++ )
			if( statoFilosofi[i]==MANGIA )
				num++;	
		printf("numero di filosofi che mangiano contemporaneamente %d\n", num );
	}
    pthread_exit(NULL);
}


void * filosofo(void *arg){
    int indice = (intptr_t) arg;
    while(1){
        //pensa
        usleep(3000);
        printf("filosofo %d  sta pensando\n", indice);
        fflush(stdout);
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
        fflush(stdout);

        //torno a pensare e cerco di svegliare vicini se posso 
        pthread_mutex_lock(&mutex);
        statoFilosofi[indice] = PENSA;
        printf("filosofo %d  sta pensando\n", indice);
        fflush(stdout);
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