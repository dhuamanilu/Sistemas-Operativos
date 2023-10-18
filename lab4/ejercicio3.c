#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define LEER 0
#define ESCRIBIR 1
int main (){
	int descr[2]; /* Descriptores de E y S de la turbería */
	int bytesleidos;
	char mensaje[100],
	*frase="Veremos si la transferecia es buena.";
	printf ("Ejemplo de tuberÍa entre padre e hijo.\n");
	pipe (descr);
	if (fork () == 0){
		close (descr[LEER]);
		write (descr[ESCRIBIR], frase, strlen(frase)+1);// +1 para incluir el carácter nulo
		close (descr[ESCRIBIR]);
	}
	else{
		close (descr[ESCRIBIR]);
		bytesleidos = read (descr[LEER], mensaje, 100);
		printf ("Bytes leidos: %d\n", bytesleidos);
		printf ("Mensaje: %s\n", mensaje);
		close (descr[LEER]);
	}
}
