#include<stdio.h>
#include<unistd.h>

int main(int arg,char *argv[])
{
    int fd[2];
    pipe(fd);
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        printf("child process içindeyim\n");
        int x;
        printf("input a number : ");
        scanf("%d",&x);
        write(fd[1],&x,sizeof(int));
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        printf("parent process içindeyim\n");
        int y;
        read(fd[0],&y,sizeof(int));
        close(fd[0]);
        printf("get int %d from child process",y);
    }
}
