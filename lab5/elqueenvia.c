#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
/* Redefiniendo la estructura msgbuf */
typedef struct mymsgbuf
{
 long mtype;
 int int_num;
 float float_num;
 char ch;
} mess_t;
int main()
{
 int qid;
 key_t msgkey;
 mess_t sent;
 mess_t received;
 int length;
 /* Inicialice la semilla del generador del numero pseudo random */
 srand (time (0));
/* Longitud el mensaje */
 length = sizeof(mess_t) - sizeof(long);
 msgkey = ftok(".",'m');
 /* Crea la cola */
 qid = msgget(msgkey, IPC_CREAT | 0660);
 printf("QID = %d\n", qid);
 /* Construye el mensaje */
 sent.mtype = 1;
 sent.int_num = rand();
 sent.float_num = (float)(rand())/3;
 sent.ch = 'f';
/* Envia el mensaje */
 msgsnd(qid, &sent, length, 0);
 printf("MENSAJE ENVIADO...\n");
 /* Recibe el mensaje */
 msgrcv(qid, &received, length, sent.mtype, 0);
 printf("MENSAJE RECIBIDO...\n");
 /* Controla que lo que se ha recibido sea igual a lo que se ha enviado */
 printf("Numero entero = %d (sent %d) -- ", received.int_num,
 sent.int_num);
 if(received.int_num == sent.int_num) printf(" OK\n");
 else printf("ERROR\n");
 printf("Numero flotante = %f (sent %f) -- ", received.float_num,
 sent.float_num);
 if(received.float_num == sent.float_num) printf(" OK\n");
 else printf("ERROR\n");
 printf("Char = %c (sent %c) -- ", received.ch, sent.ch);
 if(received.ch == sent.ch) printf(" OK\n");
 else printf("ERROR\n");
 /* Estruye la cola */
 msgctl(qid, IPC_RMID, 0);
}
