#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MSGSZ 128
/*
* Declara la estructura del mensaje.
*/
typedef struct msgbuf {
 long mtype;
 char mtext[MSGSZ];
 } message_buf;
int main(){
 int msqid;
 int msgflg = IPC_CREAT | 0666;
 key_t key;
message_buf sbuf;
 size_t buf_length;
 /*
 * Consigue el id de la cola de mensaje para el
 * "name" 1234, el cual ha sido creado
 * por el servidor.
 */
 key = 1234;
(void) fprintf(stderr, "\nmsgget: llamando a msgget(%#lx,\
%#o)\n",
key, msgflg);
 if ((msqid = msgget(key, msgflg )) < 0) {
 perror("msgget");
exit(1);
 }
 else
 (void) fprintf(stderr,"msgget: msgget exitoso: msqid = %d\n", msqid);
 /*
 * We'll send message type 1
 */

 sbuf.mtype = 1;

 (void) fprintf(stderr,"msgget: msgget exitoso: msqid = %d\n", msqid);

 (void) strcpy(sbuf.mtext, "¿Conseguistes esto?");

 (void) fprintf(stderr,"msgget: msgget exitoso: msqid = %d\n", msqid);

 buf_length = strlen(sbuf.mtext) + 1 ;


 /*
 * Enviando mensaje.
 */
 if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
 printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
 perror("msgsnd");
 exit(1);
 }
 else
 printf("Message: \"%s\" Sent\n", sbuf.mtext);

 exit(0);
}
