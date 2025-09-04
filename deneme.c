#include <stdio.h>
#include<unistd.h>
#include <sys/wait.h>

int main()
{
    int n;
    int pid = fork();
    printf("ifelse öncesi \n");
    if (pid!=0)
    {
        printf("parent process %d \n",pid);
        n=6;
        wait(NULL);
    }
    else
    {
        printf("child process %d \n",pid);
        n=1;
    }

    int i;
    for (i = n;i<n+5;i++)
    {
        printf("%d",i);
        // fflush(stdout);
    }
    if (pid != 0)
        printf("\n");
    
        return (0);
}