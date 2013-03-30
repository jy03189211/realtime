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

int OpenChatFellow();

int main(int argc, const char * argv[])
{
    
    int fellow_desc,r;
    char chr_fellow = '\0',chr_own;
    fellow_desc=OpenChatFellow();
    
    pid_t pid;
    pid=fork();
    

    //child
    if(pid==0)
    {
        while ((r=read(fellow_desc, &chr_fellow, 1))>0) {

            
            write(1,&chr_fellow,1);
            
        }
        exit(0);
    }
    
    //parent
    while(chr_own!='q'&&chr_own!='Q'){
        
        read(0,&chr_own,1);
        
        write(1,&chr_own,1);
    }

    if(wait(NULL)>0){
        printf("\nchild terminted!\n");
    }
    
    
    
    return 0;
}


