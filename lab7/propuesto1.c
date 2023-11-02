#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4

int contador = 0;
pthread_mutex_t mutex;  // Declara un mutex

void *hilo(void *arg) {
    int i;
    i = (int)arg;

    // Bloquea el mutex antes de modificar el contador
    pthread_mutex_lock(&mutex);

    contador = contador + i;
    printf("Hilo %u, contador = %d\n", (unsigned int)pthread_self(), contador);

    // Desbloquea el mutex después de la modificación
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main() {
    int i;
    pthread_t thread[NTHREADS]; // Vector para definir los hilos

    // Inicializa el mutex
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread[i], NULL, hilo, (void *)i);
    }

    for (i = 0; i < NTHREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    // Destruye el mutex una vez que no sea necesario
    pthread_mutex_destroy(&mutex);

    printf("Hilo principal, contador = %d\n", contador);
    pthread_exit(0);
}

