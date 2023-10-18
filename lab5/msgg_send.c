/* Nombre de archivo: msgq_send.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define PERMS 0644
struct my_msgbuf {
 long mtype;
 char mtext[200];
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
 printf("cola de mensajes: lista para enviar mensajes.\n");
 printf("Ingrue la linea de texto, ^D ^para salir:\n");
 buf.mtype = 1; /* No nos importa este caso en realidad */

 while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
 len = strlen(buf.mtext);
 /*remueve newline al final si esta existe */
 if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
 if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
 perror("msgsnd");
 }
 strcpy(buf.mtext, "end");
 len = strlen(buf.mtext);
 if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
 perror("msgsnd");

 if (msgctl(msqid, IPC_RMID, NULL) == -1) {
 perror("msgctl");
 exit(1);
 }
 printf("cola de mensajes hecha enviando mensajes.\n");
 return 0;
}
