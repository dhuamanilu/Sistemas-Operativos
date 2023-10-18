// Programa en C para demostrar la cancelación de los threads
// usando el id del thread
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
// To Count
int counter = 0;
// temporalmente el thread será
// almacenando el id del segundo thread
pthread_t tmp_thread;
// thread_uno llama a func
void* func(void* p)
{
while (1) {
printf("thread numero uno\n");
sleep(1); // duerme por 1 segundo
counter++;
// para salir si el contadore es 5
if (counter==2) {
// para cancelar desde thread_dos
pthread_cancel(tmp_thread);
// Para finalizar desde el thread_uno
pthread_exit(NULL);
}
}
}
// thread_two llama a la función func2
void* func2(void* p)
{
//alojando el id del thread_two en tmp_thread
tmp_thread = pthread_self();
while (1) {
printf("thread numero dos ");
sleep(1); // dormir por 1 segundo
}
}
int main()
{
// declarando dos threads
pthread_t thread_one, thread_two;
// creando el thread 1
pthread_create(&thread_one, NULL, func, NULL);
// creando el trhread 2
pthread_create(&thread_two, NULL, func2, NULL);
// esperando cuando el thread 1 es completado
pthread_join(thread_one, NULL);
// esperando cuando el thread 2 es completado
pthread_join(thread_two, NULL);
}
