#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid, child_pid, grandchild_pid, greatgrandchild_pid;

    // Proceso padre
    pid = getpid();
    printf("Soy el proceso padre (PID %d)\n", pid);

    // Crear un proceso hijo (nieto)
    child_pid = fork();

    if (child_pid == 0) {
        // Código del proceso hijo (nieto)
        pid = getpid();
        printf("Soy el proceso hijo (nieto) (PID %d), mi padre es el proceso padre (PID %d)\n", pid, getppid());

        // Crear un proceso nieto
        grandchild_pid = fork();

        if (grandchild_pid == 0) {
            // Código del proceso nieto
            pid = getpid();
            printf("Soy el proceso nieto (PID %d), mi padre es el proceso hijo (nieto) (PID %d)\n", pid, getppid());

            // Crear un proceso bisnieto
            greatgrandchild_pid = fork();

            if (greatgrandchild_pid == 0) {
                // Código del proceso bisnieto
                pid = getpid();
                printf("Soy el proceso bisnieto (PID %d), mi padre es el proceso nieto (PID %d)\n", pid, getppid());
            }
        }
    }

    // Esperar a que todos los procesos terminen
    wait(NULL);

    return 0;
}
