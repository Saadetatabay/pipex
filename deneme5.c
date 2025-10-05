#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<time.h>
#include<wait.h>
int main()
{
    int p1[2];
    int p2[2]; 
    pipe(p1);
    pipe(p2);
    int id = fork();
    if (id == 0)
    {
        //child
        int x;
        read(p2[0],&x,sizeof(int));
        printf("received %d \n",x);
        x *= 4;
        write(p1[1],&x,sizeof(int));
        printf("calculated %d \n",x);
    }
    else
    {
        srand(time(NULL));
        int y = rand() % 10;
        write(p2[1],&y,sizeof(int));
        printf("wrote %d\n",y);
        wait(NULL);
        read(p1[0],&y,sizeof(int));
        printf("result %d",y);
    }
}