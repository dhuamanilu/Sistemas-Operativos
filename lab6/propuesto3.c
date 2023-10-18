#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variable compartida
int sharedVar = 0;

void *threadFunction(void *arg) {
    int *threadVar = (int *)arg;
    printf("Hilo: El valor de la variable compartida es %d\n", *threadVar);
    
    // Modificar la variable compartida
    *threadVar = 42;

    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int mainVar = sharedVar; // Copia el valor de la variable compartida

    printf("Función principal: El valor de la variable compartida es %d\n", mainVar);

    // Crear un hilo y pasar la dirección de la variable compartida
    pthread_create(&thread, NULL, threadFunction, &sharedVar);

    // Esperar a que el hilo termine
    pthread_join(thread, NULL);

    // Verificar que la variable compartida ha sido modificada
    printf("Función principal: El valor de la variable compartida es %d\n", sharedVar);

    return 0;
}
