
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAXSIZE 80
int main(int argc, const char * argv[])
{

    pid_t pid;
    int fd;
    char chr;
    long r;
    char *buff="AAAAA";
    char name[MAXSIZE];
    fd=open("lab7.txt", O_RDWR|O_CREAT|O_APPEND,0700);
    sprintf(name, "%d",fd);
    pid=fork();
    //child
    if (pid==0) {
        execl("child.exe",name,buff);
        exit(0);
    }
    //parent
    //in lecture sample code it is said ">0", a bit missunderstand
    while (waitpid(-1, NULL, WNOHANG|WUNTRACED)==0) {
        printf("Parent is working\n");
        sleep(1);
    }
    printf("Child terminated\n");
// why do I have to open it ag?
    lseek(fd,0,SEEK_SET);
    while ((r=read(fd,&chr,1))!=0){
        printf("%c",chr);
    }
    printf("\n");

    close(fd);
    return 0;
}
