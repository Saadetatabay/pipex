#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<errno.h>

int main(int argc,char *argv[])
{
    int pid = fork();
    int pid2 = fork();
    if(pid == 0)
    {
        if(pid2 == 0)
            printf("child of child of parnet\n");
        else
            printf("child of parent\n");
            
    }
    else
    {
        if(pid2==0)
            printf("sec fork child of parent\n");
        else
        printf("parent\n");
    }
    while(wait(NULL)!=-1 || errno != ECHILD)
    {
        printf("waited for a child to finish\n");
    }
    return (0);
    // if (pid!=0)
    //     sleep(1);// burada pid 0 olmayan parent bir saniye bekliyor o yüzden önce child printleniyor sonra parent
    // printf("cuurent id %d parent id %d\n",getpid(),pid); 
    //getpid() parentid döndü pid childin idsini döndü pid = fork() childin idsi
    //getpid() childid döndü pid = fork() için 0 döndü
}