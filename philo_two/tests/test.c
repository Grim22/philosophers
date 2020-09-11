#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX 10000
int counter = 0;
void* count(void *sem) 
{
int i;
// sem_t   *sem;

// sem = (sem_t*)void_sem;
i = 0;
while (i < MAX)
{
    sem_wait(sem);
    counter++;
    if (sem_post(sem) == -1)
        perror("error:");
    i++;
}
return(NULL);
}

int main () 
{
sem_t *sem;
pthread_t t1, t2;
sem = sem_open("clezouv", O_CREAT | O_EXCL, S_IRWXU, 1);
if (sem == SEM_FAILED)
    printf("err\n");
pthread_create(&t1, NULL, count, sem); // create first thread
pthread_create(&t2, NULL, count, sem); // create second thread
pthread_join(t1, NULL); // wait for first thread
pthread_join(t2, NULL); // wait for second thread
printf("Counter: %d\n", counter);
sem_close(sem);
sem_unlink("clezouv");
}