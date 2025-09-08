// #include <stdio.h>
// #include <unistd.h>
// #include<unistd.h>
// #include <stdlib.h>
// #include <sys/wait.h>

// int main(int arg,char *argv[])
// {
//     char *argum[]={
//         "ls",
//         "-l",
//         NULL
//     };
//     char *env[]=
//     {
//         "PATH=/home/fractol",
//         NULL
//     };
//     //execl("/bin/ls","ls",NULL); //tam yol verilmeli
//     //execlp("ls","ls",NULL);  //tam yola gerek yok
//     //execvp("ls",argum);
//     execve("/bin/ls",argum,env);

//     printf("exec olmadi");
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Sadece MYVAR adında bir environment değişkeni oluşturduk
    char *env[] = {"NAME=saadet", NULL};

    // printenv programı ile environment değişkenlerini yazdırıyoruz
    char *args[] = {"printenv", NULL};

    // execve ile child process’e sadece MYVAR environment’ını veriyoruz
    execve("/usr/bin/printenv", args,env);

    perror("execve failed");
    return 1;
}
