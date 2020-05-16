#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

char ret_status[10][100];

void * thread_routine(void * arg) {
    int my_id = *((int *)arg);

    sleep(1);

    printf("Thread ID: %d, Hello Guys!\n",my_id);

    sprintf(ret_status[my_id], "Thread Id: %d : %d", my_id, my_id+10);

    if(my_id == 5)
        sleep(10);

    pthread_exit(ret_status[my_id]); 
}

int main() {

    pthread_t tid[10];
    int i , r ;
    void * status;

    char buf[128] = {0};

    int thread_no[10];
    for(i = 0; i < 10; i++) {
        thread_no[i] = i;

        if((r = pthread_create(&tid[i], NULL, thread_routine, (void *)&thread_no[i]) ) != 0) {
            strerror_r(r, buf,sizeof(buf));
            fprintf(stderr,"Error: %d (%s)\n",r,buf);
            exit(-1);
        }
    }
    sleep(2);
    if((r = pthread_cancel(tid[5])) != 0) {
        strerror_r(r, buf,sizeof(buf));
        fprintf(stderr,"Error: %d (%s)\n",r,buf);
        exit(-1);
    }

    for(i = 0; i< 10; i++) {

        if((r = pthread_join(tid[i], &status)) != 0) {
            strerror_r(r, buf,sizeof(buf));
            fprintf(stderr,"Error: %d (%s)\n",r,buf);
            exit(-1);
        }

        if(status == PTHREAD_CANCELED) {
            printf("%d is cancelled\n", i);
        }
        else {
            printf("%d status is %s\n", i, (char*)status);
        }
    }
    return 0;
}
