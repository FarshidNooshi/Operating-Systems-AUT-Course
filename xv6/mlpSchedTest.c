#include "types.h"
#include "stat.h"
#include "user.h"
#include <stddef.h>
#define CHILDREN_NUMBER 60

struct data {
    int getBurstTimes[CHILDREN_NUMBER];        // getBurstTimes for each child
    int pids[CHILDREN_NUMBER];        // pid for each child
    int turnarounds[CHILDREN_NUMBER]; // turnaround times for each child
    int waitings[CHILDREN_NUMBER];    // waiting times for each child
};

struct info {
    int i;
    struct data *tdata;
};

void run(void* arg) {
    struct info *thread_info = (struct info*) arg;
    int priority = (thread_info->i / 10) + 1;
    setPriority(priority);
    for (int i = 0; i < 200; ++i){
        printf(1, "%d, %d\n", thread_info->i, i);
        sleep(10);
    }
    thread_info->tdata->turnarounds[thread_info->i] = getTurnAroundTime();
    thread_info->tdata->getBurstTimes[thread_info->i] = getBurstTime();
    thread_info->tdata->waitings[thread_info->i] = getWaitingTime();
    thread_info->tdata->pids[thread_info->i] = thread_info->i;
    exit();
}

int main() {

    struct data *p_data = (struct data*) malloc(sizeof(p_data));
    struct info thread_info[CHILDREN_NUMBER];

    for (int i = 0; i < CHILDREN_NUMBER; i++) {
        thread_info[i].i = i;
        thread_info[i].tdata = p_data;
        threadCreate(&run, (void*) &thread_info[i]);
    }

    while (join() > 0);

    int avg_bt = 0;
    int avg_tt = 0;
    int avg_wt = 0;

    for (int i = 0; i < CHILDREN_NUMBER; ++i) {
        printf(1, "Pid: %d, Burst Time: %d, Waiting Time: %d, Turnaround Time: %d\n",
               i, thread_info[i].tdata->getBurstTimes[i], thread_info[i].tdata->waitings[i],
               thread_info[i].tdata->turnarounds[i]);
        avg_bt += thread_info[i].tdata->getBurstTimes[i];
        avg_tt += thread_info[i].tdata->turnarounds[i];
        avg_wt += thread_info[i].tdata->waitings[i];
    }

    printf(1, "\n\n\nAvg: bt: %d, tt: %d, wt: %d\n", avg_bt / CHILDREN_NUMBER, avg_tt / CHILDREN_NUMBER, avg_wt / CHILDREN_NUMBER);
    exit();
}