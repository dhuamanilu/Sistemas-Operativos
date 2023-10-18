#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644
#define MAX_MESSAGE_SIZE 8

struct my_msgbuf {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE]; // Tamaño ajustado a 8
};

int main(void) {
    struct my_msgbuf buf;
    int msqid;
    int len;
    key_t key;
    system("touch msgq.txt");
    
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Cola de mensajes: lista para enviar mensajes.\n");
    printf("Ingrese la línea de texto, ^D para salir:\n");
    buf.mtype = 1; /* No nos importa este caso en realidad */

    while (fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
        len = strnlen(buf.mtext, sizeof(buf.mtext)); // Usar strnlen para obtener la longitud
        if (msgsnd(msqid, &buf, len, 0) == -1) { // No se necesita +1 para '\0'
            perror("msgsnd");
        }
    }

    strcpy(buf.mtext, "end");
    len = strlen(buf.mtext);
    if (msgsnd(msqid, &buf, len, 0) == -1) { // No se necesita +1 para '\0'
        perror("msgsnd");
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    printf("Cola de mensajes hecha enviando mensajes.\n");
    return 0;
}
