#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUMTHREAD 10

void *funz(void *arg){
    sleep(5);
    printf("%f\t", *((float*)arg));
}


int main(){
    pthread_t tid;
    srand((unsigned int) time(NULL));
    double *r;

    for(int i=0; i<NUMTHREAD; i++){
        r = (double*) malloc(sizeof(double));
        if(r == NULL){
            perrror("malloc failed");
            pthread_exit(NULL);
        }
        *r = ceil(rand() * 100);
        int threadinsucces = pthread_create(&tid, NULL, funz, r);
        if(threadinsucces){
            perror("error creating thread");
            pthread_exit(NULL);
        }

    }

    puts("exiting main");
    pthread_exit(NULL);
}
