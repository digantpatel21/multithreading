#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

void *thread1(void *data) {

    while(1) {
        pthread_mutex_lock(&lock);

        pthread_cond_wait(&cond, &lock);

        printf("0\n");


        pthread_mutex_unlock(&lock);

    }
    pthread_cond_signal(&cond);

    return NULL;
}


void *thread2(void *data) {

    while(1) {
        pthread_mutex_lock(&lock);

        pthread_cond_wait(&cond, &lock);

        printf("1\n");

        pthread_mutex_unlock(&lock);

    }

    pthread_cond_signal(&cond);

    return NULL;
}


int main() {
    pthread_t tid1, tid2;

    printf("State-1\n");

    pthread_mutex_init(&lock, 0);
    pthread_cond_init(&cond, 0);
    pthread_create(&tid1, NULL, thread1, NULL);

    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}