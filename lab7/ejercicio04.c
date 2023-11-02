#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // Incluye la biblioteca para 'sleep'

pthread_mutex_t ml;
void* Test(char* p, char* q) {
 pthread_mutex_lock(&ml);
 printf("%s...\n", p);
 sleep(5);
 printf("%s...\n", q);
 sleep(5);
 pthread_mutex_unlock(&ml);
 }
void* T1(void* z) {
 Test("Inicializado", "1er Thread"); }
void* T2(void* z) {
 Test("Inicializado ", "2do Thread"); }
int main() {
 pthread_t t1, t2;
 pthread_create(&t1, NULL, &T1, NULL);
 pthread_create(&t2, NULL, &T2, NULL);
 while(1) {}
 exit(0);
}
