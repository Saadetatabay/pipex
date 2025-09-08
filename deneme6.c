#include <stdio.h>
#include <unistd.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
    // printf("Benim programım başladı!\n");

    // // "ls -l" komutunu çalıştır
    // execlp("ping","ping","-c","3","google.com",NULL);
    // //execlp("ls", "ls", "-l", NULL);

    // // Buraya GELEMEZ çünkü exec başarılı olursa geri dönmez
    // printf("Bunu asla göremezsin!\n");

    // return 0;
    int pid = fork();
    if (pid == 0)
    {
        printf("child process\n");
        int err = execlp("ls","ls","-l",NULL);
        if (err == -1)
        {
            printf("could not find program to execute\n");
            return (5);
        }
    }
    else{
        printf("parent process,child process working\n");
        int status;
        wait(&status);
        if (WIFEXITED(status)) //childin döndüğü değeri alır exit status
        {
            int exit_code = WEXITSTATUS(status); //child return değerini aldık
            printf("Child exited with code: %d\n",exit_code);
            if (exit_code == 0)
                printf("SUCCESS\n"); 
        }
    }
    return 0;
}
