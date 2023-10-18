#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>

#define MAX 10

// Estructura para la cola de mensajes
struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAX]; // Cambiamos el tamaño a MAX
};

int main() {
    key_t key;
    int msgid;

    // ftok genera la clave única
    key = ftok("progfile", 65);

    // msgget crea una cola de mensajes y retorna el identificador
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct mesg_buffer message;
    message.mesg_type = 1;

    printf("Escribe un número entero: ");
    
    // Leer la entrada del usuario
    char input[MAX];
    fgets(input, MAX, stdin);
    
    // Validar si la entrada es un número entero
    int valid = 1;
    for (int i = 0; i < strlen(input) - 1; i++) {
        if (!isdigit(input[i])) {
            valid = 0;
            break;
        }
    }
    
    if (valid) {
        // Convertir la entrada a un número entero y almacenarla en el mensaje
        int number = atoi(input);
        snprintf(message.mesg_text, MAX, "%d", number);

        // Enviar el mensaje
        msgsnd(msgid, &message, sizeof(message.mesg_text), 0);
        printf("El número entero enviado es: %s\n", message.mesg_text);
    } else {
        printf("Entrada no válida. Debes ingresar un número entero.\n");
    }

    return 0;
}
