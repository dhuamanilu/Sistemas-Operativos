#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Crear un proceso hijo
    child_pid = fork();

    if (child_pid == 0) {
        // Código del proceso hijo
        printf("Soy el proceso hijo (PID %d)\n", getpid());
        sleep(2); // Simular un trabajo en el proceso hijo
        exit(0); // El proceso hijo termina
    } else if (child_pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        exit(1);
    } else {
        // Código del proceso padre
        printf("Esperando a que el proceso hijo termine...\n");
        wait(NULL); // Esperar a que el proceso hijo termine y obtener su estado
        printf("El proceso hijo ha terminado.\n");
    }

    return 0;
}
