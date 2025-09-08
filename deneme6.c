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
        execlp("ls","ls","-l",NULL);
    }
    else{
        printf("parent process,child process working\n");
        wait(NULL);
        printf("SUCCESS\n"); 
    }
}
