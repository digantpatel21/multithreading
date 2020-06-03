#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t zeros_turn = PTHREAD_COND_INITIALIZER;
pthread_cond_t ones_turn = PTHREAD_COND_INITIALIZER;
pthread_cond_t twos_turn = PTHREAD_COND_INITIALIZER;

int number = 0;

int turn = 0;

void *modulo_zero_square(void * argv) {

    while(1) {

        pthread_mutex_lock(&mutex);

        while(turn != 0)
            pthread_cond_wait(&zeros_turn, &mutex);

        printf("%d\'s square is: %d, thread function is modulo_zero_square\n", number, number*number);

        turn = (turn+1)%3;

        number++;

        sleep(1);

        pthread_cond_signal(&ones_turn);

        pthread_mutex_unlock(&mutex);

    }

    return NULL;
}


void *modulo_one_square(void * argv) {

    while(1) {

        pthread_mutex_lock(&mutex);

        while(turn != 1)
            pthread_cond_wait(&ones_turn, &mutex);

        printf("%d\'s square is: %d, thread function is modulo_one_square\n", number, number*number);

        turn = (turn+1)%3;

        number++;

        sleep(1);
        pthread_cond_signal(&twos_turn);

        pthread_mutex_unlock(&mutex);

    }

    return NULL;
}


void *modulo_two_square(void * argv) {

    while(1) {

        pthread_mutex_lock(&mutex);

        while(turn != 2)
            pthread_cond_wait(&twos_turn, &mutex);

        printf("%d\'s square is: %d, thread function is modulo_two_square\n", number, number*number);

        turn = (turn+1)%3;

        number++;

        sleep(1);

        pthread_cond_signal(&zeros_turn);

        pthread_mutex_unlock(&mutex);

    }

    return NULL;
}


int main() {

    pthread_t tid[3];

    void* (*fun[]) (void*) = {modulo_zero_square, modulo_one_square, modulo_two_square};

    for(int index  = 0; index < 3; index++) {
        pthread_create(&tid[index], NULL, fun[index], (void*) NULL);
    }

    for(int index  = 0; index < 3; index++) {
        pthread_join(tid[index], NULL);
    }

    return 0;
}