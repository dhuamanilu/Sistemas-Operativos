// Programa en para la cola de mensajes (proceso lector)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Estructura para la cola de mensajes
struct mesg_buffer {
 long mesg_type;
 char mesg_text[100];
} message;

int main()
{
 key_t key;
 int msgid;

 // ftok para generar la clave unica
 key = ftok("progfile", 65); 
// msgget para crear un cola de mensajes
 // y retorna el identificador
 msgid = msgget(key, 0666 | IPC_CREAT);

 // msgrcv para recibir el mensaje
 msgrcv(msgid, &message, sizeof(message), 1, 0);

 // muestre el mensajedisplay the message
 printf("Los datos recibidos son : %s \n",
 message.mesg_text);

 // Para destruir la cola de mensajes
 msgctl(msgid, IPC_RMID, NULL);

 return 0;
}
