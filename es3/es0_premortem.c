#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>
/*string.h*/
#define TIME 1000
struct argomenti{
    pthread_t idpadre;
    intptr_t index;
}
typedef struct argomenti argomenti;
void main(){
    usleep((useconds_t)TIME);
    pthread_t tid;
    intptr_t index = =0;
    //finire
    int errThr = pthread_create(&tid, NULL, funz,(void *)args);
}