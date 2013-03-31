//
//  main.c
//  Lab7
//
//  Created by jy03189211 on 13-3-24.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, const char * argv[])
{
    int r;
    pid_t pid;
    int fd;
    char chr;
    char *buff="AAAAA";
    char name[80];
    fd=open("lab7.txt", O_RDWR|O_CREAT|O_APPEND,0700);
    sprintf(name,"%d",fd);
    pid=fork();
    //child
    if (pid==0) {
        execl("child.exe","child.exe",name,buff,NULL);
        exit(0);
    }
    //parent
    //in lecture sample code it is said ">0", a bit missunderstand
    while ((r=waitpid(-1, NULL, WNOHANG))==0) {
        printf("%dParent is working\n",r);
        sleep(1);
    }
    printf("Child terminated\n");
    lseek(fd,0,SEEK_SET);
    while (read(fd,&chr,1)!=0)
       printf("%c",chr);
    return 0;
}
