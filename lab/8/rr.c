#include <stdio.h>

struct process
{
    int pid;
    int bt;
    int wt, tt; // waiting time, turn around time
} p[60], x[10];

int main()
{
    int i, j, k, tot = 0, m, n;
    float total_waiting_time = 0.0, total_turn_around_time = 0.0;
    printf("\nenter the number of process:\t");
    scanf("%d", &n);
    for (i = 1; i <= n; i++) // reading process input
    {
        x[i].pid = i;
        printf("\nenter the burst time:\t");
        scanf("%d", &x[i].bt);
        tot += x[i].bt;
    }
    printf("\nenter the time quantum:\t");
    scanf("%d", &m);
    // calculating turn around time and waiting time
    p[0].tt = 0;
    k = 1;
    for (j = 1; j <= tot; j++)
        for (i = 1; i <= n; i++)
            if (x[i].bt != 0)
            {
                p[k].pid = i;
                if (x[i].bt - m < 0)
                {
                    p[k].bt = x[i].bt;
                    p[k].wt = p[k - 1].tt;
                    p[k].tt = p[k].wt + p[k].bt;
                    x[i].bt = 0;
                    k++;
                }
                else
                {
                    x[i].bt = x[i].bt - m;
                    p[k].wt = p[k - 1].tt;
                    p[k].tt = p[k].wt + m;
                    k++;
                }
            }
    // printing results
    printf("\nsum of burst times(total burst time):\t%d", tot);
    printf("\nProcess id \twt \ttt");
    for (i = 1; i < k; i++)
    {
        printf("\n\t%d \t%d \t%d", p[i].pid, p[i].wt, p[i].tt);
        total_waiting_time += p[i].wt;
        total_turn_around_time += p[i].tt;
    }
    total_waiting_time /= n;
    total_turn_around_time /= n;
    printf("\naverage waiting time:\t%f", total_waiting_time);
    printf("\naverage turn around time:\t%f\n", total_turn_around_time);
    return 0;
}