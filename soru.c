#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
void random_numbers()
{
    int fd;
    int num;
    char file_name[20];
    char buf[20];
    sprintf(file_name,"%d.txt",getpid());
    fd=open(file_name,O_CREAT | O_RDWR | O_TRUNC,0644);
    srand(time(NULL) + getpid());
    num=rand()%10;
    int len = sprintf(buf, "%d\n", num);
    write(fd, buf, len);
;
    close(fd);
}
void okuma(int pid,int pid2)
{
    wait(NULL);
    int fd;
    int fd2;
    int fd3;
    int num;
    int num2;
    int toplam;
    char file_name[20];
    char file_name2[20];
    char file_name3[20];

    sprintf(file_name,"%d.txt",pid);
    fd=open(file_name,O_RDONLY);
    read(fd,&num,sizeof(int));

    sprintf(file_name3,"%d.txt",pid2);
    fd3=open(file_name3,O_RDONLY);
    read(fd3,&num2,sizeof(int));

    toplam = num + num2;
    sprintf(file_name2,"%d.txt",getpid());
    fd2=open(file_name2,O_CREAT | O_RDWR | O_TRUNC,0644);
    write(fd2,&toplam,sizeof(int));
    close(fd);
    close(fd2);
    close(fd3);
}
void agac_olustur(int height)
{
    if(height == 0)
    {
        random_numbers();
        return ;
    }
    int pid = fork();
    if(pid > 0)
    {
        wait(NULL);
        //parent
        int pid2 = fork();
        if(pid2>0)
        {
            wait(NULL);
            okuma(pid2,pid);
            //parent toplama yapacak
        }
        else if(pid == 0)
        {
            agac_olustur(height-1);
        }
        else
            return;
    }
    else if(pid == 0)
    {
        //child
        agac_olustur(height-1);
    }
    else
        return;
}
int main()
{
    agac_olustur(3);
}