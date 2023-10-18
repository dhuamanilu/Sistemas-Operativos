#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
//Declaramos los prototipos de funciones
void manejador(int signum);
//Variables globales
int con = 0;
//Función principal
main(int argc, char **argv)
{
//Capturamos la señal SIGINT
signal(SIGINT,manejador);
printf("Ejemplo de signal\n");
//Hacemos un bucle para permitir que se hagan hasta 5 SIGINTs
while(con<=5);
}
//Funcion manejador
//Cuando se presiona un sigint se llama a esta función
void manejador (int signum){
printf("\nRecibi la señal sigint\n");
con++;
signal(SIGINT,manejador);
}
