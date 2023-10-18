#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#define MSGSZ 128
/*
* Declara la estructura del mensaje.
*/
typedef struct msgbuf {
 long mtype;
 char mtext[MSGSZ];
} message_buf;
int main()
{
 int msqid;
 key_t key;
 message_buf rbuf;
 /*
 * Consigue el id de la cola de mensje para el
 * "name" 1234, el cual ha sido creado por
 * el servidor.
 */
key = 1234;
 if ((msqid = msgget(key, 0666)) < 0) {
 perror("msgget");
 exit(1);
 }

 /*
 * Recibe una respuesta del mensaje de tipo 1.
 */
 if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
 perror("msgrcv");
 exit(1);
 }
 /*
 * Imprime la respuesta.
 */
 printf("%s\n", rbuf.mtext);
exit(0);
}
