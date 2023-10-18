// Programa en C para demostrar como trabaja pthread_equal()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_t tmp_thread;

void* func_one(void* ptr)
{
 // en este camplo comparamos los threads
 // pthread_self da un id del thread actual
 if (pthread_equal(tmp_thread, pthread_self())) {
 printf("son iguals\n");
 } else {
 printf("no son iguales\n");
 }
}

// driver code
int main()
{
// thread uno
 pthread_t thread_one;

 // asignando el id al thread uno temporalmente
 // mientras que el thread declara la variable global r
 tmp_thread = thread_one;

 // creando el thread
pthread_create(&thread_one, NULL, func_one, NULL);

 // esperando por el thread
 pthread_join(thread_one, NULL);
}
