#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //cabecera para usar sleep().
#include <pthread.h>
// Una función normal de c que es ejecutadad en un thread
// cuando es nombrada, es especificada como pthread_create()
void *myThreadFun(void *vargp)
{
 sleep(1);
 printf("Imprimiendo ejemplo Thread \n");
 return NULL;
}

int main()
{
 pthread_t thread_id;
 printf("Antes del Thread\n");
 pthread_create(&thread_id, NULL, myThreadFun, NULL);
 pthread_join(thread_id, NULL);
 printf("Despues del Thread\n");
 exit(0);
}
