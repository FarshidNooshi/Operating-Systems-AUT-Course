//In The Name Of GOD
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX_EAT_TIMES 1
#define NUMBER_OF_PHOLOSOPHERS 5

pthread_mutex_t chopstick[5];


void eat(int n) 
{
    int next = (n + 1) % NUMBER_OF_PHOLOSOPHERS;
    pthread_mutex_lock(&chopstick[n]);
    pthread_mutex_lock(&chopstick[next]);

    printf("Philosopher %d is eating using chopstick[%d] and chopstick[%d].\n", n + 1, n, next);
    sleep(1);

    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[next]);
}

void *philosopher(int n)
{
    for (int i = 0; i < MAX_EAT_TIMES; i++)
    {
        printf("Philosopher %d is thinking.\n", n + 1);
        eat(n);        
        printf("Philosopher %d finished eating.\n", n + 1);
    }
}


int main()
{
    pthread_t threads[NUMBER_OF_PHOLOSOPHERS];

    for (int i = 0; i < NUMBER_OF_PHOLOSOPHERS; i++)//initializing mutex
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    for (int i = 0; i < NUMBER_OF_PHOLOSOPHERS; i++)//initializing threads
    {
        pthread_create(&threads[i], NULL, (void *) philosopher, (void *)(intptr_t) i);
    }

    for (int i = 0; i < NUMBER_OF_PHOLOSOPHERS; i++)//wait to end threads
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}