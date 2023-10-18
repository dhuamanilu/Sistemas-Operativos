#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// Permite crear una variable global para cambiarlo in los threads
int g = 0;
// La función será ejecutada por todos los threads
void *myThreadFun(void *vargp)
{
// Aloja el valor del argumento pasado por el thread
int *myid = (int *)vargp;
// Permite crear una variable estatic para observar los cambios
static int s = 0;
// Cambia la variable global y estatica
++s; ++g;
// Imprime los argumentos de las variables global y estaticas
printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}
int main()
{
int i;
pthread_t tid;
// Nos permtie crear tres threads
for (i = 0; i < 3; i++)
pthread_create(&tid, NULL, myThreadFun, (void *)&tid);
pthread_exit(NULL);
return 0;
}
