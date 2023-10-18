/* decimo.c - Redirección usando dup2 */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main (int contargs, char *args[]){
	int desc_fich;
	if (contargs < 3){
		printf ("Formato: %s fichero comando [opciones].\n", args[0]);
		exit (1);
	}
	printf ("Ejemplo de redirección.\n");
	desc_fich = open (args[1], O_CREAT|O_TRUNC|O_WRONLY, 0);
	dup2 (desc_fich, 1); /* Redirige la salida normal */
	close (desc_fich);
	execvp (args[2], &args[2]);/* Ejecuta comando */
	exit(1);
}
