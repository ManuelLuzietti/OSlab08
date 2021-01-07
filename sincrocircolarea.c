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

pthread_mutex_t mutex;
pthread_cond_t cond;
int PrimoFaiWait;
int SecondoFaiWait;

int DatoProtetto = 0;

void* primo(void* a) {
	while (1) {
		pthread_mutex_lock(&mutex);
		if (PrimoFaiWait) {
			pthread_cond_wait(&cond, &mutex);
		}
		PrimoFaiWait = 1;
		//sezione critica
		DatoProtetto += 1;
		printf("Primo");
		//fine sezione critica
		pthread_cond_signal(&cond);
		SecondoFaiWait = 0;
		pthread_mutex_unlock(&mutex);
	}
}

void* secondo(void* a) {
	while (1) {
		pthread_mutex_lock(&mutex);
		if (SecondoFaiWait) {
			pthread_cond_wait(&cond, &mutex);
		}
		SecondoFaiWait = 1;
		//sezione critica
		DatoProtetto += 1;
		printf("Secondo");
		//fine sezione critica
		pthread_cond_signal(&cond);
		PrimoFaiWait = 0;
		pthread_mutex_unlock(&mutex);


	}
}
void main(void) {
	pthread_t th;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	PrimoFaiWait = 0;
	SecondoFaiWait = 1;
	
	pthread_create(&th, NULL, primo, NULL);
	pthread_create(&th, NULL, secondo, NULL);
	pthread_exit(NULL);

}