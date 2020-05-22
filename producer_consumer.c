#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <error.h>

#define MAX 5

pthread_cond_t empty, full;

pthread_mutex_t mutex;

int data[5] = {0};
int currentPosIndex = 0;
int count = 0;
void *producer_func(void* args) {

    while (1) {

        pthread_mutex_lock(&mutex);

        while(currentPosIndex == MAX)
            pthread_cond_wait(&full, &mutex);


        data[currentPosIndex++] = count;

        count++;    

        pthread_cond_signal(&empty);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void *consumer_func(void* args) {
    while(1) {

        pthread_mutex_lock(&mutex);

        while(currentPosIndex == 0)
            pthread_cond_wait(&empty, &mutex);

        printf("%d\n", data[--currentPosIndex]);


        pthread_cond_signal(&full);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}


int main() {
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, producer_func,(void*) NULL);
    pthread_create(&consumer, NULL, consumer_func,(void*) NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    return 0;
}