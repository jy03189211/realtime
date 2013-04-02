//
//  main.c
//  Lab8
//
//  Created by jy03189211 on 13-3-24.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
static void ctrl_handler(int);
int stop=0;
int test;
int main(int argc, const char * argv[])
{
    int r;
    pid_t pid,test;
    int fd;
    char chr;
    char *buff="AAAAA";
    char name[80];
    if (signal(SIGCHLD,ctrl_handler)==SIG_ERR)
      printf("Cannot set signal handler/n");

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
    while(!stop){
        //wait(NULL);
        printf("Parent is working\n");
        sleep(1);
    }
    while(stop){
        test=waitpid(-1,NULL,WNOHANG);
        if(test>0)
          break;
    }

    printf("child pid is %d\n",test);
    lseek(fd,0,SEEK_SET);
    while (read(fd,&chr,1)!=0)
       printf("%c",chr);
    return 0;
}
static void ctrl_handler(int sig_no){
  if(sig_no==SIGCHLD){
    printf("child was terminated!\n");
    stop=1;
     
  }
}
