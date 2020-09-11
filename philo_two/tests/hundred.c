
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

sem_t   *sem1;
sem_t   *sem2;

void    *even(void *data)
{
    int i;

    i = 0;
    while (i <= 100)
    {
        sem_wait(sem1);
        printf("%d\n", i);
        i = i + 2;
        sem_post(sem2);
    }
}

void    *odd(void *data)
{
    int i;

    i = 1;
    while (i <= 100)
    {
        sem_wait(sem2);
        printf("%d\n", i);
        i = i + 2;
        sem_post(sem1);
    }
}

int main()
{

    pthread_t t1, t2;
    sem1 = sem_open("clezope2", O_CREAT | O_EXCL, S_IRWXU, 1);
    sem2 = sem_open("clezope", O_CREAT | O_EXCL, S_IRWXU, 0);
    pthread_create(&t1, NULL, &odd, NULL);
    pthread_create(&t2, NULL, &even, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_close(sem1);
    sem_close(sem2);
    sem_unlink("clezope2");
    sem_unlink("clezope");
}