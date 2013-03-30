//
//  main.c
//  Lab6A
//
//  Created by jy03189211 on 13-3-20.
//  Copyright (c) 2013年 jin jin. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    pid_t childs[3],pid;
    int i,j;
    char name='A';
    for (i = 0; i < 4 ; i++) {
        
        childs[i] = fork();
        if (childs[i] == 0) { //this is child
            for (j=0; j<5; j++) {
                putchar(name);
                sleep(1);
                fflush(stdout);
            }
            
            exit(0);
            
        }
        name++;
    }
    i = 0;
    while ((pid=waitpid(childs[i], NULL,0)) >0) {
        i++;
        printf("\nChild %d has terminated\n", pid);
    }
    
    
    
    return 0;
}

