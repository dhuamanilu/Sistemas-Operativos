#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_THREADS 100
#define NUM_PROCESSES 100

void *threadFunction(void *arg) {
    int thread_id = *((int *)arg);
    printf("Hilo %d creado con PID %d y espacio de memoria %p.\n", thread_id, getpid(), &thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Creación de hilos:\n");

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Creación de procesos:\n");

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Este es el proceso hijo.
            printf("Proceso hijo %d creado con PID %d y espacio de memoria %p.\n", i, getpid(), &i);
            exit(0);
        } else if (pid < 0) {
            perror("Error al crear el proceso hijo.");
            exit(1);
        }
    }

    // Espera a que todos los procesos hijos terminen.
    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    return 0;
}
