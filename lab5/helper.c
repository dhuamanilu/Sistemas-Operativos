#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t clave = ftok("/temp", 40);
    int msgid = msgget(clave, 0660 | IPC_CREAT);

    if (msgid < 0) {
        perror("Error al crear la cola de mensajes");
        exit(1);
    }

    printf("Cola de mensajes creada con éxito.\n");

    return 0;
}
