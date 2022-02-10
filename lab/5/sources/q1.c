#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int *hist, int sample) {
    for (int i = 0; i < 25; i++) 
    {
        printf("%d\t", i - 12);
        if(sample <= 400) {
            for (int j = 0; j < hist[i]; j++){
                printf("*");
            }
            printf("\n");
        }
        else
            printf(" %d\n", hist[i]);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Enter sample number.\n");
        return 0;
    }
    int sample, counter, random, hist[25] = {0};
    sscanf(argv[1], "%d", &sample);

    clock_t begin = clock();//starting timer
    srand(time(0));
    for (int i = 0; i < sample; i++)
    {
        counter = 12;
        for (int j = 0; j < 12; j++)
        {
            random = rand() % (100 + 1 - 0) + 0;
            if (random >= 49 && counter <= 23)
                counter++;
            else if (random < 49 && counter >= 1)
                counter--;        
        }
        hist[counter]++;
    }
    clock_t end = clock();
    printf("Runtime = %f s\n", ((double)end - begin) / CLOCKS_PER_SEC);
    print(hist, sample);
    return 0;
}