#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* myFunc1(void* args) {

    while(1) {
        pthread_mutex_lock(&mutex);
        
        printf("0\n");
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);

    }
}

void* myFunc2(void* args) {

    while(1) {
        pthread_mutex_lock(&mutex);

        pthread_cond_wait(&condition, &mutex);
        printf("1\n");

        pthread_mutex_unlock(&mutex);

    }
}

int main () {

    int number1 = 1;
    int number2 = -1;
    pthread_t p1, p2;
    int rc;

    rc = pthread_create(&p1, NULL, myFunc1, (void *)&number1); assert(rc==0);
    rc = pthread_create(&p2, NULL, myFunc2, (void *)&number1); assert(rc==0);

    rc = pthread_join(p1, NULL); assert(rc == 0);
    rc = pthread_join(p2, NULL); assert(rc == 0);

    return 0;
}