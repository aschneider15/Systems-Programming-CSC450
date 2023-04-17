#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * iterate(void * arg);

int main() {
    pthread_t tid;
    pthread_t tid2;
    pthread_t tid3;

    pthread_create(&tid, NULL, iterate, NULL);
    pthread_create(&tid2, NULL, iterate, NULL);
    pthread_create(&tid3, NULL, iterate, NULL);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
}

void * iterate(void * arg) {
    for(int i = 0; i < 100; i++){
        printf("%d\n", i+1);
    }
}