// Programa en C para demostrar como trabaja pthread_equal()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
// la variable global pthread_t es declarada
pthread_t tmp_thread;
void* func_one(void* ptr)
{
tmp_thread = pthread_self(); // assign the id of thread one in
// temporalmente el thread declara la variable global
}
void* func_two(void* ptr)
{
pthread_t thread_two = pthread_self();
// compara dos thread
if (pthread_equal(tmp_thread, thread_two)) {
printf("igual\n");
} else {
printf("no igual\n");
}
}
int main()
{
pthread_t thread_one, thread_two;
// creando el thread uno
pthread_create(&thread_one, NULL, func_one, NULL);
// creando el thread dos
pthread_create(&thread_two, NULL, func_two, NULL);
// esperando por el thread uno
pthread_join(thread_one, NULL);
// esperando por el thread dos
pthread_join(thread_two, NULL);
}
