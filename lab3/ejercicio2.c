#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int n; // Número de procesos hijos a crear
    printf("Ingrese la cantidad de procesos hijos a crear: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid_t child_pid = fork();

        if (child_pid == 0) {
            // Código del proceso hijo
            printf("Soy el proceso hijo %d (PID %d)\n", i + 1, getpid());
            exit(0); // El proceso hijo termina
        } else if (child_pid < 0) {
            // Error al crear el proceso hijo
            perror("Error al crear el proceso hijo");
            exit(1);
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Todos los procesos hijos han terminado.\n");

    return 0;
}
