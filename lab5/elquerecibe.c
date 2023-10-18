#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h> // Para fork y sleep
/* Redefine la estructura del mensaje */
typedef struct mymsgbuf
{
 long mtype;
 int num;
} mess_t;
int main()
{
 int qid;
 key_t msgkey;
 pid_t pid;
 mess_t buf;
 int length;
 int cont;
 length = sizeof(mess_t) - sizeof(long);
 msgkey = ftok(".",'m');
 qid = msgget(msgkey, IPC_CREAT | 0660);
 if(!(pid = fork())){
 printf("HIJO - QID = %d\n", qid);
 srand (time (0));
 for(cont = 0; cont < 10; cont++){
 sleep (rand()%4);
 buf.mtype = 1;
 buf.num = rand()%100;
 msgsnd(qid, &buf, length, 0);
 printf("HIJO – NUMERO DE MENSAJE %d: %d\n", cont+1, buf.num);
 }
 return 0;
 }
 printf("PADRE - QID = %d\n", qid);
 for(cont = 0; cont < 10; cont++){
 sleep (rand()%4);
 msgrcv(qid, &buf, length, 1, 0);
 printf("PADRE – NUMERO DE MENSAJE %d: %d\n", cont+1, buf.num);
 }
 msgctl(qid, IPC_RMID, 0);
 return 0;
}
