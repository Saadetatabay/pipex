#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<time.h>
#include<wait.h>
int main()
{
    int fd[2]; //fd[0] okuma ucu fd[1] yazma ucu
    pipe(fd);
    int id = fork();
    if (id == 0)
    {
        //child
        int x;
        read(fd[0],&x,sizeof(int));
        printf("received %d \n",x);
        x *= 4;
        write(fd[1],&x,sizeof(int));
        printf("calculated %d \n",x);
    }
    else
    {
        srand(time(NULL));
        int y = rand() % 10;
        write(fd[1],&y,sizeof(int));
        printf("wrote %d\n",y);
        wait(NULL);
        read(fd[0],&y,sizeof(int));
        printf("result %d",y);
    }
}