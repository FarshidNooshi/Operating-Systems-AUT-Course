#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_RESOURCES 5
#define NUMBER_OF_CUSTOMERS 5
#define MAX_CUSTOMER_ITERATION 10
#define MAX_FILE_NAME "max.txt"

void run_program();                                     // running program after initiating arrays.
bool is_safe();                                         // to check if the state is safe or not
char *req_to_str(int req[]);                            // casting int array to string
void *customer_thread(int n);                           // thread for use as a costumer in bankers problem
bool is_need_less_than_work(int need_i[], int work[]);  // declaration says it all
int request_resources(int customer_num, int request[]); // as described in manual
int release_resources(int customer_num, int request[]); // as described in manual

sem_t mutex;

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {0};
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    // reading inputs
    if (argc <= NUMBER_OF_RESOURCES)
    {
        printf("Not enough arguments\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] = atoi(argv[i + 1]);
    }
    FILE *file_pointer = fopen(MAX_FILE_NAME, "r");
    if (file_pointer == NULL)
    {
        printf("%s not found.\n", MAX_FILE_NAME);
        return 0;
    }
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            fscanf(file_pointer, "%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    // printing initial values of the problem
    printf("Available:\n");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Need:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("Allocation:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("Maximum:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
        {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("===================\n\n");
    // running the program
    run_program();
    return 0;
}

void run_program()
{
    sem_init(&mutex, 0, 1); // initializing the lock

    // creating threads
    pthread_t customer_threads[NUMBER_OF_CUSTOMERS];
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        pthread_create(&customer_threads[i], NULL, (void *)customer_thread, (void *)(intptr_t)i);
    }
    // waiting for all threads to finish
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }
}

bool is_need_less_than_work(int need_i[], int work[]) // checking if need array is less than or equal work array
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        if (need_i[i] > work[i])
        {
            return false;
        }
    }
    return true;
}

bool is_safe() // checking if current state is safe
{
    int work[NUMBER_OF_RESOURCES];
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        work[i] = available[i]; // right now work array is equal to available array
    }

    bool finish[NUMBER_OF_CUSTOMERS] = {0};
    int finish_count = 0;
    bool changed;
    while (finish_count != NUMBER_OF_CUSTOMERS)
    {
        changed = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) // in each step is a costumer is done with resources we take back the given resources and check again but no new costumer finds satisfied we return false because we are in an unsafe state
        {
            if (!finish[i] && is_need_less_than_work(need[i], work)) // checking if this costumers need array is less than or equal the available resources.
            {                                                        // if true we satisfy our ith costumer and move on to another iteration
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
                {
                    work[j] += allocation[i][j];
                }

                finish[i] = true;
                finish_count++;
                changed = true;
            }
        }
        if (!changed) // if we don't have available resources to satisfy neither of our costumers then we're in an unsafe state.
        {
            return false;
        }
    }
    return true; // if all the iterations above didn't return false from the function then we're in a safe state.
}

int request_resources(int customer_num, int request[]) // in this function we request for some resources.
{

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        if (request[i] > need[customer_num][i] || request[i] > available[i]) // if we don't have enough resources or the request is more than costumers need we'll return -1
        {
            return -1;
        }
    }

    sem_wait(&mutex); // locking

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) // giving resources to the costumer and updating other arrays
    {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }

    if (is_safe()) // if it's safe finishing the function
    {
        sem_post(&mutex); // unlock first !
        return 0;
    }
    // it's not safe and we should take back the given resources.
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] += request[i];
        allocation[customer_num][i] -= request[i];
        need[customer_num][i] += request[i];
    }
    sem_post(&mutex); // unlock and finish with -1
    return -1;
}

int release_resources(int customer_num, int request[]) // in this function we request to release some resources
{
    sem_wait(&mutex); // lock for race condition handling

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) // releasing resources
    {
        available[i] += request[i];
        allocation[customer_num][i] -= request[i];
        need[customer_num][i] += request[i];
    }

    sem_post(&mutex); // unlock
    return 0;
}

void *customer_thread(int n) // in this function we simulate a costumer behavior
{
    int req[NUMBER_OF_RESOURCES];
    bool req_rel;
    int done;
    for (int i = 0; i < MAX_CUSTOMER_ITERATION; i++) // doing iterations
    {
        req_rel = rand() % 2; // request type
        if (req_rel == 1)
        {                                                 // requesting resource
            for (int j = 0; j < NUMBER_OF_RESOURCES; j++) // creating request array
            {
                req[j] = rand() % (need[n][j] + 1);
            }
            done = request_resources(n, req); // asking for resource
            printf("Customer %d Requests [%s\b] -> %s\n", n + 1, req_to_str(req), done == 0 ? "accepted" : "not accepted");
        }
        else
        {                                                 // release resource
            for (int j = 0; j < NUMBER_OF_RESOURCES; j++) // creating release array
            {
                req[j] = rand() % (allocation[n][j] + 1);
            }
            done = release_resources(n, req); // giving back resources
            printf("Customer %d Releases [%s\b]\n", n + 1, req_to_str(req));
        }
    }
}

char *req_to_str(int req[]) // casting to string in a desired format :)
{
    char *ret = malloc(100);
    char buf[5] = {0};
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        sprintf(buf, "%d", req[i]);
        strcat(ret, buf);
        strcat(ret, " ");
    }
    return ret;
}