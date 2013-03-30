//
//  Lab5B2.c
//
//
//  Created by jy03189211 on 13-3-19.
//
//

#include <stdio.h>
//
//  main.c
//  Lab5B
//
//  Created by jy03189211 on 13-3-11.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAXLINE 80

int OpenChatFellow();
void counter(int i);
int main(int argc, const char * argv[])
{
    
    int fellow_desc,r;
    int i=0;
    int status;
    int fd[2];
    char chr_fellow = '\0',chr_own;
    char childline[MAXLINE];
    char parentline[MAXLINE];
    fellow_desc=OpenChatFellow();
    
    pid_t pid;
    
    if((pid=fork())<0){
        perror("fork error");
        exit(1);
        
    }
    //child
    else if(pid==0)
    {

        while ((r=read(fellow_desc, &chr_fellow, 1))>0) {
            write(1,&chr_fellow,1);
            i++;

        }
        printf("i from child %d\n",i);
        _exit(i);
    }
    
    //parent

    else{
        while(chr_own!='q'&&chr_own!='Q'){
            
                        read(0,&chr_own,1);
                        write(1,&chr_own,1);

        }
        //By using wait(&status), you gonna get "0" forever!!!!!!
        //Have to specify the pid as well
        if(waitpid(pid,&status,WUNTRACED)>0){
            if(WIFEXITED(status)){
                printf("\n%d\n",WEXITSTATUS(status));
            }
        }
    }
    
    
    return 0;
}


