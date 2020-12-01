#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>	/* uintptr_t */
#include <inttypes.h>	/* PRIiPTR */
#include <errno.h>

#define SIZE 100
#define NUMTHREAD 1000

void * funz(void *arg){
    printf("%" PRIiPTR "\n", (intptr_t)arg);
    pthread_exit(NULL);
}

void main(){
    intptr_t t=0;
    pthread_t tid[NUMTHREAD];
    char buff[SIZE];
    int i=0;
    while (1)
    {
        while (i < NUMTHREAD)
        {
            int err = pthread_create(&tid[i], NULL, funz, (void *)t);
            if (err)
            {
                strerror_r(err, buff, SIZE);
                puts(buff);
                exit(-1);
            }
            t++;
            i++;
        }
        i=0;
        for(int x=0; x<NUMTHREAD; x++){
            int errJoin = pthread_join(tid[x],NULL);
            if(errJoin){
                strerror_r(errJoin,buff,SIZE);
                puts(buff);
                exit(-1);
            }
        }
    }
    pthread_exit(NULL);
}
