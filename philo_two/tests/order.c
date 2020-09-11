#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
sem_t *sem2;
void* first(void* data) {
    printf("First\n"); 
    sem_post(data);
    }
void* second(void* data) { 
    sem_wait(data);
    printf("Second\n");
    sem_post(sem2); }
void* third(void* data) { 
    sem_wait(sem2);
    printf("Third\n"); }
int main () {
pthread_t t1, t2, t3;
sem_t *sem;
sem = sem_open("clezoun2s2", O_CREAT | O_EXCL, S_IRWXU, 0);
sem2 = sem_open("clezoun2s22", O_CREAT | O_EXCL, S_IRWXU, 0);
if (sem == SEM_FAILED)
    printf("err\n");
pthread_create(&t3, NULL, third, sem);
pthread_create(&t2, NULL, second, sem);
pthread_create(&t1, NULL, first, sem);
// wait for all threads
pthread_join(t1, NULL); pthread_join(t2, NULL); pthread_join(t3, NULL);
sem_close(sem);
sem_close(sem2);
sem_unlink("clezoun2s2");
sem_unlink("clezoun2s22");
}