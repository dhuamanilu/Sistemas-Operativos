#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
void *fun1();
void *fun2();
int shared=1; //variable compartida
pthread_mutex_t l; //mutex lock
int main()
{
pthread_mutex_init(&l, NULL); //inicializando mutex locks
pthread_t thread1, thread2;
pthread_create(&thread1, NULL, fun1, NULL);
pthread_create(&thread2, NULL, fun2, NULL);
pthread_join(thread1, NULL);
pthread_join(thread2,NULL);
printf("El valor final de la variable compartida es %d\n",shared); //imprime la ultima actualización del valor de variable compartida
}
void *fun1()
{
 int x;
 printf("Thread1 intentando adquirir la cerradura \n");
 pthread_mutex_lock(&l);
//thread uno adquiriendo la cerradura. Ahora los otros threads no serán capacesde de adquirir la cerradura
//hasta que sea liberado por el threada 1
 printf("Thread1 adquiere la cerradura\n");
 x=shared;//el thread lee el valor de la variable compartida
 printf("Thread1 lee el valor de la variable compartida %d\n",x);
 x++; //thread uno incremente al valor
 printf("Actualizacion local del Thread1: %d\n",x);
 sleep(1); //thread uno es prevenido por thread 2
 shared=x; //thread uno actualiza el valor de la variable compartida
 printf("Valor de la variable compartida actualizada del Thread1 es: %d\n",shared);
 pthread_mutex_unlock(&l);
 printf("Thread1 libera la cerradura \n");
 return NULL;
}
void *fun2()
{
 int y;
 printf("Thread2 intenta adquiriri la cerradura \n");
 pthread_mutex_lock(&l);
 printf("Thread2 adquiere la cerradura \n");
 y=shared;//thread dos lee el valor de la variable compartida
 printf("Thread2 lee el valor de %d\n",y);
 y--; //thread two incrementa el valor
 printf("Actualización Local del Thread2: %d\n",y);
 sleep(1); //thread dos es prevenido por thread 1
 shared=y; //thread uno es actualiza el valor de la variable compartida
 printf("Valor de la variable compartida actualizado por el Thread2 es: %d\n",shared);
 pthread_mutex_unlock(&l);
printf("Thread2 libera la cerradura \n");
 return NULL;
}
