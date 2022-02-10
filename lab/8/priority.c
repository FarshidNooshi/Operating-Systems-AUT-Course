#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt;
    int tt;
    int prior;
} p[10], temp;

int main()
{
    int i, j, n, totwt, tottt;
    // reading inputs
    printf("\nenter the number of process:\t");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        p[i].pid = i;
        printf("\n enter the burst time:\t");
        scanf("%d", &p[i].bt);
        printf("\n enter the priority:\t");
        scanf("%d", &p[i].prior);
    }
    // sorting processes by their priority with bubble sort
    for (i = 1; i < n; i++)
    {
        for (j = i + 1; j <= n; j++)
        {
            if (p[i].prior > p[j].prior || (p[i].prior == p[j].prior && p[i].pid > p[j].pid))
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
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