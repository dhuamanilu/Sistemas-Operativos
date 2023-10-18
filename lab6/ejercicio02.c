// Importando la librería Pthread
#include <pthread.h>
// Importando la librería para usar printf
#include <stdio.h>
// Esta función tomo en un puntero
void * ThreadFunction(void *arguments)
{
 printf("Thread Running\n");
 return NULL;
}
int main() {
 // Creando la locación donde el ID del thread recientemente creado recientemente
 // el thread será alojado
 pthread_t thread1;
 printf("Llamando al thread \n");
// Creando el thread
 pthread_create(&thread1, NULL, ThreadFunction, NULL);
 return 0;
}
