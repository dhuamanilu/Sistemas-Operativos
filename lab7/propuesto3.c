#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 1000000; i++) {  // Incrementa 1,000,000 veces por hilo
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // Lee mails
        // Incrementa
        // Escribe mails
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threads[10];  // Arreglo de 10 hilos
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 10; i++) {
        if (pthread_create(&threads[i], NULL, routine, NULL) != 0) {
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error al unirse al hilo %d\n", i);
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Número de mails: %d\n", mails);
    return 0;
}
