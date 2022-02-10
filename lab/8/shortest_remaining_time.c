#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt;
    int tt;
} p[10], temp, copy[10];

int main()
{
    int i, j, n, totwt, tottt;
    float avg1, avg2;
    int total_time = 0;
    // reading inputs
    printf("\nEnter the number of process:\t");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        p[i].pid = i;
        printf("\nEnter the burst time:\t");
        scanf("%d", &p[i].bt);
        total_time += p[i].bt;
    }
    // first, sorting by burst time
    for (i = 1; i <= n; i++)
    {
        for (j = i + 1; j <= n; j++)
        {
            if (p[i].bt > p[j].bt)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
        copy[i] = p[i];
    }
    int m = n;
    // going through a loop for processing each process. we go step by step in processing processes with 1ms in each operation
    for (int time = 1; time <= total_time; time++)
    {
        // reducing remaining burst time of the running process by one unit
        copy[1].bt--;
        for (i = 2; i <= m; i++) // adding one unit to other processes waiting time
            copy[i].wt++;
        if (copy[1].bt == 0) // if the current process finishes
        {
            copy[1].tt += time;      // turn around time of the done process get updated
            for (j = 1; j <= n; j++) // giving the results of the copy array back to the original array
            {
                if (copy[1].pid == p[j].pid)
                {
                    p[j].tt = copy[1].tt;
                    p[j].wt = copy[1].wt;
                    break;
                }
            }
            copy[1].bt = 1000000 + time; // removing the finished process by giving it a very big burst time so that after sorting this element goes to the end of the list
            for (i = 1; i < m; i++)      // sorting processes because the first process is over.
            {
                for (j = i + 1; j <= m; j++)
                {
                    if (copy[i].bt > copy[j].bt)
                    {
                        temp = copy[i];
                        copy[i] = copy[j];
                        copy[j] = temp;
                    }
                }
            }
            m--; //removing the last process because it is finished
        }
        printf("do you want to add a process ?:\t"); // asking the user to give other processes
        int state = 0;
        scanf("%d", &state);
        if (state) // if a new process wants to being added then add it and update the copy list and p list.
        {
            n++;
            p[n].pid = n;
            printf("\nEnter the burst time:\t");
            scanf("%d", &p[n].bt);
            total_time += p[n].bt;
            m++;
            copy[m] = p[n];
            copy[m].tt = -time;     // because it added to the list at time = time (ms), when this process finishes its work we add its turn around time by the finishing time.
            for (i = 1; i < m; i++) // sorting copy list by burst time
            {
                for (j = i + 1; j <= m; j++)
                {
                    if (copy[i].bt > copy[j].bt)
                    {
                        temp = copy[i];
                        copy[i] = copy[j];
                        copy[j] = temp;
                    }
                }
            }
        }
    }
    // printing results
    totwt = tottt = 0;
    printf("\n processid \t bt\t wt\t tt\n");
    for (i = 1; i <= n; i++)
    {
        printf("\n\t%d \t%d \t%d \t%d", p[i].pid, p[i].bt, p[i].wt, p[i].tt);
        totwt = p[i].wt + totwt;
        tottt = p[i].tt + tottt;
    }
    float avg1 = 1.0 * totwt / n;
    float avg2 = 1.0 * tottt / n;
    printf("\navg1=%f \t avg2=%f \t", avg1, avg2);
    return 0;
}