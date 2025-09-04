#include<stdio.h>
#include<unistd.h>

int main()
{
    int arr[] = {1,2,3,4,1,2,7};
    int adet = sizeof(arr) / sizeof(int);
    int start;
    int end;
    int fd[2];
    pipe(fd);
    int id = fork();
    if (id==0)
    {
        //printf("child process içindeyim\n");
        start = 0;
        end = adet / 2;
    }
    else
    {
        //printf("parent process içindeyim \n");
        start = adet / 2;
        end = adet;
    }
    int i;
    int sum = 0;
    for (i=start;i<end;i++)
        sum+=arr[i];
    printf("sum %d \n",sum);
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1],&sum,sizeof(int));
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int sumf;
        read(fd[0],&sumf,sizeof(int));
        close(fd[0]);
        int total = sum + sumf;
        printf("total sum %d \n",total);
    }
}