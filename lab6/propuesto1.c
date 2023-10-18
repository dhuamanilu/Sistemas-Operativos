#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4  // Número de threads a utilizar
#define ARRAY_SIZE 100  // Tamaño del arreglo

int array[ARRAY_SIZE];
int partialSums[NUM_THREADS] = {0};

void *sumArray(void *arg) {
    int thread_id = *(int *)arg;
    int elements_per_thread = ARRAY_SIZE / NUM_THREADS;
    int start = thread_id * elements_per_thread;
    int end = (thread_id == NUM_THREADS - 1) ? ARRAY_SIZE : start + elements_per_thread;
    
    for (int i = start; i < end; i++) {
        partialSums[thread_id] += array[i];
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Inicializa el arreglo con valores
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }
    
    // Crea los threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sumArray, &thread_ids[i]);
    }
    
    // Espera a que los threads terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Calcula la suma total a partir de los resultados parciales
    int totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalSum += partialSums[i];
    }
    
    printf("La suma total del arreglo es: %d\n", totalSum);
    
    return 0;
}
