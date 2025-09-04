#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<time.h>
int main()
{
    int fd[2];
    pipe(fd);
    int id = fork();
    if (id == 0)
    {
        //child
        int x;
        read(fd[0],&x,sizeof(int));
        x *= 4;
        write(fd[1],&x,sizeof(int));
    }
    else
    {
        srand(time(NULL));
        int y = rand() % 10;
        printf("y %d",y);
        write(fd[1],&y,sizeof(int));
        read(fd[0],&y,sizeof(int));
        printf("%d",y);
    }
}