#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread
{
    int id;
    int* result;
    int count;
};
struct Range
{
    int firstIndex;
    int lastIndex;
};

int *randomArr;
int numThreads = 0;
int dimension = 0;

void *runner(void *param);
int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        fprintf(stderr, "usage: a.out <integer value>\n");
        /*exit(1);*/
        return -1;
    }
    if (atoi(argv[1]) < 1)
    {
        numThreads = 1;
    }
    else
    {
        numThreads = atoi(argv[1]);
    }
    if (atoi(argv[2]) < 1)
    {
        dimension = 1;
    }
    else
    {
        dimension = atoi(argv[2]);
    }
    if (numThreads > dimension)
    {
        numThreads = dimension;
    }

    printf("-----------------------\n");
    printf("SIZE OF ARRAY: %d\n", dimension);
    printf("NUM OF THREAD: %d\n", numThreads);
    printf("-----------------------\n");
    randomArr = (int *)malloc(dimension * sizeof(int));
    printf("-----------------------\n");
    for (int i = 0; i < dimension; i++)
    {
        randomArr[i] = rand() % 500;
        printf("Arr[%d] = %d\n", i, randomArr[i]);
    }
    printf("-----------------------\n");
    pthread_t tid[numThreads];
    struct thread core_data[numThreads];
    pthread_attr_t attr;

    for (int i = 0; i < numThreads; i++)
    {
        core_data[i].id = i;
    }

    pthread_attr_init(&attr);

    for (size_t i = 0; i < numThreads; i++)
    {
        pthread_create(&tid[i], &attr, runner, &core_data[i]);
    }
    for (size_t i = 0; i < numThreads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    printf("-----------------------\n");
    for (int i = 0; i < numThreads; i++)
    {
        printf("Core[%d]:\n",i);
        for (int j = 0; j < core_data[i].count; j++)
        {
            printf("\tResultArr[%d] = %d\n",j,core_data[i].result[j]);
        }
    }
    printf("-----------------------\n");
}

struct Range balance_load(int cores, int numbers, int core)
{
    double quotient = numbers / cores;
    double remainder = numbers % cores;
    int count = 0;
    struct Range load;
    if (core < remainder)
    {
        count = quotient + 1;
        load.firstIndex = core * count;
    }
    else
    {
        count = quotient;
        load.firstIndex = core * count + remainder;
    }
    load.lastIndex = load.firstIndex + count;

    return load;
};

void *runner(void *param)
{
    struct thread *core = (struct thread *)param;
    struct Range index = balance_load(numThreads, dimension, core->id);
    int firstIndex = index.firstIndex;
    int lastIndex = index.lastIndex;
    int range = lastIndex-firstIndex;
    core->result = (int *)malloc(range * sizeof(int));
    core->count=0;
    for (size_t i = 0; i < range; i++)
    {
        core->result[i]=0;
    }
    
    for (size_t i = firstIndex; i < lastIndex; i++)
    {
        if (randomArr[i]%2==0)
        {
            core->result[core->count++]=randomArr[i];
        }
    }
    pthread_exit(0);
}
