#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt, tt; // waiting time, turn around time
} p[10];

int main()
{
    int i, n, totwt, tottt;
    printf("enter the number of processes:\t");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) //reading process input
    {
        printf("enter the burst time n:\t");
        scanf("%d", &p[i].bt);
        p[i].pid = i;
    }
    //calculating turn around time and waiting time
    p[1].wt = 0;
    p[1].tt = p[1].bt + p[1].wt;
    for (i = 2; i <= n; i++)
    {
        p[i].wt = p[i - 1].bt + p[i - 1].wt;
        p[i].tt = p[i].bt + p[i].wt;
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
