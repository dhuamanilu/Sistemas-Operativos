// programa en CPP para ilustrar
// el manejador de señales por defecto
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void handle_sigint(int sig)
{
printf("Señal cogida %d\n", sig);
}
int main()
{
signal(SIGINT, handle_sigint);
while (1)
{
printf("hola mundo\n");
sleep(1);
}
return 0;
}
