#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUMTHREAD 10

void *funz(void *arg){
    sleep(5);
    printf("%f\t", *((float*)arg));
    free(arg);
    pthread_exit(NULL);
}


int main(){
    pthread_t tid;
    srand((unsigned int) time(NULL));
    double *r;
    int i;
    for(i=0; i<10; i++){
        r = (double*) malloc(sizeof(double));
        if(r == NULL){
            /*perrror("malloc failed");*/
            pthread_exit(NULL);
        }
        *r = (double) rand();
        int threadinsucces = pthread_create(&tid, NULL, funz, r);
        if(threadinsucces){
            /*perror("error creating thread");*/
            pthread_exit(NULL);
        }

    }

    puts("exiting main");
    pthread_exit(NULL);
}
