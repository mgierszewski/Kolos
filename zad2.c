#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int zmienna_globalna = 0;
sem_t semafor;

void *watek(void *arg) {
    for (int i = 0; i < 100; i++) {
        sem_wait(&semafor);
        zmienna_globalna++;
        sem_post(&semafor);
        usleep(100000); // 100 ms
    }
    return NULL;
}

int main() {
    sem_init(&semafor, 0, 1);

    pthread_t watek1, watek2, watek3;

    pthread_create(&watek1, NULL, watek, NULL);
    pthread_create(&watek2, NULL, watek, NULL);
    pthread_create(&watek3, NULL, watek, NULL);

    pthread_join(watek1, NULL);
    pthread_join(watek2, NULL);
    pthread_join(watek3, NULL);

    printf("Wartość zmiennej globalnej: %d\n", zmienna_globalna);

    sem_destroy(&semafor);
    return 0;
}