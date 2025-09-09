#include <stdio.h>
#include <unistd.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);
    if (pipe(fd)== -1)
        return 1;
    
    int pid = fork();
    if (pid == 0)
    {
        //child process
        dup2(fd[1],1); //stdouta çıktı gidecek olan fd yazılıyor
        close(fd[1]);
        close(fd[0]);
        execlp("ping","ping","-c","5","google.com",NULL);
    }
    //normalde burada iki tane daha process açılmalı ama chil1 execlp ile başka bir programa dönüştü sadece parenttan fork olur
    //1 parent iki process olur
    int pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0],0); //grep aldığı inputu fd den okuyacak
        close(fd[1]);
        close(fd[0]);
        execlp("grep","grep","rtt",NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid,NULL,0);
    waitpid(pid2,NULL,0);
}