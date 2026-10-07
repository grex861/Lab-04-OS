#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    pid_t child1, child2;
    clock_t start, end;

    child1 = fork();

    if (child1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (child1 == 0)
    {
        start = clock();

        printf("Process 1: PID = %d, PPID = %d\n",
               getpid(), getppid());

        end = clock();

        printf("Process 1 execution time: %.3f ms\n",
               1000.0 * (double)(end - start) / CLOCKS_PER_SEC);

        return 0;
    }
    child2 = fork();

    if (child2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (child2 == 0)
    {
        start = clock();

        printf("Process 2: PID = %d, PPID = %d\n",
               getpid(), getppid());

        end = clock();

        printf("Process 2 execution time: %.3f ms\n",
               1000.0 * (double)(end - start) / CLOCKS_PER_SEC);

        return 0;
    }

    start = clock();

    printf("Main process: PID = %d, PPID = %d\n",
           getpid(), getppid());

    end = clock();

    printf("Main process execution time: %.3f ms\n",
           1000.0 * (double)(end - start) / CLOCKS_PER_SEC);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}
