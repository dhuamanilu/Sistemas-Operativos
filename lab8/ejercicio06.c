#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h> //para imprimir
sem_t mutex;
void *my_thread(void *arg){
 while(1){
 sem_wait(&mutex);
printf("Entra\n");
sleep(4);
printf("Sale\n");
 sem_post(&mutex);
 }
}
int main(){
pthread_t thread1_id, thread2_id;
sem_init(&mutex, 0, 1);
pthread_create(&thread1_id, NULL, &my_thread, NULL);
sleep(2);
pthread_create(&thread2_id, NULL, &my_thread, NULL);
sleep(2);
pthread_join(thread1_id, NULL);
sleep(2);
pthread_join(thread2_id, NULL);
}
