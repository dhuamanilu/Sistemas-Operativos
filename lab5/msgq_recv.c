/* Nombre de archivo: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define PERMS 0644
struct my_msgbuf {
 long mtype;
 char mtext[200];
};
int main(void) {
 struct my_msgbuf buf;
 int msqid;
 int toend;
 key_t key;

 if ((key = ftok("msgq.txt", 'B')) == -1) {
 perror("ftok");
 exit(1);
 }

 if ((msqid = msgget(key, PERMS)) == -1) { /* conectando con la cola */
 perror("msgget");
 exit(1);
 }
 printf("cola de mensajes lista para recibir mensajes.\n");

 for(;;) { /* normalmente la recepción nunca termina pero tiene una conclusion */
 /* este programa finaliz con la cadena end */
 if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
 perror("msgrcv");
 exit(1);
 }
 printf("recvd: \"%s\"\n", buf.mtext);
 toend = strcmp(buf.mtext,"end");
 if (toend == 0)
 break;
 }
 printf("cola de mensajes hecha recibiendo mensajes.\n");
 system("rm msgq.txt");
 return 0;
}
