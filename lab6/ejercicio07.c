// Un programa en C para demostrar la cancelación de un thread propio
// usando el id del thread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void* calls(void* ptr)
{
printf("Cancelado");
// Para salir del actual thread
// pthread_self() devuelve el valor del id del thread
pthread_cancel(pthread_self());
return NULL;
}
int main()
{
// NULL cuando no hay atributo
pthread_t thread;
// Llamada a funciíon
pthread_create(&thread, NULL, calls, NULL);
// Esperando cuando el thread es completado
pthread_join(thread, NULL);
return 0;
}
